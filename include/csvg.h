/*
 * C Scalable Vector Graphics (CSVG) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 */

#ifndef CSVG_H
#define CSVG_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FONT_WEIGHT_THIN        100
#define FONT_WEIGHT_EXTRA_LIGHT 200
#define FONT_WEIGHT_LIGHT       300
#define FONT_WEIGHT_NORMAL      400
#define FONT_WEIGHT_MEDIUM      500
#define FONT_WEIGHT_SEMI_BOLD   600
#define FONT_WEIGHT_BOLD        700
#define FONT_WEIGHT_EXTRA_BOLD  800
#define FONT_WEIGHT_BLACK       900

typedef struct _SVG  SVG;
typedef enum   _bool bool;

enum _bool
{
   F = 0,
   T = ( ! 0 )
};

struct _SVG
{
   FILE *file;
   int   width;
   int   height;
};

SVG *svg_init( const char* filename, int width, int height );
void svg_set_background( SVG *svg, unsigned long hexColor );
void svg_close( SVG *svg );

void svg_rect( SVG *svg, int x, int y, int width, int height, int stroke_width, unsigned int color );
void svg_filled_rect( SVG *svg, int x, int y, int width, int height, unsigned int color );

void svg_triangle( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, int stroke_width, unsigned int color );
void svg_filled_triangle( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color );

void svg_circle( SVG *svg, int cx, int cy, int r, int stroke_width, unsigned int color );
void svg_filled_circle( SVG *svg, int cx, int cy, int r, unsigned int color );

void svg_line( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, unsigned int color );
void svg_polyline( SVG *svg, int *points, int point_count, int stroke_width, unsigned int color );

void svg_arrow( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, unsigned int color );
void svg_numbered_arrow( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, int start_num, int end_num, int step, unsigned int color );
void svg_numbered_arrow_xy( SVG *svg, int x1, int y1, int x2, int y3, int stroke_width, int start_num, int end_num, int step, unsigned int color );

void svg_hexagon( SVG *svg, int hx, int hy, int r, int stroke_width, bool type, unsigned int color );
void svg_filled_hexagon( SVG *svg, int hx, int hy, int r, bool type, unsigned int color );

void svg_ellipse( SVG *svg, int cx, int cy, int rx, int ry, int stroke_width, unsigned int color );
void svg_filled_ellipse( SVG *svg, int cx, int cy, int rx, int ry, unsigned int fill_color );

void svg_bezier_curve( SVG *svg, int *points, int point_count, int stroke_width, unsigned int color );

void svg_text( SVG *svg, int x, int y, const char *text, const char *font, int size, int font_weight, unsigned int color );

void svg_linear_gradient( SVG *svg, const char *id, unsigned int startColor, unsigned int endColor, float x1, float y1, float x2, float y2 );
void svg_triangle_linear_gradient( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int startColor, unsigned int endColor );

void svg_radial_gradient( SVG *svg, const char *id, unsigned int innerColor, unsigned int outerColor, float cx, float cy, float r );
void svg_triangle_radial_gradient( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int startColor, unsigned int endColor );

void svg_rect_gradient( SVG *svg, int x, int y, int width, int height, const char *gradient_id );
void svg_circle_gradient( SVG *svg, int cx, int cy, int r, const char *gradient_id );

#endif /* CSVG_H */
