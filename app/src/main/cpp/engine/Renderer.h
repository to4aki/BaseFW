#pragma once

#include <cstdint>
#include <cassert>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "AndroidOut.h"

struct android_app;

class Renderer {
public:

    explicit Renderer(android_app *app);

    ~Renderer();

    void render(
            const uint32_t *framebuffer,
            int width,
            int height);

private:

    void initRenderer();

private:

    android_app *app_;

    EGLDisplay display_ = EGL_NO_DISPLAY;
    EGLSurface surface_ = EGL_NO_SURFACE;
    EGLContext context_ = EGL_NO_CONTEXT;

    GLuint program_ = 0;

    GLuint texture_ = 0;

    GLuint vbo_ = 0;

    GLint positionLoc_ = -1;
    GLint uvLoc_ = -1;

    int fbWidth_ = 0;
    int fbHeight_ = 0;
};