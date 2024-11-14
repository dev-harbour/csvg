/*
 * 
 */

#include "csvg.h"

int main()
{
   int x, y, x1, y1, x2, y2;
   double a;
   int i, r = 200;

   SVG *svg = svg_init( "example_01.svg", 830, 450 );

   svg_set_background( svg, 0x530972 );

   x = 415;
   y = 225;

   a = 2 * M_PI / 6;

   svg_hexagon( svg, x, y, r + 10, 6, 0, 0xFAF2FE );
   svg_filled_hexagon( svg, x, y, r, 0, 0x5C6BBF );

   for( i = 0; i < 2; i++ )
   {
      x1 = x + r * cos( a * i + M_PI / 6 );
      y1 = y + r * sin( a * i + M_PI / 6 );
      x2 = x + r * cos( a * ( i + 1 ) + M_PI / 6 );
      y2 = y + r * sin( a * ( i + 1 ) + M_PI / 6 );
      svg_filled_triangle( svg, x, y, x1, y1, x2, y2, 0x283492 );
   }

   svg_circle( svg, x, y, 100, 66, 0xFFFFFF );

   x1 = x + r * cos( a * 5 + M_PI / 6 );
   y1 = y + r * sin( a * 5 + M_PI / 6 );
   x2 = x + r * cos( a * ( 5 + 1 ) + M_PI / 6 );
   y2 = y + r * sin( a * ( 5 + 1 ) + M_PI / 6 );
   svg_filled_triangle( svg, x, y, x1, y1, x2, y2, 0x3848AA );
   
   svg_close( svg );
   return 0;
}
