/*
 * Copyright 2023 Rafał Jopek ( rafaljopek at hotmail com )
 */

#include "csvg.h"

SVG *svg_init( const char *filename, int width, int height )
{
   SVG *svg = malloc( sizeof( SVG ) );
   if( svg == NULL )
   {
      fprintf( stderr, "Error: Could not allocate memory for SVG structure.\n" );
      return NULL; // Return NULL to indicate failure
    }

   svg->file = fopen( filename, "w" );
   if( svg->file == NULL )
   {
      fprintf( stderr, "Error: Could not open file '%s' for writing.\n", filename );
      free( svg ); // Don't forget to free the previously allocated memory
      return NULL; // Return NULL to indicate failure
   }

   svg->width = width;
   svg->height = height;

   fprintf( svg->file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" );
   fprintf( svg->file, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " );
   fprintf( svg->file, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n" );
   fprintf( svg->file, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\">\n", svg->width, svg->height, svg->width, svg->height );

   return svg;
}

void svg_set_background( SVG *svg, unsigned int color )
{
   svg_filled_rect( svg, 0, 0, svg->width, svg->height, color );
}

void svg_close( SVG *svg )
{
   if( svg )
   {
      fprintf( svg->file, "</svg>" );
      fclose( svg->file );
      free( svg );
   }
   else 
   {
      fprintf( stderr, "Error: svg_close called with NULL SVG pointer.\n" );
      return; // Do nothing if SVG is NULL 
   }
}

void svg_rect( SVG *svg, int x, int y, int width, int height, int stroke_width, unsigned int color )
{
   fprintf( svg->file, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke-width=\"%d\" stroke=\"#%06x\" fill=\"none\"/>\n", x, y, width, height, stroke_width, color );
}

void svg_filled_rect( SVG *svg, int x, int y, int width, int height, unsigned int color )
{
   fprintf( svg->file, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"#%06x\"/>\n", x, y, width, height, color );
}

void svg_triangle( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, int stroke_width, unsigned int color )
{
   fprintf( svg->file, "<polygon points=\"%d,%d %d,%d %d,%d\" stroke-width=\"%d\" stroke=\"#%06x\" fill=\"none\"/>\n", x1, y1, x2, y2, x3, y3, stroke_width, color );
}

void svg_filled_triangle( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color )
{
   fprintf( svg->file, "<polygon points=\"%d,%d %d,%d %d,%d\" fill=\"#%06x\"/>\n", x1, y1, x2, y2, x3, y3, color );
}

void svg_circle( SVG *svg, int cx, int cy, int r, int stroke_width, unsigned int color )
{
   fprintf( svg->file, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke-width=\"%d\" stroke=\"#%06x\" fill=\"none\"/>\n", cx, cy, r, stroke_width, color );
}

void svg_filled_circle( SVG *svg, int cx, int cy, int r, unsigned int color )
{
   fprintf( svg->file, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"#%06x\"/>\n", cx, cy, r, color );
}

void svg_line( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, unsigned int color )
{
   fprintf( svg->file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke-width:%d; stroke:#%06x\" />\n", x1, y1, x2, y2, stroke_width, color );
}

void svg_polyline( SVG *svg, int *points, int point_count, int stroke_width, unsigned int color )
{
   if( svg == NULL || points == NULL || point_count < 2 )
      return;

   fprintf( svg->file, "<polyline points=\"" );

   for( int i = 0; i < point_count; ++i )
   {
      fprintf( svg->file, "%d,%d ", points[ 2 * i ], points[ 2 * i + 1 ] );
   }

   fprintf( svg->file, "\" stroke-width=\"%d\" stroke=\"#%06x\" fill=\"none\"/>\n", stroke_width, color );
}

void svg_hexagon( SVG *svg, int hx, int hy, int r, int stroke_width, bool type, unsigned int color )
{
   double a = 2 * M_PI / 6;
   double angle_offset = ( type == 0 ? M_PI_2 : M_PI / 3 ); // Decides the orientation
   double x1 = hx + r * cos( a * 5 + angle_offset );
   double y1 = hy + r * sin( a * 5 + angle_offset );
  
   fprintf( svg->file, "<polygon points=\"%.2lf,%.2lf ", x1, y1 );
  
   for( int i = 0; i < 6; ++i )
   {
      double x = hx + r * cos( a * i + angle_offset );
      double y = hy + r * sin( a * i + angle_offset );
      fprintf( svg->file, "%.2lf,%.2lf ", x, y );
   }

   fprintf( svg->file, "\" stroke-width=\"%d\" stroke=\"#%06x\"", stroke_width, color );
   fprintf( svg->file, " fill=\"none\"/>\n" );
}

void svg_filled_hexagon( SVG *svg, int hx, int hy, int r, bool type, unsigned int color )
{
   double a = 2 * M_PI / 6;
   double angle_offset = ( type == 0 ? M_PI_2 : M_PI / 3 ); // Decides the orientation
   double x1 = hx + r * cos( a * 5 + angle_offset );
   double y1 = hy + r * sin( a * 5 + angle_offset );
  
   fprintf( svg->file, "<polygon points=\"%.2lf,%.2lf ", x1, y1 );
  
   for( int i = 0; i < 6; ++i )
   {
      double x = hx + r * cos( a * i + angle_offset );
      double y = hy + r * sin( a * i + angle_offset );
      fprintf( svg->file, "%.2lf,%.2lf ", x, y );
   }

   fprintf( svg->file, "\" stroke=\"#%06x\" stroke-width=\"1\"", color );
   fprintf( svg->file, " fill=\"#%06x\"/>\n", color );
}

void svg_ellipse( SVG *svg, int cx, int cy, int rx, int ry, int stroke_width, unsigned int color )
{
   fprintf( svg->file, "<ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" stroke=\"#%06x\" stroke-width=\"%d\" fill=\"none\"/>\n", cx, cy, rx, ry, color, stroke_width );
}

void svg_filled_ellipse( SVG *svg, int cx, int cy, int rx, int ry, unsigned int fill_color )
{
   fprintf( svg->file, "<ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" fill=\"#%06x\"/>\n", cx, cy, rx, ry, fill_color );
}

void svg_text( SVG *svg, int x, int y, const char *text, const char *font, int size, unsigned int color )
{
   fprintf( svg->file, "<text x=\"%d\" y=\"%d\" font-family=\"%s\" font-size=\"%d\" fill=\"#%06x\">%s</text>\n", x, y, font, size, color, text );
}
