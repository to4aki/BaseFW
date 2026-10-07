#include "Renderer.h"
#include <android/native_window.h>

static const char kVertexShader[] =
"attribute vec2 aPos;\n"
"attribute vec2 aUV;\n"
"varying vec2 vUV;\n"
"void main()\n"
"{\n"
"    vUV = aUV;\n"
"    gl_Position = vec4(aPos, 0.0, 1.0);\n"
"}\n";

static const char kFragmentShader[] =
"precision mediump float;\n"
"varying vec2 vUV;\n"
"uniform sampler2D uTexture;\n"
"void main()\n"
"{\n"
"    gl_FragColor = texture2D(uTexture, vUV);\n"
"}\n";

static GLuint compileShader(
        GLenum type,
        const char *source)
{
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

    if(!ok)
    {
        char log[2048];

        GLsizei len = 0;

        glGetShaderInfoLog(
                shader,
                sizeof(log),
                &len,
                log);

        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "Shader compile failed:\n%s",
                log);

        glDeleteShader(shader);

        return 0;
    }

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
    if (!app_ || !app_->window) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "app or app->window is null");
        return;
    }

    display_ =
            eglGetDisplay(
                    EGL_DEFAULT_DISPLAY);

    if (display_ == EGL_NO_DISPLAY) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "eglGetDisplay failed");
        return;
    }

    if (!eglInitialize(
            display_,
            nullptr,
            nullptr)) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "eglInitialize failed");
        return;
    }

    const EGLint configAttribsES3[] =
            {
                    EGL_RENDERABLE_TYPE,
                    EGL_OPENGL_ES3_BIT,

                    EGL_SURFACE_TYPE,
                    EGL_WINDOW_BIT,

                    EGL_NONE
            };

    const EGLint configAttribsES2[] =
            {
                    EGL_RENDERABLE_TYPE,
                    EGL_OPENGL_ES2_BIT,

                    EGL_SURFACE_TYPE,
                    EGL_WINDOW_BIT,

                    EGL_NONE
            };

    EGLConfig config = nullptr;
    EGLint numConfig = 0;

    if (!eglChooseConfig(
            display_,
            configAttribsES3,
            &config,
            1,
            &numConfig) || numConfig < 1) {
        __android_log_print(
                ANDROID_LOG_INFO,
                "Renderer",
                "ES3 config not supported, trying ES2...");

        if (!eglChooseConfig(
                display_,
                configAttribsES2,
                &config,
                1,
                &numConfig) || numConfig < 1) {
            __android_log_print(
                    ANDROID_LOG_ERROR,
                    "Renderer",
                    "eglChooseConfig ES2 failed");
            return;
        }
    }

    EGLint format = 0;
    if (eglGetConfigAttrib(
            display_,
            config,
            EGL_NATIVE_VISUAL_ID,
            &format)) {
        ANativeWindow_setBuffersGeometry(
                app_->window,
                0,
                0,
                format);
    }

    surface_ =
            eglCreateWindowSurface(
                    display_,
                    config,
                    app_->window,
                    nullptr);

    if (surface_ == EGL_NO_SURFACE) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "eglCreateWindowSurface failed: 0x%x",
                eglGetError());
        return;
    }

    const EGLint ctxAttribs3[] =
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
                    ctxAttribs3);

    if (context_ == EGL_NO_CONTEXT) {
        __android_log_print(
                ANDROID_LOG_INFO,
                "Renderer",
                "ES3 context creation failed, trying ES2...");

        const EGLint ctxAttribs2[] =
                {
                        EGL_CONTEXT_CLIENT_VERSION,
                        2,
                        EGL_NONE
                };

        context_ =
                eglCreateContext(
                        display_,
                        config,
                        EGL_NO_CONTEXT,
                        ctxAttribs2);
    }

    if (context_ == EGL_NO_CONTEXT) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "eglCreateContext failed completely: 0x%x",
                eglGetError());
        return;
    }

    if (!eglMakeCurrent(
            display_,
            surface_,
            surface_,
            context_)) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "eglMakeCurrent failed: 0x%x",
                eglGetError());
        return;
    }

    GLuint vs =
            compileShader(
                    GL_VERTEX_SHADER,
                    kVertexShader);

    GLuint fs =
            compileShader(
                    GL_FRAGMENT_SHADER,
                    kFragmentShader);

    if (vs == 0 || fs == 0) {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "Renderer",
                "Shader compilation failed, vs=%u, fs=%u",
                vs, fs);
        return;
    }

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
    if (display_ == EGL_NO_DISPLAY || surface_ == EGL_NO_SURFACE || context_ == EGL_NO_CONTEXT) {
        return;
    }

    EGLint surfaceWidth = 0;
    EGLint surfaceHeight = 0;

    if (!eglQuerySurface(
            display_,
            surface_,
            EGL_WIDTH,
            &surfaceWidth) ||
        !eglQuerySurface(
            display_,
            surface_,
            EGL_HEIGHT,
            &surfaceHeight)) {
        return;
    }

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

    glFinish();

    eglSwapBuffers(
            display_,
            surface_);
}