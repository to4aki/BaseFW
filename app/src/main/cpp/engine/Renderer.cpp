#include "Renderer.h"

static const char *kVertexShader = R"(
#version 300 es

in vec2 aPos;
in vec2 aUV;

out vec2 vUV;

void main()
{
    vUV = aUV;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

static const char *kFragmentShader = R"(
#version 300 es

precision mediump float;

in vec2 vUV;

uniform sampler2D uTexture;

out vec4 outColor;

void main()
{
    outColor = texture(uTexture, vUV);
}
)";

static GLuint compileShader(
        GLenum type,
        const char *source) {
    GLuint shader = glCreateShader(type);

    glShaderSource(
            shader,
            1,
            &source,
            nullptr);

    glCompileShader(shader);

    GLint ok = 0;

    glGetShaderiv(
            shader,
            GL_COMPILE_STATUS,
            &ok);

    assert(ok);

    return shader;
}

Renderer::Renderer(android_app *app)
        : app_(app) {
    initRenderer();
}

Renderer::~Renderer() {
    if (texture_) {
        glDeleteTextures(
                1,
                &texture_);
    }

    if (vbo_) {
        glDeleteBuffers(
                1,
                &vbo_);
    }

    if (program_) {
        glDeleteProgram(program_);
    }

    if (display_ != EGL_NO_DISPLAY) {
        eglMakeCurrent(
                display_,
                EGL_NO_SURFACE,
                EGL_NO_SURFACE,
                EGL_NO_CONTEXT);

        if (context_ != EGL_NO_CONTEXT) {
            eglDestroyContext(
                    display_,
                    context_);
        }

        if (surface_ != EGL_NO_SURFACE) {
            eglDestroySurface(
                    display_,
                    surface_);
        }

        eglTerminate(display_);
    }
}

void Renderer::initRenderer() {
    display_ =
            eglGetDisplay(
                    EGL_DEFAULT_DISPLAY);

    eglInitialize(
            display_,
            nullptr,
            nullptr);

    const EGLint configAttribs[] =
            {
                    EGL_RENDERABLE_TYPE,
                    EGL_OPENGL_ES3_BIT,

                    EGL_SURFACE_TYPE,
                    EGL_WINDOW_BIT,

                    EGL_RED_SIZE,
                    8,

                    EGL_GREEN_SIZE,
                    8,

                    EGL_BLUE_SIZE,
                    8,

                    EGL_NONE
            };

    EGLConfig config;
    EGLint numConfig;

    eglChooseConfig(
            display_,
            configAttribs,
            &config,
            1,
            &numConfig);

    surface_ =
            eglCreateWindowSurface(
                    display_,
                    config,
                    app_->window,
                    nullptr);

    const EGLint ctxAttribs[] =
            {
                    EGL_CONTEXT_CLIENT_VERSION,
                    3,
                    EGL_NONE
            };

    context_ =
            eglCreateContext(
                    display_,
                    config,
                    EGL_NO_CONTEXT,
                    ctxAttribs);

    eglMakeCurrent(
            display_,
            surface_,
            surface_,
            context_);

    GLuint vs =
            compileShader(
                    GL_VERTEX_SHADER,
                    kVertexShader);

    GLuint fs =
            compileShader(
                    GL_FRAGMENT_SHADER,
                    kFragmentShader);

    program_ =
            glCreateProgram();

    glAttachShader(
            program_,
            vs);

    glAttachShader(
            program_,
            fs);

    glLinkProgram(
            program_);

    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(program_);

    positionLoc_ =
            glGetAttribLocation(
                    program_,
                    "aPos");

    uvLoc_ =
            glGetAttribLocation(
                    program_,
                    "aUV");

    float vertices[] =
            {
                    -1.f, -1.f, 0.f, 1.f,
                    1.f, -1.f, 1.f, 1.f,
                    -1.f, 1.f, 0.f, 0.f,

                    1.f, 1.f, 1.f, 0.f
            };

    glGenBuffers(
            1,
            &vbo_);

    glBindBuffer(
            GL_ARRAY_BUFFER,
            vbo_);

    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW);

    glGenTextures(
            1,
            &texture_);

    glBindTexture(
            GL_TEXTURE_2D,
            texture_);

    glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

    glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);

    glClearColor(
            0.f,
            0.f,
            0.f,
            1.f);

    GLint texLoc =
            glGetUniformLocation(
                    program_,
                    "uTexture");

    glUniform1i(texLoc, 0);
}

void Renderer::render(
        const uint32_t *framebuffer,
        int width,
        int height)
{
    EGLint surfaceWidth;
    EGLint surfaceHeight;

    eglQuerySurface(
            display_,
            surface_,
            EGL_WIDTH,
            &surfaceWidth);

    eglQuerySurface(
            display_,
            surface_,
            EGL_HEIGHT,
            &surfaceHeight);

    glViewport(
            0,
            0,
            surfaceWidth,
            surfaceHeight);

    glBindTexture(
            GL_TEXTURE_2D,
            texture_);

    if (width != fbWidth_
        || height != fbHeight_) {

        fbWidth_ = width;
        fbHeight_ = height;

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                framebuffer);
    } else {

        glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                0,
                0,
                width,
                height,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                framebuffer);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(
            GL_ARRAY_BUFFER,
            vbo_);

    glEnableVertexAttribArray(
            positionLoc_);

    glEnableVertexAttribArray(
            uvLoc_);

    glVertexAttribPointer(
            positionLoc_,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(float) * 4,
            (void*)0);

    glVertexAttribPointer(
            uvLoc_,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(float) * 4,
            (void*)(sizeof(float) * 2));

    glDrawArrays(
            GL_TRIANGLE_STRIP,
            0,
            4);

    eglSwapBuffers(
            display_,
            surface_);
}