/*
 *
 */

#include "csvg.h"

unsigned int random_color()
{
   return rand() % 0xFFFFFF;
}

int main()
{
   SVG *svg = svg_init( "bar_chart.svg", 850, 300 );
   svg_set_background( svg, 0xFFFFFF );

   // Rysowanie osi
   svg_arrow( svg, 50, 275, 825, 275, 1, 0x000000 );  // Oś X
   svg_arrow( svg, 50, 275, 50, 50, 1, 0x000000 );   // Oś Y

   // Dni i wartości
   char *days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
   int values[] = { 10, 20, 30, 25, 15, 40, 50 };

    int bar_width = 80;
    int bar_spacing = 20;
    int x_pos = 100;  // początkowa pozycja X dla pierwszego słupka

   for( int i = 0; i < 7; ++i )
   {
      unsigned int color = random_color();
      svg_filled_rect( svg, x_pos, 275 - values[ i ], bar_width, values[ i ], color );
      svg_text( svg, x_pos, 290, days[ i ], "Arial", 12, 0x000000 ); // Tekst wyrównany do początku słupka
      x_pos += bar_width + bar_spacing;  // aktualizacja pozycji X dla następnego słupka
   }

   svg_close(svg);
   return 0;
}
