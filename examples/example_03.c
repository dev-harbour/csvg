/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "example_03.svg", 391, 391 );

   svg_set_background( svg, 0xFFFFFF );
   svg_filled_rect( svg, 25, 25, 200, 200, 0x00FF00 );
   svg_circle( svg, 125, 125, 75, 4, 0xFFA500 );
   int points[] = { 50, 150, 50, 200, 200, 200, 200, 100 };
   svg_polyline( svg, points, 4, 4, 0xFF0000 );
   svg_line( svg, 50, 50, 200, 200, 4, 0x0000FF );

   svg_close( svg );

   return 0;
}
