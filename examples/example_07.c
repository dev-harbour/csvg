/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "example_07.svg", 500, 500 );
    
   svg_triangle_linear_gradient( svg, 100, 100, 200, 100, 150, 50, 0xFF0000, 0x0000FF );
   svg_triangle_radial_gradient( svg, 300, 100, 400, 100, 350, 50, 0xFF0000, 0x0000FF );
    
   svg_close( svg );
   return 0;
}
