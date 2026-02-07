/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "../include/gltools.h"
#include "../include/gl.h"
#include "../include/minmax.h"

void graphics_Texture_setFilter(GLuint texID, graphics_Filter *filter) {
	glBindTexture(GL_TEXTURE_2D, texID);

	// Keep textures "complete" on strict drivers (macOS core profile).
	// These are safe defaults and can be overridden elsewhere if needed.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Always start from base level 0.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);

	// If mipmaps are requested, only generate them when level 0 is actually defined.
	GLint level0w = 0;
	GLint level0h = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &level0w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &level0h);

	int minFilter = GL_NEAREST;

	// If mipmaps are requested but the texture has no level-0 storage yet,
	// fall back to non-mipmap filtering to avoid incomplete/unloadable textures.
	bool hasLevel0 = (level0w > 0 && level0h > 0);
	bool wantMipmaps = (filter->mipmapMode != graphics_FilterMode_none);

	if (!wantMipmaps || !hasLevel0) {
		// No mipmaps (or can't build them yet)
		switch (filter->minMode) {
			case graphics_FilterMode_linear:
				minFilter = GL_LINEAR;
				break;
			case graphics_FilterMode_nearest:
			default:
				minFilter = GL_NEAREST;
				break;
		}

		// Force max level to 0 so the texture is complete.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	} else {
		// Mipmaps enabled and level 0 exists.
		if (filter->mipmapMode == graphics_FilterMode_nearest) {
			switch (filter->minMode) {
				case graphics_FilterMode_linear:
					minFilter = GL_LINEAR_MIPMAP_NEAREST;
					break;
				case graphics_FilterMode_nearest:
				default:
					minFilter = GL_NEAREST_MIPMAP_NEAREST;
					break;
			}
		} else {
			// graphics_FilterMode_linear
			switch (filter->minMode) {
				case graphics_FilterMode_linear:
					minFilter = GL_LINEAR_MIPMAP_LINEAR;
					break;
				case graphics_FilterMode_nearest:
				default:
					minFilter = GL_NEAREST_MIPMAP_LINEAR;
					break;
			}
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		// Set a sane max mip level based on the current size.
		GLint m = level0w > level0h ? level0w : level0h;
		GLint maxLevel = 0;
		while (m > 1) {
			m >>= 1;
			maxLevel++;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, maxLevel);
	}

	int magFilter = (filter->magMode == graphics_FilterMode_linear) ? GL_LINEAR : GL_NEAREST;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	/*
	 * Not supported by WebGL, still interesting for native builds.
	 * Accept GL_INVALID_ENUM on WebGL
	 */
#ifndef EMSCRIPTEN
	if (filter->mipmapMode != graphics_FilterMode_none) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, filter->mipmapLodBias);
	}
#endif

	/*
	 * https://www.khronos.org/opengl/wiki/Sampler_Object
	 * Note: Though this feature only became core in OpenGL 4.6, it is widely available through the EXT_texture_filter_anisotropic extension.
	 */
	if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic") || GLEW_EXT_texture_filter_anisotropic) {
		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		// GL_TEXTURE_MAX_ANISOTROPY does not accept values less than 1.0f!
		GLfloat anisotropy = clampf(filter->maxAnisotropy, 1.0f, fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
	}
}

float graphics_Texture_getMaxAnisotropy(void) {
	if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic") || GLEW_EXT_texture_filter_anisotropic) {
		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		return fLargest;
	}
	return 1.0f;
}

void graphics_Texture_getFilter(GLuint texID, graphics_Filter *filter) {
	glBindTexture(GL_TEXTURE_2D, texID);
	// Ensure we query from base level 0.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	int fil;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &fil);
	switch (fil) {
		case GL_NEAREST:
			filter->minMode = graphics_FilterMode_nearest;
			filter->mipmapMode = graphics_FilterMode_none;
			break;
		case GL_LINEAR:
			filter->minMode = graphics_FilterMode_linear;
			filter->mipmapMode = graphics_FilterMode_none;
			break;
		case GL_NEAREST_MIPMAP_NEAREST:
			filter->minMode = graphics_FilterMode_nearest;
			filter->mipmapMode = graphics_FilterMode_nearest;
			break;
		case GL_NEAREST_MIPMAP_LINEAR:
			filter->minMode = graphics_FilterMode_nearest;
			filter->mipmapMode = graphics_FilterMode_linear;
			break;
		case GL_LINEAR_MIPMAP_NEAREST:
			filter->minMode = graphics_FilterMode_linear;
			filter->mipmapMode = graphics_FilterMode_nearest;
			break;
		case GL_LINEAR_MIPMAP_LINEAR:
			filter->minMode = graphics_FilterMode_linear;
			filter->mipmapMode = graphics_FilterMode_linear;
			break;
	}

#ifndef EMSCRIPTEN
	if (filter->mipmapMode == graphics_FilterMode_none) {
#endif
		filter->mipmapLodBias = 0.0f;
#ifndef EMSCRIPTEN
	} else {
		glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, &filter->mipmapLodBias);
	}
#endif

	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &fil);

	filter->magMode = (fil == GL_LINEAR) ? graphics_FilterMode_linear : graphics_FilterMode_nearest;

	if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic") || GLEW_EXT_texture_filter_anisotropic) {
		glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, &filter->maxAnisotropy);
	} else {
		filter->maxAnisotropy = 1.0f;
	}
}
