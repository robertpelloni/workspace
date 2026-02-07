#include "../include/canvas.h"
#include "../include/graphics.h"
#include "../include/vertex.h"

#include <stdlib.h>

static graphics_Vertex const imageData[] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
};

static unsigned char const imageIndices[] = { 0, 1, 2, 3 };

// This is the actual quad onto which we draw our texture.
static void setup_quad(graphics_Canvas* c) {
    glGenBuffers(1, &c->image.vbo);
    glGenBuffers(1, &c->image.ibo);

    glBindBuffer(GL_ARRAY_BUFFER, c->image.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(imageData), imageData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->image.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(imageIndices), imageIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex), (GLvoid const*)(2*sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex), (GLvoid const*)(4*sizeof(float)));
}

void graphics_Canvas_new(graphics_Canvas *c, int width, int height) {
	setup_quad(c);

	glGenFramebuffers(1, &c->fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, c->fbo);
	// create a color attachment texture
	glGenTextures(1, &c->image.texID);
	glBindTexture(GL_TEXTURE_2D, c->image.texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, c->image.texID, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		clove_error("%s\n", "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	c->image.width = width;
	c->image.height = height;
}

void graphics_Canvas_free(graphics_Canvas *canvas) {
	graphics_Image_free(&canvas->image);
	glDeleteFramebuffers(1, &canvas->fbo);
}

void graphics_Canvas_draw(graphics_Canvas const* canvas, graphics_Quad const* quad,
                         float x, float y, float r, float sx, float sy,
                         float ox, float oy, float kx, float ky) {
  graphics_Image_draw(&canvas->image, quad, x, y, r, sx, sy, ox, oy, kx, ky);
}

void graphics_setCanvas(graphics_Canvas* canvas) {
	if (canvas != NULL) {
		int width = canvas->image.width;
		int height = canvas->image.height;
		glBindFramebuffer(GL_FRAMEBUFFER, canvas->fbo);
		glViewport(0, 0, width, height);
		graphics_set_camera_2d(0, width, 0, height, 0.1f, 100.0f);
	} else {
		int width = graphics_getWidth();
		int height = graphics_getHeight();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
		graphics_set_camera_2d(0, width, height, 0, 0.1f, 100.0f);
	}
}
