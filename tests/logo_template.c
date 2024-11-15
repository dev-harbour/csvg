/*
 *
 */

#include "csvg.h"

int main()
{
   int width = 512, height = 512;

   SVG *svg = svg_init( "logo_template.svg", width, height );

   svg_filled_circle( svg, width / 2, height / 2, 256, 0x530972 );

   svg_line( svg, 42, ( height - 250 ) / 2, width - 42, ( height - 250 ) / 2, 30, 0x323232 );

   svg_filled_rect( svg, 25, ( height - 220 ) / 2, width - 50, 180, 0xF2F2F2 );

   svg_line( svg, 25, ( height + 141 ) / 2, width - 25, ( height + 141 ) / 2, 30, 0x323232 );

   svg_circle( svg, width / 2, height / 2, 256 - 15, 30, 0x323232 );

   svg_text( svg, ( width - 3 * ( 140 * 0.6 ) ) / 2, ( height + 20 ) / 2, "C++", "Free Mono", 140, FONT_WEIGHT_BLACK, 0x323232 );

   svg_close( svg );

   return 0;
}
