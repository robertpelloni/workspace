/*
#   clove
#
#   Copyright (C) 2019-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/microui/src/microui.h"

void ui_init(void);
void ui_deinit(void);
mu_Context *ui_get_context(void);

void ui_layout_row(int no_items, int widths[], int height);
void ui_layout_begin_column(void);
void ui_layout_end_column(void);

void ui_layout_width(int width);
void ui_layout_set_next(int x, int y,
                        int w, int h,
                        int relative);
mu_Container* ui_get_container(const char *name);

void ui_init_window(mu_Container *ctn, int x, int y, int w, int h);
int ui_begin_window(const char *title, mu_Rect rect, int opt);
void ui_end_window(void);

void ui_draw_control_text(const char *str, mu_Rect rect, int colorid, int opt);
mu_Rect ui_layout_next(void);
void ui_rect(mu_Rect rect, mu_Color color);
int ui_checkbox(const char *label, int state);
void ui_text(const char *text);
int ui_button(const char* label, int opt);
int ui_textbox(char* label, int len, int opt);
int ui_header(const char *label, int opt);
void ui_label(const char *label, int opt);
mu_Real ui_slider(mu_Real value, int low, int high, int step, int opt);
int ui_begin_tree(const char *label, int opt);
void ui_end_tree(void);
void ui_draw_rect(int x, int y, int w, int h,
                  int r, int g, int b, int a);
void ui_begin_panel(mu_Container *cnt, const char *name, int opt);
void ui_end_panel(void);
void ui_open_popup(const char *name);
int ui_begin_popup(const char *name);
void ui_end_popup(void);

void ui_begin(void);
void ui_end(void);
void ui_draw(void);

void ui_input_mouse_move(int x, int y);
void ui_input_mouse_down(int btn, int x, int y);
void ui_input_mouse_up(int btn, int x, int y);
void ui_input_text(const char *txt);
void ui_input_scroll(int x, int y);
void ui_input_keydown(int key);
void ui_input_keyup(int key);
