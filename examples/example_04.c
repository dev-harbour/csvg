/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "example_04.svg", 800, 600 );

   svg_text( svg, 50, 50, "Hello, World!", "Arial", 24, 0xFF0000 );
   svg_text( svg, 50, 100, "How are you?", "Verdana", 24, 0x00FF00 );
   svg_text( svg, 50, 150, "C SVG Library", "Courier New", 24, 0x0000FF );
   svg_text( svg, 50, 200, "Different Fonts", "Times New Roman", 24, 0xFF00FF );

   svg_close( svg );
   return 0;
}
