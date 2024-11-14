/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "arrow_with_numbers.svg", 800, 400 );
   svg_set_background( svg, 0xFFFFFF );

   svg_numbered_arrow( svg, 100, 100, 700, 300, 1, 0, 10, 1, 0xFF0000 );

   svg_close( svg );
   return 0;
}
