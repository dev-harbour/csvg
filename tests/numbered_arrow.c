/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "numbered_arrow.svg", 800, 600 );
   svg_set_background( svg, 0xFFFFFF );

   // Rysowanie strzałki poziomej z etykietami od 0 do 100 (co 10)
   svg_numbered_arrow( svg, 50, 550, 750, 550, 1, 0, 100, 10, 0x000000 );

   // Rysowanie strzałki pionowej z etykietami od 0 do 100 (co 10)
   svg_numbered_arrow( svg, 50, 550, 50, 50, 1, 0, 100, 10, 0x000000 );

   svg_close( svg );
   return 0;
}
