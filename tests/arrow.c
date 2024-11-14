/*
 *
 */

#include "csvg.h"

int main()
{
   SVG *svg = svg_init( "arrow.svg", 400, 400 );
   svg_set_background( svg, 0xFFFFFF );

   // Początkowy punkt dla strzałek (lewym dolnym rogu)
   int startX = 50;
   int startY = 350;

   // Długość strzałek
   int length = 300;

   // Kąt początkowy i końcowy
   double startAngle = 90.0;
   double endAngle = 18.0;

   // Krok dla kąta (na przykład 10 stopni)
   double step = 10.0;

   // Rysowanie strzałek
   for( double angle = startAngle; angle >= endAngle; angle -= step )
   {
      double radianAngle = angle * ( M_PI / 180.0 );
      int endX = startX + ( int ) ( length * cos( radianAngle ) );
      int endY = startY - ( int ) ( length * sin( radianAngle ) );

      // Zmiana koloru strzałki w zależności od kąta
      unsigned int red = ( int ) ( 255 * sin( radianAngle ) );
      unsigned int green = ( int ) ( 255 * cos( radianAngle ) );
      unsigned int blue = 255 - red - green;
      unsigned int color = ( red << 16 ) + ( green << 8 ) + blue;

      svg_arrow( svg, startX, startY, endX, endY, 1, color );
   }

   svg_close( svg );
   return 0;
}
