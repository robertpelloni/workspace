/*
#   clove
#
#   Copyright (C) 2016-2025 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include <stdint.h>
#include <stdio.h>

#include "../include/graphics.h"
#include "../include/gl.h"
#include "../include/utils.h"
#include "../include/vector.h"
#include "../include/matrixstack.h"
#include "../include/font.h"
#include "../include/batch.h"
#include "../include/quad.h"
#include "../include/shader.h"
#include "../include/geometry.h"

#ifndef SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
#define SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG 0x0002
#endif

static struct {
    SDL_Window *window;
    SDL_GLContext context;
    SDL_WindowFlags w_flags;
    GLuint defaultVao;

    SDL_Surface *surface;
    graphics_Color backgroundColor;
    graphics_Color foregroundColor;

    bool colorMask[4];
    graphics_BlendMode blendMode;
    int scissorBox[4];
    bool scissorSet;

    mat4x4 projectionMatrix;
    const char *title;
    int x;
    int y;
    bool isCreated;
    bool hasWindow;
    image_ImageData *icon;
    bool mouse_focus;
    bool focus;
} moduleData;

SDL_Window *graphics_getWindow(void) {
    if (moduleData.hasWindow)
        return moduleData.window;

    return NULL;
}


void graphics_bindDefaultVao(void) {
    // In core profile (macOS), a VAO must be bound for glVertexAttribPointer / glDraw*.
    // Create a default VAO lazily in case init path changes.
    if (moduleData.defaultVao == 0) {
        glGenVertexArrays(1, &moduleData.defaultVao);
    }
    glBindVertexArray(moduleData.defaultVao);
}

static void graphics_init_window(int width, int height) {
    glewExperimental = true;
    GLenum res = glewInit();

    if (res != GLEW_OK) {
        clove_error("Error: Could not init glew!\n");
        return;
    }

    glViewport(0, 0, width, height);

    // Default VAO required for core profile rendering.
    glGenVertexArrays(1, &moduleData.defaultVao);
    glBindVertexArray(moduleData.defaultVao);

    // Clear any GL errors that might have been generated during context/glew init.
    while (glGetError() != GL_NO_ERROR) {
    }

    matrixstack_init();

    m4x4_newIdentity(&moduleData.projectionMatrix);
    m4x4_newOrtho(&moduleData.projectionMatrix, 0, width, height, 0, 0.1f, 100.0f);

    moduleData.isCreated = true;

    graphics_setColor(1.0f, 1.0f, 1.0f, 1.0f);

    graphics_geometry_init();
    graphics_font_init();
    graphics_batch_init();
    graphics_image_init();
    graphics_shader_init();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    graphics_setColorMask(true, true, true, true);
    graphics_setBlendMode(graphics_BlendMode_alpha);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    graphics_clearScissor();
}

void graphics_init(int width, int height, bool resizable, bool stats, bool show) {
    moduleData.isCreated = false;
    moduleData.hasWindow = show;

    if (!show) {
        return;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        clove_error("Error: Could not init SDL video \n");
        return;
    }

    moduleData.x = SDL_WINDOWPOS_CENTERED;
    moduleData.y = SDL_WINDOWPOS_CENTERED;
    moduleData.title = "CLove: Untitled window";

    moduleData.w_flags = (SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (resizable) {
        moduleData.w_flags = (SDL_WindowFlags) (moduleData.w_flags | SDL_WINDOW_RESIZABLE);
    }

    moduleData.window = SDL_CreateWindow(moduleData.title, moduleData.x, moduleData.y, width, height,
                                         moduleData.w_flags);

    if (!moduleData.window) {
        clove_error("Error: Could not create window :O\n");
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);


    moduleData.context = SDL_GL_CreateContext(moduleData.window);
    if (!moduleData.context) {
        clove_error("Error: Could not create window context!\n");
        return;
    }

    //moduleData.surface = SDL_GetWindowSurface(moduleData.window);
    /* This makes our buffer swap synchronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    if (stats > 0) {
        printf("Sdl version: %d.%d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
        printf("OpenGL version: %s\n", glGetString(GL_VERSION));
        printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        printf("Vendor: %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
    }

    graphics_init_window(width, height);
}

void graphics_shutdown() {
    if (moduleData.hasWindow) {
        if (moduleData.defaultVao) {
            glDeleteVertexArrays(1, &moduleData.defaultVao);
            moduleData.defaultVao = 0;
        }
        SDL_GL_DeleteContext(moduleData.context);
        SDL_DestroyWindow(moduleData.window);
    }
    moduleData.hasWindow = false;
    SDL_Quit();
}

void graphics_setBackgroundColor(float red, float green, float blue, float alpha) {
    moduleData.backgroundColor.red = red;
    moduleData.backgroundColor.green = green;
    moduleData.backgroundColor.blue = blue;
    moduleData.backgroundColor.alpha = alpha;
    glClearColor(red, green, blue, alpha);
}

void graphics_setColor(float red, float green, float blue, float alpha) {
    moduleData.foregroundColor.red = red;
    moduleData.foregroundColor.green = green;
    moduleData.foregroundColor.blue = blue;
    moduleData.foregroundColor.alpha = alpha;
}

void graphics_clear(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void graphics_swap(void) {
    if (moduleData.hasWindow) {
        SDL_GL_SwapWindow(moduleData.window);
    }
}


void graphics_drawArray(graphics_Quad const *quad, mat4x4 const *tr2d, GLuint ibo, GLuint count, GLenum type,
                        GLenum indexType, float const *useColor, float ws, float hs) {
#ifdef GL_VERTEX_ARRAY_BINDING
    GLint vao = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    if (vao == 0) {
        graphics_bindDefaultVao();
    }
#else
    graphics_bindDefaultVao();
#endif

    // tr = proj * view * model * vpos;

    // layout: pos(2), uv(2), color(4) => 8 floats per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void *) (4 * sizeof(float)));

    graphics_Shader_activate(
        &moduleData.projectionMatrix,
        matrixstack_head(),
        tr2d,
        quad,
        useColor,
        ws,
        hs
    );

    if (ibo != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    }
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    glDrawElements(type, count, indexType, (GLvoid const *) 0);
}

void graphics_drawBatch(
    graphics_Quad const *quad,
    mat4x4 const *tr2d,
    GLuint count,
    GLenum type,
    GLenum indexType,
    float const *useColor,
    float ws,
    float hs
) {
#ifdef GL_VERTEX_ARRAY_BINDING
    GLint vao = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    if (vao == 0) {
        printf("Default VAO bind in drawBatch\n");
        graphics_bindDefaultVao();
    }
#else
    graphics_bindDefaultVao();
#endif


    // IMPORTANT: do NOT bind any VAO here.
    // Caller must have a VAO bound (defaultVao for non-batch, batch->vao for batch).
    graphics_Shader_activate(
        &moduleData.projectionMatrix,
        matrixstack_head(),
        tr2d,
        quad,
        useColor,
        ws,
        hs
    );

    glDrawElements(type, count, indexType, (GLvoid const *) 0);

    // GLenum postErr = glGetError();
    // if (postErr != GL_NO_ERROR) {
    //     clove_error("GL ERROR at graphics_drawBatch: post-draw: 0x%04x\n", (unsigned) postErr);
    // }
}

int *graphics_getDesktopDimension() {
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        clove_error("Error, love.window.getDesktopDimension(): %s", SDL_GetError());
    }
    static int ret[2] = {0};
    ret[0] = dm.w;
    ret[1] = dm.h;
    return ret;
}

const char *graphics_getDisplayName(int indx) {
    return SDL_GetDisplayName(indx);;
}

void graphics_setTitle(const char *title) {
#ifndef CLOVE_WEB
    if (moduleData.hasWindow) {
        moduleData.title = title;
        SDL_SetWindowTitle(moduleData.window, title);
    }
#endif
}

bool graphics_hasMouseFocus() {
    return moduleData.mouse_focus;
}

void graphics_setMouseFocus(int value) {
    moduleData.mouse_focus = value;
}

bool graphics_hasFocus() {
    return moduleData.focus;
}

void graphics_setFocus(int value) {
    moduleData.focus = value;
}

void graphics_setPosition(int x, int y) {
#ifndef CLOVE_WEB
    if (moduleData.hasWindow) {
        if (x <= -1) // center x
            x = SDL_WINDOWPOS_CENTERED;
        if (y <= -1) // center y
            y = SDL_WINDOWPOS_CENTERED;
        SDL_SetWindowPosition(moduleData.window, x, y);
    }
#endif
}

int graphics_getWindowX() {
    if (!moduleData.hasWindow) {
        return 0;
    }
    int x, y;
    SDL_GetWindowPosition(moduleData.window, &x, &y);
    return x;
}

int graphics_getWindowY() {
    if (!moduleData.hasWindow) {
        return 0;
    }
    int x, y;
    SDL_GetWindowPosition(moduleData.window, &x, &y);
    return y;
}

void graphics_setVsync(bool value) {
    if (moduleData.hasWindow) SDL_GL_SetSwapInterval(value);
}

void graphics_setBordless(bool value) {
    if (moduleData.hasWindow)
        SDL_SetWindowBordered(moduleData.window, (SDL_bool) !value);
}

void graphics_setWindowResizable(bool value) {
    if (!moduleData.hasWindow) {
        return;
    }
    SDL_SetWindowResizable(moduleData.window, value);
}

void graphics_setMinSize(int w, int h) {
    if (moduleData.hasWindow) SDL_SetWindowMinimumSize(moduleData.window, w, h);
}

void graphics_setMaxSize(int w, int h) {
    if (moduleData.hasWindow) SDL_SetWindowMaximumSize(moduleData.window, w, h);
}

int graphics_getDisplayCount() {
    return moduleData.hasWindow ? SDL_GetNumVideoDisplays() : 0;
}

void graphics_setIcon(image_ImageData *imgd) {
    if (!moduleData.hasWindow) {
        return;
    }
    //Adapted from Love
    Uint32 rmask, gmask, bmask, amask;
    moduleData.icon = imgd;

    rmask = 0x000000FF;
    gmask = 0x0000FF00;
    bmask = 0x00FF0000;
    amask = 0xFF000000;

    int w = image_ImageData_getWidth(imgd);
    int h = image_ImageData_getHeight(imgd);
    int pitch = w * image_ImageData_getChannels(imgd);;

    SDL_Surface *sdlicon = 0;

    sdlicon = SDL_CreateRGBSurfaceFrom(image_ImageData_getSurface(imgd), w, h, 32, pitch, rmask, gmask, bmask, amask);
    SDL_SetWindowIcon(moduleData.window, sdlicon);
    SDL_FreeSurface(sdlicon);
}

void graphics_loadAndSetIcon(const char *iconPath) {
    FILE *icon = fopen(iconPath, "r");
    if (!icon) {
        clove_error("%s %s\n", "Warning: Could not load window icon: ", iconPath);
        return;
    }
    fclose(icon);
    image_ImageData *img = malloc(sizeof(image_ImageData));
    image_ImageData_new_with_filename(img, iconPath);
    graphics_setIcon(img);
    free(img);
}

image_ImageData *graphics_getIcon() {
    return moduleData.icon;
}

void graphics_setWindowSize(int width, int height) {
    SDL_SetWindowSize(moduleData.window, width, height);
}

int graphics_setMode(int width, int height,
                     bool fullscreen, bool vsync, int min_size_x, int min_size_y,
                     int max_size_x, int max_size_y, bool border, int x, int y) {
    /*
     * If the main window was disabled in conf.lua
     * then we shall create one using this function.
     *
     * Note: This works only on desktop
     */
#ifndef CLOVE_WEB
    if (!moduleData.hasWindow) {
        moduleData.window = SDL_CreateWindow(moduleData.title, moduleData.x, moduleData.y, width, height,
                                             moduleData.w_flags);
        if (!moduleData.window)
            clove_error("Error: Could not create window :O");

        moduleData.context = SDL_GL_CreateContext(moduleData.window);

        if (!moduleData.context)
            clove_error("Error: Could not create window context!");

        if (vsync)
            SDL_GL_SetSwapInterval(1);

        graphics_init_window(width, height);

        moduleData.hasWindow = true;
    }

    SDL_SetWindowSize(moduleData.window, width, height);

    m4x4_newOrtho(&moduleData.projectionMatrix, 0, width, height, 0, 0.1f, 100.0f);
    glViewport(0, 0, width, height);

    if (fullscreen)
        SDL_SetWindowFullscreen(moduleData.window, SDL_WINDOW_FULLSCREEN);

    SDL_SetWindowMinimumSize(moduleData.window, min_size_x, min_size_y);
    SDL_SetWindowMaximumSize(moduleData.window, max_size_x, max_size_y);
    SDL_SetWindowBordered(moduleData.window, (SDL_bool) border);
    if (x != -1 || y != -1)
        SDL_SetWindowPosition(moduleData.window, x, y);
    else if (x == -1 && y == -1)
        graphics_setPosition(-1, -1);
#else
    //moduleData.surface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL);
    SDL_SetWindowSize(moduleData.window, width, height);
#endif
    return 1;
}

int graphics_getWidth(void) {
    if (moduleData.hasWindow) {
        int w;
        int h;
        SDL_GetWindowSize(moduleData.window, &w, &h);
        return w;
    }
    return 0;
}

int graphics_getHeight(void) {
    if (moduleData.hasWindow) {
        int w;
        int h;
        SDL_GetWindowSize(moduleData.window, &w, &h);
        return h;
    }
    return 0;
}

const char *graphics_getTitle() {
    return moduleData.title;
}

int graphics_setFullscreen(bool fullscreen, const char *mode) {
#ifndef CLOVE_WEB
    if (moduleData.hasWindow) {
        if (!fullscreen) {
            SDL_SetWindowFullscreen(moduleData.window, 0);
            return 0;
        }

        if (strcmp(mode, "desktop") == 0) {
            if (SDL_SetWindowFullscreen(moduleData.window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0) {
                clove_error("Error on 'fullscreen' %s", SDL_GetError());
            }
        } else if (strcmp(mode, "fullscreen") == 0) {
            if (SDL_SetWindowFullscreen(moduleData.window, SDL_WINDOW_FULLSCREEN) < 0) {
                clove_error("Error on 'fullscreen' %s", SDL_GetError());
            }
        } else {
            clove_error("Unknown fullscreen type: %s, use: 'desktop' or 'fullscreen'\n", mode);
            return -1;
        }
    }
#endif
    return 0;
}

bool graphics_isCreated() {
    return moduleData.isCreated;
}

void graphics_set_camera_2d(float left, float right, float bottom, float top, float zNear, float zFar) {
    if (moduleData.hasWindow) {
        m4x4_newIdentity(&moduleData.projectionMatrix);
        m4x4_newOrtho(&moduleData.projectionMatrix, left, right, bottom, top, zNear, zFar);
    }
}

void graphics_set_camera_3d(float fov, float ratio, float zNear, float zFar) {
    m4x4_newIdentity(&moduleData.projectionMatrix);
    m4x4_newPerspective(&moduleData.projectionMatrix, fov, ratio, zNear, zFar);
}

void graphics_set_look_at(float px, float py, float pz, float tx, float ty, float tz, float ux, float uy, float uz) {
    m4x4_newLookAt(matrixstack_head(), vec3_new(px, py, pz), vec3_new(tx, ty, tz), vec3_new(ux, uy, uz));
}

float *graphics_getColor(void) {
    return (float *) (&moduleData.foregroundColor);
}

float *graphics_getBackgroundColor(void) {
    return (float *) (&moduleData.backgroundColor);
}

void graphics_setColorMask(bool r, bool g, bool b, bool a) {
    moduleData.colorMask[0] = r;
    moduleData.colorMask[1] = g;
    moduleData.colorMask[2] = b;
    moduleData.colorMask[3] = a;

    glColorMask(r, g, b, a);
}

void graphics_getColorMask(bool *r, bool *g, bool *b, bool *a) {
    *r = moduleData.colorMask[0];
    *g = moduleData.colorMask[1];
    *b = moduleData.colorMask[2];
    *a = moduleData.colorMask[3];
}

graphics_BlendMode graphics_getBlendMode(void) {
    return moduleData.blendMode;
}

void graphics_setBlendMode(graphics_BlendMode mode) {
    moduleData.blendMode = mode;

    GLenum sfRGB = GL_ONE;
    GLenum dfRGB = GL_ZERO;
    GLenum sfA = GL_ONE;
    GLenum dfA = GL_ZERO;
    GLenum bFunc = GL_FUNC_ADD;

    switch (mode) {
        case graphics_BlendMode_alpha:
            sfRGB = GL_SRC_ALPHA;
            sfA = GL_ONE;
            dfRGB = dfA = GL_ONE_MINUS_SRC_ALPHA;
            break;

        case graphics_BlendMode_subtractive:
            bFunc = GL_FUNC_REVERSE_SUBTRACT;
        // fallthrough
        case graphics_BlendMode_additive:
            sfA = sfRGB = GL_SRC_ALPHA;
            dfA = dfRGB = GL_ONE;
            break;


        case graphics_BlendMode_multiplicative:
            sfA = sfRGB = GL_DST_COLOR;
            dfA = dfRGB = GL_ZERO;
            break;

        case graphics_BlendMode_premultiplied:
            sfA = sfRGB = GL_ONE;
            dfA = dfRGB = GL_ONE_MINUS_SRC_ALPHA;
            break;

        case graphics_BlendMode_screen:
            sfA = sfRGB = GL_ONE;
            dfA = dfRGB = GL_ONE_MINUS_SRC_COLOR;
            break;

        case graphics_BlendMode_replace:
        default:
            // uses default init values
            break;
    }

    glBlendFuncSeparate(sfRGB, dfRGB, sfA, dfA);
    glBlendEquation(bFunc);
}

void graphics_clearScissor(void) {
    moduleData.scissorSet = false;
    glDisable(GL_SCISSOR_TEST);
}

void graphics_setScissor(int x, int y, int w, int h) {
    moduleData.scissorBox[0] = x;
    moduleData.scissorBox[1] = y;
    moduleData.scissorBox[2] = w;
    moduleData.scissorBox[3] = h;
    moduleData.scissorSet = true;
    glScissor(x, y, w, h);
    glEnable(GL_SCISSOR_TEST);
}

bool graphics_getScissor(int *x, int *y, int *w, int *h) {
    if (!moduleData.scissorSet) {
        return false;
    }

    *x = moduleData.scissorBox[0];
    *y = moduleData.scissorBox[1];
    *w = moduleData.scissorBox[2];
    *h = moduleData.scissorBox[3];

    return true;
}

void graphics_reset(void) {
    matrixstack_origin();
    graphics_setColor(1.0f, 1.0f, 1.0f, 1.0f);
    graphics_setBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
    graphics_setBlendMode(graphics_BlendMode_alpha);
    graphics_setDefaultShader();
    graphics_setColorMask(true, true, true, true);
    graphics_clearScissor();
}

double graphics_getDPIScale() {
    if (!moduleData.hasWindow) {
        return 0;
    }

    int pixelWidth, pixelHeight;
    SDL_GL_GetDrawableSize(moduleData.window, &pixelWidth, &pixelHeight);
    return (double) pixelHeight / (double) graphics_getHeight();
}

void graphics_shear(float kx, float ky) {
    matrixstack_shear_2d(kx, ky);
}
