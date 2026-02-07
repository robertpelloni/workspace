/*
#   clove
#
#   Copyright (C) 2019-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "../include/ui.h"

#include "atlas.inl"

#include "../include/image.h"
#include "../include/imagedata.h"
#include "../include/geometry.h"
#include "../include/graphics.h"
#include "../include/font.h"

#include <string.h>

static struct {
    mu_Context *ctx;
    graphics_Font *font;

    graphics_Image *img;
} moduleData;

static void draw_rect(mu_Rect rect, mu_Color color) {
  graphics_setColor(color.r / 255.0f, color.g / 255.0f,
                    color.b / 255.0f, color.a / 255.0f);
  graphics_geometry_rectangle(true, rect.x, rect.y,
                              rect.w, rect.h,
                              0, 1, 1, 0, 0);
  graphics_setColor(1, 1, 1, 1);
}

static void draw_icon(int id, mu_Rect rect, mu_Color color) {
    mu_Rect src = atlas[id];

  int x = rect.x + (rect.w - src.w) / 2;
  int y = rect.y + (rect.h - src.h) / 2;
  graphics_setColor(color.r / 255.0f, color.g / 255.0f,
                    color.b / 255.0f, color.a / 255.0f);
  graphics_Quad quad;
  graphics_Quad_newWithRef(&quad, src.x, src.y, src.w, src.h, ATLAS_WIDTH, ATLAS_HEIGHT);

  graphics_Image_draw(moduleData.img, &quad, x, y, 0, 1, 1, 0, 0, 0, 0);

  graphics_setColor(1, 1, 1, 1);
}

static void draw_font(mu_TextCommand text, mu_Color color) {
    graphics_setColor(color.r / 255.0f, color.g / 255.0f,
                      color.b / 255.0f, color.a / 255.0f);
    graphics_Font_render(moduleData.font, text.str,
                         text.pos.x, text.pos.y,
                         0, 1, 1, 0, 0, 0, 0);
    graphics_setColor(1, 1, 1, 1);
}

static int text_width(mu_Font font, const char *text, int len) {
	if (len > 0) {
		char t[len];
		strncpy(t, text, len);
		return graphics_Font_getWidth(moduleData.font, t);
	}
	return graphics_Font_getWidth(moduleData.font, text);
}

static int text_height(mu_Font font) {
    return graphics_Font_getHeight(moduleData.font);
}

void ui_init(void) {
    moduleData.ctx = malloc(sizeof (mu_Context));
    mu_init(moduleData.ctx);

    moduleData.font = malloc(sizeof (graphics_Font));
    graphics_Font_new(moduleData.font, NULL, 14);

    // For font alignment and clipping to work correctly
    moduleData.ctx->text_width = text_width;
    moduleData.ctx->text_height = text_height;

    image_ImageData *data = malloc(sizeof(image_ImageData));
    image_ImageData_new_with_surface(data, atlas_texture, ATLAS_WIDTH, ATLAS_HEIGHT, 1);

    graphics_Filter filter;

    moduleData.img = malloc(sizeof(graphics_Image));
    graphics_Image_new_with_ImageData(moduleData.img, data);

    graphics_Image_getFilter(moduleData.img, &filter);
    filter.magMode = graphics_FilterMode_nearest;
    filter.minMode = graphics_FilterMode_nearest;
    filter.maxAnisotropy = 1;

    graphics_Image_setFilter(moduleData.img, &filter);

    graphics_Font_getFilter(moduleData.font, &filter);
    filter.magMode = graphics_FilterMode_nearest;
    filter.minMode = graphics_FilterMode_nearest;
    filter.maxAnisotropy = 1;

    graphics_Font_setFilter(moduleData.font, &filter);

}

void ui_deinit(void) {
    free(moduleData.ctx);
    free(moduleData.font);
    graphics_Image_free(moduleData.img);
    free(moduleData.img);
}

mu_Context *ui_get_context(void) {
    return moduleData.ctx;
}

void ui_layout_row(int no_items, int widths[], int height) {
    mu_layout_row(moduleData.ctx, no_items, widths, height);
}

void ui_layout_begin_column(void) {
    mu_layout_begin_column(moduleData.ctx);
}

void ui_layout_end_column(void) {
    mu_layout_end_column(moduleData.ctx);
}

void ui_layout_set_next(int x, int y,
                        int w, int h,
                        int relative) {
    mu_layout_set_next(moduleData.ctx,
                       mu_rect(x, y, w, h), relative);
}

void ui_layout_width(int width) {
    mu_layout_width(moduleData.ctx, width);
}

mu_Container* ui_get_container(const char *name) {
    return mu_get_container(moduleData.ctx, name);
}

int ui_begin_window(const char* title, mu_Rect rect, int opt) {
    return mu_begin_window_ex(moduleData.ctx, title, rect, opt);
}

void ui_draw_control_text(const char *str, mu_Rect rect, int colorid, int opt) {
    mu_draw_control_text(moduleData.ctx, str, rect, colorid, opt);
}

mu_Rect ui_layout_next(void) {
    return mu_layout_next(moduleData.ctx);
}

void ui_rect(mu_Rect rect, mu_Color color) {
    mu_draw_rect(moduleData.ctx, rect, color);
}

int ui_button(const char* label, int opt) {
    return mu_button_ex(moduleData.ctx, label, 0, opt);
}

int ui_checkbox(const char *label, int state) {
    return mu_checkbox(moduleData.ctx, label, &state);
}

void ui_text(const char *text) {
    mu_text(moduleData.ctx, text);
}

int ui_textbox(char* label, int len, int opt) {
    return mu_textbox_ex(moduleData.ctx, label, len, opt);
}

int ui_header(const char *label, int opt) {
    return mu_header_ex(moduleData.ctx, label, opt);
}

int ui_begin_tree(const char *label, int opt) {
    return mu_begin_treenode_ex(moduleData.ctx, label, opt);
}

void ui_end_tree(void) {
    mu_end_treenode(moduleData.ctx);
}

void ui_label(const char *label, int opt) {
    mu_label(moduleData.ctx, label);
}

void ui_draw_rect(int x, int y, int w, int h,
                  int r, int g, int b, int a) {
    mu_draw_rect(moduleData.ctx, mu_rect(x, y, w, h),
                 mu_color(r, g, b, a));
}

void ui_begin_panel(mu_Container *cnt, const char *name, int opt) {
    mu_begin_panel_ex(moduleData.ctx, name, opt);
}

void ui_open_popup(const char *name) {
    mu_open_popup(moduleData.ctx, name);
}

void ui_end_panel(void) {
    mu_end_panel(moduleData.ctx);
}

int ui_begin_popup(const char *name) {
    return mu_begin_popup(moduleData.ctx, name);
}

void ui_end_popup(void) {
    mu_end_popup(moduleData.ctx);
}

mu_Real ui_slider(mu_Real value, int low, int high, int step, int opt) {
  return mu_slider_ex(moduleData.ctx, &value, low, high, step, MU_SLIDER_FMT, opt);
}

void ui_end_window(void) {
    mu_end_window(moduleData.ctx);
}

void ui_begin(void) {
    mu_begin(moduleData.ctx);
}

void ui_end(void) {
    mu_end(moduleData.ctx);
}

void ui_draw(void) {
	graphics_clearScissor();
	mu_Command *cmd = NULL;
	while (mu_next_command(moduleData.ctx, &cmd)) {
		switch (cmd->type) {
			case MU_COMMAND_TEXT: draw_font(cmd->text, cmd->text.color); break;
			case MU_COMMAND_RECT: draw_rect(cmd->rect.rect, cmd->rect.color); break;;
			case MU_COMMAND_ICON: draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
			case MU_COMMAND_CLIP: graphics_setScissor(cmd->clip.rect.x,
										  graphics_getHeight() - (cmd->clip.rect.y + cmd->clip.rect.h),
										  cmd->clip.rect.w, cmd->clip.rect.h); break;

		}

	}
}

void ui_input_mouse_move(int x, int y) {
    mu_input_mousemove(moduleData.ctx, x, y);
}

void ui_input_mouse_down(int btn, int x, int y) {
    mu_input_mousedown(moduleData.ctx, x, y, btn);
}

void ui_input_mouse_up(int btn, int x, int y) {
    mu_input_mouseup(moduleData.ctx, x, y, btn);
}

void ui_input_text(const char *txt) {
    mu_input_text(moduleData.ctx, txt);
}

void ui_input_scroll(int x, int y) {
    mu_input_scroll(moduleData.ctx, x, y);
}

void ui_input_keydown(int key) {
    mu_input_keydown(moduleData.ctx, key);
}

void ui_input_keyup(int key) {
    mu_input_keyup(moduleData.ctx, key);
}
