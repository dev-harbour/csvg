/*
 * C Scalable Vector Graphics (CSVG) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
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

void svg_set_background( SVG *svg, unsigned long hexColor )
{
   if( hexColor <= 0xFFFFFF )
   {
      // No alpha channel, use full opacity
      fprintf( svg->file, "<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%06lX\" fill-opacity=\"1\"/>\n", svg->width, svg->height, hexColor );
   }
   else if( hexColor <= 0xFFFFFFFF )
   {
      // Alpha channel is available
      double a = ( hexColor & 0xFF ) / 255.0;
      unsigned int color = ( hexColor >> 8 ) & 0xFFFFFF;
      fprintf( svg->file, "<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%06X\" fill-opacity=\"%f\"/>\n", svg->width, svg->height, color, a );
   }
   else
   {
      fprintf( stderr, "Invalid hex value passed\n" );
   }
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

void svg_arrow( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, unsigned int color )
{
   // Draw a line from ( x1, y1 ) to ( x2, y2 )
   svg_line( svg, x1, y1, x2, y2, stroke_width, color );

   // Calculate the angle of the line
   double angle = atan2( ( double )( y2 - y1 ), ( double )( x2 - x1 ) );

   // Length of the arrow head
   int arrow_length = 10;

   // Angles for the arrow heads
   double angle1 = angle + M_PI / 6.0;
   double angle2 = angle - M_PI / 6.0;

   // Calculate the endpoints for the arrow head
   int x3 = x2 - ( int ) ( arrow_length * cos( angle1 ) );
   int y3 = y2 - ( int ) ( arrow_length * sin( angle1 ) );

   int x4 = x2 - ( int ) ( arrow_length * cos( angle2 ) );
   int y4 = y2 - ( int ) ( arrow_length * sin( angle2 ) );

   // Draw the "head" of the arrow
   svg_line( svg, x2, y2, x3, y3, stroke_width, color );
   svg_line( svg, x2, y2, x4, y4, stroke_width, color );
}

void svg_numbered_arrow( SVG *svg, int x1, int y1, int x2, int y2, int stroke_width, int start_num, int end_num, int step, unsigned int color )
{
   // Drawing an arrow
   svg_arrow( svg, x1, y1, x2, y2, stroke_width, color );

   // Determining the number of labels on the arrow
   int num_labels = ( end_num - start_num ) / step + 1;

   // Determining the spacing between labels on the arrow
   float dx = ( x2 - x1 ) / ( float ) ( num_labels - 1 );
   float dy = ( y2 - y1 ) / ( float ) ( num_labels - 1 );

   // If the arrow is vertical, adjust the label positions
   int label_offset_x = 0;
   int label_offset_y = 15;
   if( x1 == x2 )
   {
      label_offset_x = -20;  // Start with a default offset
      label_offset_y = 0;
   }

   // Adding labels and tick marks
   for( int i = 0; i < num_labels; ++i )
   {
      int x = x1 + dx * i;
      int y = y1 + dy * i;
      int num = start_num + step * i;
      char label[ 10 ];
      sprintf( label, "%d", num );

      // Draw tick mark
      int tick_length = ( i % 5 == 0 ) ? 10 : 5; // Every fifth tick mark is longer
      if( x1 == x2 )
      {
         svg_line( svg, x - tick_length, y, x, y, 1, color );
      }
      else
      {
         svg_line( svg, x, y + tick_length, x, y, 1, color );
      }

      // Adjust the label offset based on the number of digits
      int num_digits = strlen( label );
      if( x1 == x2 )  // Only adjust for vertical arrows
      {
         label_offset_x = -10 * num_digits;  // Assume each digit is about 10 units wide
      }

      // Additional adjustment for values 100 or greater
      if( num >= 100 )
      {
         label_offset_x += 3;
      }

      svg_text( svg, x + label_offset_x, y + label_offset_y, label, "Arial", 12, FONT_WEIGHT_NORMAL, color );
   }
}

void svg_numbered_arrow_xy( SVG *svg, int x1, int y1, int x2, int y3, int stroke_width, int start_num, int end_num, int step, unsigned int color )
{
   // Drawing horizontal arrow
   svg_arrow( svg, x1, y1, x2, y1, stroke_width, color );
   // Drawing vertical arrow
   svg_arrow( svg, x1, y1, x1, y3, stroke_width, color );

   // Determining the number of labels on the arrow
   int num_labels = ( end_num - start_num ) / step + 1;

   // Common adjustments for labels
   int label_offset_x = 0;
   int label_offset_y = 15;

   // Adding labels and tick marks for the horizontal arrow
   float dx = ( x2 - x1 ) / ( float ) ( num_labels - 1 );
   for( int i = 0; i < num_labels; ++i )
   {
      int x = x1 + dx * i;
      int y = y1;
      int num = start_num + step * i;
      char label[ 10 ];
      sprintf( label, "%d", num );

      // Draw tick mark for horizontal arrow
      int tick_length = (i % 5 == 0) ? 10 : 5; // Every fifth tick mark is longer
      svg_line(svg, x, y + tick_length, x, y, 1, color);

      svg_text( svg, x + label_offset_x, y + label_offset_y, label, "Arial", 12, FONT_WEIGHT_NORMAL, color );
   }

   // Adding labels and tick marks for the vertical arrow
   label_offset_x = -20;  // Start with a default offset for vertical labels
   label_offset_y = 0;
   float dy = ( y1 - y3 ) / ( float ) ( num_labels - 1 );
   for( int i = 0; i < num_labels; ++i )
   {
      int x = x1;
      int y = y1 - dy * i;
      int num = start_num + step * i;
      char label[ 10 ];
      sprintf( label, "%d", num );

      // Draw tick mark for vertical arrow
      int tick_length = (i % 5 == 0) ? 10 : 5; // Every fifth tick mark is longer
      svg_line(svg, x - tick_length, y, x, y, 1, color);

      // Adjust the label offset based on the number of digits
      int num_digits = strlen( label );
      label_offset_x = -10 * num_digits;  // Assume each digit is about 10 units wide

      // Additional adjustment for values 100 or greater
      if( num >= 100 )
      {
         label_offset_x += 3;
      }

      if( num != 0 )  // Skip zero for the vertical arrow
      {
         svg_text( svg, x + label_offset_x, y + label_offset_y, label, "Arial", 12, FONT_WEIGHT_NORMAL, color );
      }
   }
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

void svg_bezier_curve( SVG *svg, int *points, int point_count, int stroke_width, unsigned int color )
{
   if( point_count < 4 )
      return; // Bezier curve requires at least 4 points (two control points, start point and end point)

   fprintf( svg->file, "<path d=\"M %d %d ", points[ 0 ], points[ 1 ] );

   for( int i = 2; i < point_count * 2; i += 6 )
   {
      fprintf( svg->file, "C %d %d, %d %d, %d %d ", points[ i ], points[ i + 1 ], points[ i + 2 ], points[ i + 3 ], points[ i + 4 ], points[ i + 5 ] );
   }

   fprintf( svg->file, "\" stroke=\"#%06x\" stroke-width=\"%d\" fill=\"none\"/>\n", color, stroke_width );
}

void svg_text( SVG *svg, int x, int y, const char *text, const char *font, int size, int font_weight, unsigned int color )
{
   fprintf( svg->file, "<text x=\"%d\" y=\"%d\" font-family=\"%s\" font-size=\"%d\" font-weight=\"%d\" fill=\"#%06x\">%s</text>\n", x, y, font, size, font_weight, color & 0xFFFFFF, text );
}

/* Linear gradient */
void svg_linear_gradient( SVG *svg, const char *id, unsigned int startColor, unsigned int endColor, float x1, float y1, float x2, float y2 )
{
   fprintf( svg->file, "<defs>\n" );
   fprintf( svg->file, "<linearGradient id=\"%s\" x1=\"%f%%\" y1=\"%f%%\" x2=\"%f%%\" y2=\"%f%%\">\n", id, x1, y1, x2, y2 );
   fprintf( svg->file, "<stop offset=\"0%%\" style=\"stop-color:#%06x;stop-opacity:1\" />\n", startColor );
   fprintf( svg->file, "<stop offset=\"100%%\" style=\"stop-color:#%06x;stop-opacity:1\" />\n", endColor );
   fprintf( svg->file, "</linearGradient>\n" );
   fprintf( svg->file, "</defs>\n" );
}

void svg_triangle_linear_gradient( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int startColor, unsigned int endColor )
{
   // Definition of a linear gradient triangle
   static int gradient_id = 0;
   fprintf( svg->file, "<defs>\n" );
   fprintf( svg->file, "  <linearGradient id=\"triangleGradient%d\" x1=\"0%%\" y1=\"0%%\" x2=\"100%%\" y2=\"0%%\">\n", gradient_id );
   fprintf( svg->file, "    <stop offset=\"0%%\" style=\"stop-color:#%06x;stop-opacity:1\" />\n", startColor );
   fprintf( svg->file, "    <stop offset=\"100%%\" style=\"stop-color:#%06x;stop-opacity:1\" />\n", endColor );
   fprintf( svg->file, "  </linearGradient>\n" );
   fprintf( svg->file, "</defs>\n" );

   // Drawing a triangle with a gradient
   fprintf( svg->file, "<polygon points=\"%d,%d %d,%d %d,%d\" fill=\"url(#triangleGradient%d)\"/>\n", x1, y1, x2, y2, x3, y3, gradient_id );

   gradient_id++; // Increment the gradient ID
}

/* Radial gradient */
void svg_radial_gradient( SVG *svg, const char *id, unsigned int innerColor, unsigned int outerColor, float cx, float cy, float r )
{
   fprintf( svg->file, "<defs>\n" );
   fprintf( svg->file, "<radialGradient id=\"%s\" cx=\"%f%%\" cy=\"%f%%\" r=\"%f%%\">\n", id, cx, cy, r );
   fprintf( svg->file, "<stop offset=\"0%%\" style=\"stop-color:#%06x;stop-opacity:1\"/>\n", innerColor );
   fprintf( svg->file, "<stop offset=\"100%%\" style=\"stop-color:#%06x;stop-opacity:1\"/>\n", outerColor );
   fprintf( svg->file, "</radialGradient>\n" );
   fprintf( svg->file, "</defs>\n" );
}

void svg_triangle_radial_gradient( SVG *svg, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int startColor, unsigned int endColor )
{

   // Definition of a radial gradient triangle
   static int gradient_id = 0;
   fprintf( svg->file, "<defs>\n" );
   fprintf( svg->file, "  <radialGradient id=\"triangleRadialGradient%d\" cx=\"50%%\" cy=\"50%%\" r=\"50%%\">\n", gradient_id );
   fprintf( svg->file, "    <stop offset=\"0%%\" style=\"stop-color:#%06x;stop-opacity:1\" />\n", startColor );
   fprintf( svg->file, "    <stop offset=\"100%%\" style=\"stop-color:#%06x;stop-opacity:1\" />\n", endColor );
   fprintf( svg->file, "  </radialGradient>\n" );
   fprintf( svg->file, "</defs>\n" );

   // Drawing a triangle with a gradient
   fprintf( svg->file, "<polygon points=\"%d,%d %d,%d %d,%d\" fill=\"url(#triangleRadialGradient%d)\"/>\n", x1, y1, x2, y2, x3, y3, gradient_id );

   gradient_id++; // Increment the gradient ID
}

void svg_rect_gradient( SVG *svg, int x, int y, int width, int height, const char *gradient_id )
{
   fprintf( svg->file, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"url(#%s)\"/>\n", x, y, width, height, gradient_id );
}

void svg_circle_gradient( SVG *svg, int cx, int cy, int r, const char *gradient_id )
{
   fprintf( svg->file, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"url(#%s)\"/>\n", cx, cy, r, gradient_id );
}
