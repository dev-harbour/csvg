/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "example_06.svg", 500, 500 );

   svg_linear_gradient( svg, "gradient1", 0xFF0000, 0x0000FF, 5.0, 5.0, 100.0, 100.0 );
   svg_radial_gradient( svg, "gradient2", 0x00FF00, 0x000000, 50.0, 50.0, 50.0 );

   // Using a linear gradient
   svg_rect_gradient( svg, 10, 10, 200, 200, "gradient1" );
    
   // Using a radial gradient
   svg_circle_gradient( svg, 400, 400, 100, "gradient2" );

   svg_close( svg );
   return 0;
}
