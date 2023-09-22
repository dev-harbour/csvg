/*
 *
 */

#include "csvg.h"

int main()
{
   int x, y, i, radius = 80;
   unsigned int color;

   SVG *svg = svg_init( "example_02.svg", 400, 400 );

   svg_set_background( svg, 0xFFFFFF );

   srand( time( NULL ) ); 

   for( i = 0; i < 44; i++ )
   {
      x = sin( i ) * radius + 200;
      y = cos( i ) * radius + 200;
      color = rand() % 0xFFFFFF;
      svg_circle( svg, x, y, radius, 1, color );
   }

   svg_close( svg );
   return 0;
}
