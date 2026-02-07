/*
#   clove
#   Copyright (C) 2017-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "game.h"

#include "../src/3rdparty/SDL2/include/SDL.h"
#include <stdio.h>

#include <stdbool.h>
#include <stdio.h>

#include "../src/include/graphics.h"
#include "../src/include/geometry.h"
#include "../src/include/matrixstack.h"
#include "../src/include/keyboard.h"
#include "../src/include/canvas.h"
#include "../src/include/ui.h"

//#define NANOSVG_IMPLEMENTATION
//#include "../src/include/nanosvg.h"

//NSVGimage* image;

/*
static const graphics_Quad defaultQuad = {
    .x = 0.0f,
    .y = 0.0f,
    .w = 1.0f,
    .h = 1.0f
};

graphics_Canvas c;
graphics_Canvas c2;
float x= 0;
*/

void game_load(void) {
/*
    graphics_Canvas_new(&c, 400, 200);
    graphics_Canvas_new(&c2, 800, 600);

    graphics_setCanvas(&c);
    graphics_setBackgroundColor(.2f, .6f, .5f, 1);
    graphics_setColor(0.6f, 0.5f, 1.0f, 1);
    graphics_clear();
    graphics_setBlendMode(graphics_BlendMode_alpha);
    graphics_geometry_fillCircle(10, 120, 32, 12, 0, 1, 1, 0, 0);
    graphics_setCanvas(NULL);
*/
    //printf("HELLO GAME.C\n");
    //image = nsvgParseFromFile("23.svg", "px", 96.0f);
    //if (image == NULL) {
      //  printf("COULD NOT LOAD SVG IMAGE");
    //}
}

void game_update(float delta) {
/*
    graphics_setCanvas(&c);
        graphics_setBackgroundColor(.9f, .1f, .2f, 1);
        graphics_setColor(0.6f, 1, 1.0f, .5f);
        graphics_clear();
        graphics_geometry_fillCircle(x, 120, 32, 12, 0, 1, 1, 0, 0);
        x += 100 *delta;
    graphics_setCanvas(NULL);

    graphics_setCanvas(&c2);
        graphics_setBackgroundColor(.8f, .6f, .5f, 1);
        graphics_setColor(1.0f, 1.0f, 1.0f, 1);
        graphics_clear();
        graphics_geometry_rectangle(true, 400, 200, 32, 32, 0, 1, 1, 0, 0);
    graphics_setCanvas(NULL);
*/
}

static float distPtSeg(float x, float y, float px, float py, float qx, float qy)
{
    float pqx, pqy, dx, dy, d, t;
    pqx = qx-px;
    pqy = qy-py;
    dx = x-px;
    dy = y-py;
    d = pqx*pqx + pqy*pqy;
    t = pqx*dx + pqy*dy;
    if (d > 0) t /= d;
    if (t < 0) t = 0;
    else if (t > 1) t = 1;
    dx = px + t*pqx - x;
    dy = py + t*pqy - y;
    return dx*dx + dy*dy;
}

static void cubicBez(float x1, float y1, float x2, float y2,
                     float x3, float y3, float x4, float y4,
                     float tol, int level)
{
    float x12,y12,x23,y23,x34,y34,x123,y123,x234,y234,x1234,y1234;
    float d;

    if (level > 12) return;

    x12 = (x1+x2)*0.5f;
    y12 = (y1+y2)*0.5f;
    x23 = (x2+x3)*0.5f;
    y23 = (y2+y3)*0.5f;
    x34 = (x3+x4)*0.5f;
    y34 = (y3+y4)*0.5f;
    x123 = (x12+x23)*0.5f;
    y123 = (y12+y23)*0.5f;
    x234 = (x23+x34)*0.5f;
    y234 = (y23+y34)*0.5f;
    x1234 = (x123+x234)*0.5f;
    y1234 = (y123+y234)*0.5f;

    d = distPtSeg(x1234, y1234, x1,y1, x4,y4);
    if (d > tol*tol) {
        cubicBez(x1,y1, x12,y12, x123,y123, x1234,y1234, tol, level+1);
        cubicBez(x1234,y1234, x234,y234, x34,y34, x4,y4, tol, level+1);
    } else {
//        graphics_geometry_points(x4, y4);
        float arr[4] = {x1, y2, x4, y4};
        graphics_geometry_line(arr, 2);

    }
}

void drawPath(float* pts, int npts, char closed, float tol)
{
    int i;
//    graphics_geometry_points(pts[0], pts[1]);
    float arr[4] = {pts[0], pts[1], pts[2], pts[3]};
    graphics_geometry_line(arr, 2);
    for (i = 0; i < npts-1; i += 3) {
        float* p = &pts[i*2];
        cubicBez(p[0],p[1], p[2],p[3], p[4],p[5], p[6],p[7], tol, 0);
    }
    if (closed) {
 //       graphics_geometry_points(pts[0], pts[1]);
        float arr[4] = {pts[0], pts[1], pts[2], pts[3]};
        graphics_geometry_line(arr, 2);
    }
}


void game_draw(void) {
/*
    graphics_Canvas_draw(&c2, &defaultQuad, 0, 0, 0, 1, 1, 0, 0, 0, 0);
    graphics_Canvas_draw(&c, &defaultQuad, 0, 0, 0, 1, 1, 0, 0, 0, 0);

    graphics_setColor(0.2f, 0.2f, 0.2f, 1);
    graphics_geometry_rectangle(true, 400, 400, 64, 64, 0, 1, 1, 0, 0);
*/
    //graphics_setColor(0.2f, 0.2f, 0.2f, 1);
    //graphics_geometry_rectangle(true, 400, 400, 64, 64, 0, 1, 1, 0, 0);

    //NSVGshape* shape;
    //NSVGpath* path;

    //for (shape = image->shapes; shape != NULL; shape = shape->next) {
      //  for (path = shape->paths; path != NULL; path = path->next) {
        //    drawPath(path->pts, path->npts, path->closed, 700);
        //}
    //}

}

void game_quit(void) {
    //nsvgDelete(image);
}
