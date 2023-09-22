/*
 * Copyright 2023 Rafał Jopek ( rafaljopek at hotmail com )
 */

#ifndef CSVG_H
#define CSVG_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum bool
{
   F = 0,
   T = ( ! 0 )
} bool;

typedef struct
{
   FILE *file;
   int width;
   int height;
} SVG;

SVG *svg_init( const char* filename, int width, int height );
void svg_set_background( SVG *svg, unsigned int color );
void svg_close( SVG *svg );

void svg_rect( SVG *svg, int x, int y, int width, int height, int stroke_width, unsigned int color );
void svg_filled_rect( SVG *svg, int x, int y, int width, int height, unsigned int color );

void svg_triangle( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, int stroke_width, unsigned int color );
void svg_filled_triangle( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color );

void svg_circle( SVG *svg, int cx, int cy, int r, int stroke_width, unsigned int color );
void svg_filled_circle( SVG *svg, int cx, int cy, int r, unsigned int color );

void svg_line( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, unsigned int color );

void svg_hexagon( SVG *svg, int hx, int hy, int r, int stroke_width, bool type, unsigned int color );
void svg_filled_hexagon( SVG *svg, int hx, int hy, int r, bool type, unsigned int color );

void svg_ellipse( SVG *svg, int cx, int cy, int rx, int ry, int stroke_width, unsigned int color );
void svg_filled_ellipse( SVG *svg, int cx, int cy, int rx, int ry, unsigned int fill_color );

void svg_text( SVG *svg, int x, int y, const char *text, const char *font, int size, unsigned int color );

#endif /* CSVG_H */