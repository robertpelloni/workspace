/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "graphics_shader.h"

#include "../3rdparty/FH/src/value.h"
#include "../3rdparty/slre/slre.h"

#include <string.h>
#include <stdlib.h>

#include "../include/filesystem.h"
#include "../include/minmax.h"

#include "image.h"

static fh_c_obj_gc_callback shader_gc(fh_graphics_Shader *shader) {
    graphics_Shader_free(&shader->shader);
    free(shader);
    return (fh_c_obj_gc_callback) 1;
}

static struct {
    struct slre fragmentSingleShaderDetectRegex;
    struct slre vertexShaderDetectRegex;
    void * sendValueBuffer;
    int sendValueBufferSize;
    fh_graphics_Shader *currentShader;
} moduleData;

static char const * fragmentSingleShaderDetectRegexSrc = "vec4\\s*effect\\s*\\(";
static char const * vertexShaderDetectRegexSrc = "vec4\\s*position\\s*\\(";

bool static isVertexShader(char const* str) {
    return slre_match(&moduleData.vertexShaderDetectRegex, str, strlen(str), NULL);
}

bool static isSingleFragmentShader(char const* str) {
    return slre_match(&moduleData.fragmentSingleShaderDetectRegex, str, strlen(str), NULL);
}

static int fn_love_graphics_newShader(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_string(&args[0]))
        return fh_set_error(prog, "Expected vertex source");

    const char *vertexSrc = fh_get_string(&args[0]);
    const char *fragmentSrc = NULL;

    char *loadedFile1 = NULL;
    char *loadedFile2 = NULL;

    if (n_args == 2) {
        if (!fh_is_string(&args[1])) {
            return fh_set_error(prog, "expected string as second argument");
        }
        fragmentSrc = fh_get_string(&args[1]);

        if (isVertexShader(vertexSrc)) {
            filesystem_read(vertexSrc, &loadedFile1);
            if (!loadedFile1 || !isVertexShader(loadedFile1)) {
                free(loadedFile1);
                return fh_set_error(prog, "input 1 is not a valid vertex shader");
            }
            vertexSrc = loadedFile1;
        }

        if(!isSingleFragmentShader(fragmentSrc)) {
            filesystem_read(fragmentSrc, &loadedFile2);
            if(!loadedFile2 || !isSingleFragmentShader(loadedFile2)) {
                free(loadedFile1);
                free(loadedFile2);
                return fh_set_error(prog, "input 2 is not a valid fragment shader");
            }
            fragmentSrc = loadedFile2;
        }
    } else if (n_args == 1) {
        if(isVertexShader(vertexSrc)) {
            // nothing required
        } else if(isSingleFragmentShader(vertexSrc)) {
            fragmentSrc = vertexSrc;
            vertexSrc = NULL;
        } else {
            // TODO
            int loadedFile1Size = filesystem_read(vertexSrc, &loadedFile1);
            (void) loadedFile1Size;
            if(!loadedFile1) {
                return fh_set_error(prog, "could not open file");
            }

            if(isSingleFragmentShader(loadedFile1)) {
                fragmentSrc = loadedFile1;
                vertexSrc = NULL;
            } else if(isVertexShader(loadedFile1)) {
                vertexSrc = loadedFile1;
                fragmentSrc = NULL;
            } else {
                free(loadedFile1);
                return fh_set_error(prog, "input is not a valid shader");
            }
        }
    } else {
        return fh_set_error(prog, "Invalid parameter");
    }

    fh_graphics_Shader *shader = malloc(sizeof(fh_graphics_Shader));
    graphics_ShaderCompileStatus status = graphics_Shader_new(&shader->shader, vertexSrc, fragmentSrc);
    switch (status) {
    case graphics_ShaderCompileStatus_okay:
        break;
    case graphics_ShaderCompileStatus_linkError:
    {
        free(loadedFile1);
        free(loadedFile2);
        free(shader);
        return fh_set_error(prog, "Failed to link shader!");
    }
    case graphics_ShaderCompileStatus_vertexError:
    {
        free(loadedFile1);
        free(loadedFile2);
        free(shader);
        return fh_set_error(prog, "Failed to compile vertex shader!");
    }
    case graphics_ShaderCompileStatus_fragmentError:
    {
        free(loadedFile1);
        free(loadedFile2);
        free(shader);
        return fh_set_error(prog, "Failed to compile fragment shader!");
    }
    }

    free(loadedFile1);
    free(loadedFile2);

    int const textureUnits = shader->shader.textureUnitCount;
    shader->referencedTextures = 0;

    fh_c_obj_gc_callback *callback = shader_gc;
    *ret = fh_new_c_obj(prog, shader, callback, FH_GRAPHICS_SHADER);

    return 0;
}

static int fn_love_graphics_getShader(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_c_obj(prog, moduleData.currentShader, NULL, FH_GRAPHICS_SHADER);
    return 0;
}

static int fn_love_graphics_setShader(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    UNUSED(n_args);
    if (fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)) {
        moduleData.currentShader = fh_get_c_obj_value(&args[0]);
        graphics_setShader(&moduleData.currentShader->shader);
    } else {
        graphics_setDefaultShader();
        moduleData.currentShader = NULL;
    }
    *ret = fh_new_null();
    return 0;
}

static char const vertexName[] = "vertex shader:\n";
static char const fragmentName[] = "\npixel shader:\n";
static char const programName[] = "\nprogram:\n";

static char *pushShaderInfoLog(graphics_Shader const* shader) {
    size_t len = strlen(shader->warnings.fragment)
            + strlen(shader->warnings.vertex)
            + strlen(shader->warnings.program)
            + strlen(vertexName)
            + strlen(fragmentName)
            + strlen(programName);

    char * fullLog = malloc(len + 1);
    strcpy(fullLog, vertexName);
    strcat(fullLog, shader->warnings.vertex);
    strcat(fullLog, fragmentName);
    strcat(fullLog, shader->warnings.fragment);
    strcat(fullLog, programName);
    strcat(fullLog, shader->warnings.program);
    fullLog[len] = '\0';
    return fullLog;
}

static int fn_love_graphics_getShaderWarnings(struct fh_program *prog,
                                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER))
        return fh_set_error(prog, "Expected shader");

    fh_graphics_Shader const* shader = fh_get_c_obj_value(&args[0]);

    char *warning = pushShaderInfoLog(&shader->shader);
    *ret = fh_new_string(prog, warning);
    free(warning);
    return 0;
}

static int fn_love_shader_sendInteger(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 3)
        return fh_set_error(prog, "Expected 3 arguments, got '%d'", n_args);

    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)
            || !fh_is_string(&args[1])
            || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected shader, 'extern' aka uniform name and an integer");

    fh_graphics_Shader *shader = fh_get_c_obj_value(&args[0]);
    const char *name = fh_get_string(&args[1]);

    graphics_ShaderUniformInfo info;
    info.location = glGetUniformLocation(shader->shader.program, name);
   // if (info.location == -1) {
   //     return fh_set_error(prog, "Cannot find extern integer named '%s'", name);
   // }
    info.type = GL_INT;

    int v = (int)args[2].data.num;
    graphics_Shader_sendIntegers(&shader->shader, &info, 1, (GLint*)&v);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_shader_sendFloat(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 3)
        return fh_set_error(prog, "Expected 3 arguments, got '%d'", n_args);

    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)
            || !fh_is_string(&args[1])
            || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected shader, 'extern' aka uniform name and a float");

    fh_graphics_Shader *shader = fh_get_c_obj_value(&args[0]);
    const char *name = fh_get_string(&args[1]);

    graphics_ShaderUniformInfo info;
    info.location = glGetUniformLocation(shader->shader.program, name);
   // if (info.location == -1) {
   //     return fh_set_error(prog, "Cannot find extern float named '%s'", name);
   // }
    info.type = GL_FLOAT;

    float v = (float)args[2].data.num;
    graphics_Shader_sendFloats(&shader->shader, &info, 1, (GLfloat*)&v);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_shader_sendBool(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 3)
        return fh_set_error(prog, "Expected 3 arguments, got '%d'", n_args);

    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)
            || !fh_is_string(&args[1])
            || !fh_is_bool(&args[2]))
        return fh_set_error(prog, "Expected shader, extern' aka uniform name and a bool");

    fh_graphics_Shader *shader = fh_get_c_obj_value(&args[0]);
    const char *name = fh_get_string(&args[1]);

    graphics_ShaderUniformInfo info;
    info.location = glGetUniformLocation(shader->shader.program, name);
    ////if (info.location == -1) {
  //      return fh_set_error(prog, "Cannot find extern variable named '%s'", name);
  //  }
    info.type = GL_BOOL;

    int v = (int)args[2].data.b;
    graphics_Shader_sendBooleans(&shader->shader, &info, 1, (GLint*)&v);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_shader_sendVector(struct fh_program *prog,
                                     struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 3)
        return fh_set_error(prog, "Expected 3 arguments, got '%d'", n_args);

    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)
            || !fh_is_string(&args[1])
            || !fh_is_array(&args[2]))
        return fh_set_error(prog, "Expected shader, 'extern' aka uniform name and a vector");

    fh_graphics_Shader *shader = fh_get_c_obj_value(&args[0]);
    const char *name = fh_get_string(&args[1]);

    graphics_ShaderUniformInfo info;

    info.location = glGetUniformLocation(shader->shader.program, name);
   // if (info.location == -1) {
     //   return fh_set_error(prog, "Cannot find extern vector named '%s'", name);
    //}

    struct fh_array *arr = GET_VAL_ARRAY(&args[2]);

    if (arr->len == 2) {
        info.type = GL_FLOAT_VEC2;
    } else if (arr->len == 3) {
        info.type = GL_FLOAT_VEC3;
    } else if (arr->len == 4) {
        info.type = GL_FLOAT_VEC4;
    } else
        return fh_set_error(prog, "Invalid array length!");

    //float *v = malloc(sizeof(float) * arr->len);
    GLfloat v[arr->len];
    for (uint32_t i = 0; i < arr->len; i++) {
        if (!fh_is_number(&arr->items[i]))
            return fh_set_error(prog, "Expected float got '%s'", fh_type_to_str(prog, arr->items[i].type));
        v[i] = (GLfloat)arr->items[i].data.num;
    }
    graphics_Shader_sendFloatVectors(&shader->shader, &info, 1, v);
    //free(v);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_shader_sendMatrice(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 3)
        return fh_set_error(prog, "Expected 3 arguments, got '%d'", n_args);

    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)
            || !fh_is_string(&args[1])
            || !fh_is_array(&args[2]))
        return fh_set_error(prog, "Expected shader, 'extern' aka uniform name and a vector");

    fh_graphics_Shader *shader = fh_get_c_obj_value(&args[0]);
    const char *name = fh_get_string(&args[1]);

    graphics_ShaderUniformInfo info;
    info.location = glGetUniformLocation(shader->shader.program, name);
    if (info.location == -1) {
        return fh_set_error(prog, "Cannot find extern matrice named '%s'", name);
    }
    info.type = GL_FLOAT;

    struct fh_array *arr = GET_VAL_ARRAY(&args[2]);

    if (arr->len == 2) {
        info.type = GL_FLOAT_MAT2;
    } else if (arr->len == 3) {
        info.type = GL_FLOAT_MAT3;
    } else if (arr->len == 4) {
        info.type = GL_FLOAT_MAT4;
    } else
        return fh_set_error(prog, "Invalid matrix length!");


    float *v = malloc(sizeof(float) * arr->len);
    for (uint32_t i = 0; i < arr->len; i++) {
        if (!fh_is_number(&arr->items[i]))
            return fh_set_error(prog, "Expected float got '%s'", fh_type_to_str(prog, arr->items[i].type));
        v[i] = (float)arr->items[i].data.num;
    }
    graphics_Shader_sendFloatVectors(&shader->shader, &info, 1, (GLfloat*)v);
    free(v);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_shader_sendTexture(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 3)
        return fh_set_error(prog, "Expected 3 arguments, got '%d'", n_args);

    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_SHADER)
            || !fh_is_string(&args[1])
            || !fh_is_c_obj_of_type(&args[2], FH_IMAGE_TYPE))
        return fh_set_error(prog, "Expected shader, extern name and a image");

    fh_graphics_Shader *shader = fh_get_c_obj_value(&args[0]);
    const char *name = fh_get_string(&args[1]);

    fh_image_t *v = fh_get_c_obj_value(&args[2]);

    graphics_ShaderUniformInfo info;
    info.type = GL_SAMPLER_2D;

    info.location = glGetUniformLocation(shader->shader.program, name);
    if (info.location == -1) {
        return fh_set_error(prog, "Cannot find extern variable named '%s'", name);
    }

    if (shader->referencedTextures >= graphics_getMaxTextureUnits())
        return fh_set_error(prog, "Reached maximum number, '%d' of textures per shader", graphics_getMaxTextureUnits());

    shader->shader.textureUnits[shader->referencedTextures++].boundTexture = v->img->texID;
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_getMaxTextureUnits(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    UNUSED(args);
    UNUSED(n_args);
    *ret = fh_new_number(graphics_getMaxTextureUnits());
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newShader),
    DEF_FN(love_graphics_setShader),
    DEF_FN(love_graphics_getShader),
    DEF_FN(love_graphics_getMaxTextureUnits),
    DEF_FN(love_graphics_getShaderWarnings),
    DEF_FN(love_shader_sendFloat),
    DEF_FN(love_shader_sendInteger),
    DEF_FN(love_shader_sendBool),
    DEF_FN(love_shader_sendVector),
    DEF_FN(love_shader_sendMatrice),
    DEF_FN(love_shader_sendTexture),
};

void fh_graphics_shader_register(struct fh_program *prog) {
    moduleData.currentShader = NULL;

    slre_compile(&moduleData.fragmentSingleShaderDetectRegex, fragmentSingleShaderDetectRegexSrc);
    slre_compile(&moduleData.vertexShaderDetectRegex, vertexShaderDetectRegexSrc);

    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
