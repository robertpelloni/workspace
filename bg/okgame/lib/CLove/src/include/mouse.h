/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

void mouse_mousemoved(int x, int y);
int mouse_getwheel();
void mouse_mousewheel(int y);
void mouse_mousepressed(int x, int y, int button);
void mouse_mousereleased(int x, int y, int button);
int mouse_isDown(const char *str);
int mouse_isVisible(void);
void mouse_getPosition(int *x, int *y);
int mouse_getX(void);
int mouse_getY(void);
void mouse_setPosition(int x, int y);
void mouse_setVisible(int b);
void mouse_setX(int x);
void mouse_setY(int y);
void mouse_setButton(int button);
const char *mouse_button_to_str(int x);

