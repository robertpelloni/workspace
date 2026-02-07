/*
#   clove
#
#   Copyright (C) 2016-2025 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include <stdlib.h>
#include <stddef.h>

#include "../include/utils.h"
#include "../include/batch.h"
#include "../include/graphics.h"

static struct {
	GLuint sharedIndexBuffer;
	uint16_t *sharedIndexBufferData;
	int indexBufferSize;
	mat4x4 tr2d;
	mat3x3 transform;
} moduleData;

static void graphics_Batch_uploadIfDirty(graphics_Batch *batch);

static void graphics_batch_makeIndexBuffer(int quadCount) {
	if (quadCount <= moduleData.indexBufferSize) {
		return;
	}

	// Round up to multiple of 128
	quadCount = (quadCount + 127) & ~127;

	size_t indexCount = quadCount * 6;
	size_t sizeBytes = indexCount * sizeof(uint16_t);

	uint16_t *newData = realloc(moduleData.sharedIndexBufferData, sizeBytes);
	if (!newData) {
		return;
	}

	moduleData.sharedIndexBufferData = newData;
	for (int i = moduleData.indexBufferSize; i < quadCount; ++i) {
		moduleData.sharedIndexBufferData[6 * i] = 4 * i;
		moduleData.sharedIndexBufferData[6 * i + 1] = 4 * i + 1;
		moduleData.sharedIndexBufferData[6 * i + 2] = 4 * i + 2;
		moduleData.sharedIndexBufferData[6 * i + 3] = 4 * i + 2;
		moduleData.sharedIndexBufferData[6 * i + 4] = 4 * i + 1;
		moduleData.sharedIndexBufferData[6 * i + 5] = 4 * i + 3;
	}

	graphics_bindDefaultVao();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.sharedIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeBytes, moduleData.sharedIndexBufferData, GL_STATIC_DRAW);

	// Leave the EBO bound on the default VAO. Unbinding here can be surprising and isn't needed.
	glBindVertexArray(0);

	moduleData.indexBufferSize = quadCount;
}

void graphics_batch_init(void) {
	glGenBuffers(1, &moduleData.sharedIndexBuffer);
	moduleData.sharedIndexBufferData = NULL;
	moduleData.indexBufferSize = 0;
	graphics_batch_makeIndexBuffer(128);
}

void graphics_Batch_changeBufferSize(graphics_Batch *batch, int newSize) {
	SAFE_FREE(batch->vertexData);
	batch->vertexData = malloc(4 * newSize * sizeof(graphics_Vertex));
	if (batch->vbo == 0) {
		glGenBuffers(1, &batch->vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * newSize * sizeof(graphics_Vertex), NULL, (GLenum) batch->usage);
	batch->maxCount = newSize;
	batch->insertPos = 0;

	graphics_batch_makeIndexBuffer(newSize);
}


void graphics_Batch_new(graphics_Batch *batch, graphics_Image const *texture, int maxSize, graphics_BatchUsage usage) {
	// Safety: make sure the shared index buffer is created before any batch VAO tries to reference it.
	if (moduleData.sharedIndexBuffer == 0) {
		graphics_batch_init();
	}
	batch->texture = texture;
	batch->vertexData = malloc(4 * maxSize * sizeof(graphics_Vertex));
	batch->maxCount = maxSize;
	batch->insertPos = 0;
	batch->dirty = false;
	batch->usage = usage;

	// IMPORTANT: asigură EBO mare pentru maxSize quads
	graphics_batch_makeIndexBuffer(maxSize);

	glGenVertexArrays(1, &batch->vao);
	glBindVertexArray(batch->vao);

	glGenBuffers(1, &batch->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * maxSize * sizeof(graphics_Vertex), NULL, usage);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex),
	                      (void *) offsetof(graphics_Vertex, pos));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex),
	                      (void *) offsetof(graphics_Vertex, uv));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex),
	                      (void *) offsetof(graphics_Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.sharedIndexBuffer);
	glBindVertexArray(0);

	batch->bound = false;
	batch->colorSet = false;
	batch->colorUsed = false;
	batch->color.x = batch->color.y = batch->color.z = batch->color.w = 1.0f;
}

static const vec2 batchQuadPts[4] = {
	{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}
};

int graphics_Batch_add(graphics_Batch *batch, graphics_Quad const *q, float x, float y, float r, float sx, float sy,
                       float ox, float oy, float kx, float ky) {
	if (batch->insertPos == batch->maxCount) {
		clove_error("[BATCH ADD] FAILED insertPos=%d max=%d\n", batch->insertPos, batch->maxCount);
		return -1;
	}

	m3x3_newTransform2d(&moduleData.transform, x, y, r, sx, sy, ox, oy, kx, ky,
	                    q->w * batch->texture->width, q->h * batch->texture->height);

	graphics_Vertex *v = batch->vertexData + 4 * batch->insertPos;

	for (int i = 0; i < 4; ++i) {
		m3x3_mulV2(&v[i].pos, &moduleData.transform, batchQuadPts + i);
		v[i].color = batch->color;
	}

	batch->colorUsed |= batch->colorSet;

	v[0].uv.x = q->x;
	v[0].uv.y = q->y;
	v[1].uv.x = q->x;
	v[1].uv.y = q->y + q->h;
	v[2].uv.x = q->x + q->w;
	v[2].uv.y = q->y;
	v[3].uv.x = q->x + q->w;
	v[3].uv.y = q->y + q->h;

	batch->dirty = true;

	return batch->insertPos++;
}


void graphics_Batch_set(graphics_Batch *batch, int id, graphics_Quad const *q, float x, float y, float r, float sx,
                        float sy, float ox, float oy, float kx, float ky) {
	if (id >= batch->insertPos)
		return;

	mat3x3 transform;
	m3x3_newTransform2d(&transform, x, y, r, sx, sy, ox, oy, kx, ky, q->w * batch->texture->width,
	                    q->h * batch->texture->height);

	graphics_Vertex *v = batch->vertexData + 4 * id;

	for (int i = 0; i < 4; ++i) {
		m3x3_mulV2(&v[i].pos, &transform, batchQuadPts + i);
		float *c = (float *) (&v[i].color);
		for (int j = 0; j < 4; ++j)
			c[j] = 1.0f;
	}

	v[0].uv.x = q->x;
	v[0].uv.y = q->y;
	v[1].uv.x = q->x;
	v[1].uv.y = q->y + q->h;
	v[2].uv.x = q->x + q->w;
	v[2].uv.y = q->y;
	v[3].uv.x = q->x + q->w;
	v[3].uv.y = q->y + q->h;

	if (batch->bound) {
		batch->dirty = true;
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
		glBufferSubData(GL_ARRAY_BUFFER,
		                (GLintptr) (id * 4 * sizeof(graphics_Vertex)),
		                (GLsizeiptr) (4 * sizeof(graphics_Vertex)),
		                v);
	}
}

static const graphics_Quad fullQuad = {
	0.0f, 0.0f, 1.0f, 1.0f
};

void graphics_Batch_draw(graphics_Batch *batch,
                         float x, float y, float r, float sx, float sy,
                         float ox, float oy, float kx, float ky) {
	if (batch->insertPos == 0) return;

	graphics_batch_makeIndexBuffer(batch->insertPos);

	glBindVertexArray(batch->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.sharedIndexBuffer);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, batch->texture->texID);

	graphics_Batch_uploadIfDirty(batch);

	m4x4_newTransform2d(&moduleData.tr2d, x, y, r, sx, sy, ox, oy, kx, ky);

	graphics_drawBatch(&fullQuad, &moduleData.tr2d,
	                   batch->insertPos * 6,
	                   GL_TRIANGLES, GL_UNSIGNED_SHORT,
	                   (float *) &batch->color, 1.0f, 1.0f);

	glBindVertexArray(0);
}

static void graphics_Batch_uploadIfDirty(graphics_Batch *batch) {
	if (!batch->dirty) return;

	const GLsizeiptr totalCapacityBytes =
			(GLsizeiptr) (4 * batch->maxCount * sizeof(graphics_Vertex));

	const GLsizeiptr usedBytes =
			(GLsizeiptr) (4 * batch->insertPos * sizeof(graphics_Vertex));

	glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);

	// ORPHANING: evită stall dacă GPU încă folosește bufferul vechi
	glBufferData(GL_ARRAY_BUFFER, totalCapacityBytes, NULL, (GLenum) batch->usage);

	if (usedBytes > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, usedBytes, batch->vertexData);
	}

	batch->dirty = false;
}


void graphics_Batch_bind(graphics_Batch *batch) {
	batch->bound = true;
}

void graphics_Batch_clear(graphics_Batch *batch) {
	batch->insertPos = 0;
	batch->colorUsed = false;
	batch->dirty = false;
}

void graphics_Batch_flush(graphics_Batch *batch) {
	graphics_Batch_uploadIfDirty(batch);
}

void graphics_Batch_unbind(graphics_Batch *batch) {
	if (!batch->bound) return;
	graphics_Batch_flush(batch);
	batch->bound = false;
}

void graphics_Batch_setColor(graphics_Batch *batch, float r, float g, float b, float a) {
	batch->color.x = r;
	batch->color.y = g;
	batch->color.z = b;
	batch->color.w = a;
	batch->colorSet = true;
}

void graphics_Batch_clearColor(graphics_Batch *batch) {
	batch->color.x = 1.0f;
	batch->color.y = 1.0f;
	batch->color.z = 1.0f;
	batch->color.w = 1.0f;
	batch->colorSet = false;
}

void graphics_Batch_free(graphics_Batch *batch) {
	if (batch->vao != 0) {
		glDeleteVertexArrays(1, &batch->vao);
		batch->vao = 0;
	}
	if (batch->vbo != 0) {
		glDeleteBuffers(1, &batch->vbo);
		batch->vbo = 0;
	}

	SAFE_FREE(batch->vertexData);
}

void graphics_Batch_shutdown() {
	if (moduleData.sharedIndexBuffer) {
		glDeleteBuffers(1, &moduleData.sharedIndexBuffer);
		moduleData.sharedIndexBuffer = 0;
	}
	SAFE_FREE(moduleData.sharedIndexBufferData);
	moduleData.indexBufferSize = 0;
}
