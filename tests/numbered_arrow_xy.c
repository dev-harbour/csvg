/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "numbered_arrow_xy.svg", 800, 600 );
   svg_set_background( svg, 0xFFFFFF );

   // x1 = 50, y1 = 550 (początek obu strzałek)
   // x2 = 750 (końcowa współrzędna x dla strzałki poziomej)
   // y3 = 50 (końcowa współrzędna y dla strzałki pionowej)

   svg_numbered_arrow_xy( svg, 50, 550, 750, 50, 1, 0, 100, 10, 0x000000 );

   svg_close( svg );
   return 0;
}
