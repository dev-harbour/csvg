/*
 * A simple table based on the `dbf` database table showing basic information about selected countries.
 *
 * This example demonstrates the use of the csvg library to generate an SVG file with a table.
 * It contains columns for country code, name and number of inhabitants, presenting the data
 * in an orderly and legible manner.
 *
 * The functions used from the csvg library are svg_text for text and svg_line for creating lines,
 * which allows you to easily build a table structure in the SVG format.
 *
 * This example can be used as a simple way to visualize data from dbf or
 * other sources in your C/C++ project, and also as a starting point for building more
 * complex tables and charts.
 */

#include "csvg.h"

typedef struct _Country
{
   char CODE[ 4 ];
   char NAME[ 31 ];
   double RESIDENTS;
} Country;

void draw_table( SVG *svg, int nX, int nY, char *aCol[][ 3 ], int numCols, Country *countries, int numCountries )
{
   int nI, nDX;
   char *xValue, cValue[ 20 ];
   int nTextWidth;

   nDX = nX;

   svg_line( svg, nX, nY + 5, nX + 350, nY + 5, 1, 0x000000 );

   for( nI = 0; nI < numCols; nI++ )
   {
      xValue = aCol[ nI ][ 0 ];

      nTextWidth = strlen( xValue ) * 6;

      svg_text( svg, nDX + ( atoi( aCol[ nI ][ 2 ] ) - nTextWidth ) / 2, nY, xValue, "Arial", 10, FONT_WEIGHT_NORMAL, 0x000000 );

      nDX += atoi( aCol[ nI ][ 2 ]);

      if( nI < numCols - 1 )
      {
         svg_line( svg, nDX, nY - 15, nDX, nY + 200, 1, 0x000000 );
      }
   }

   nY += 20;

   for( nI = 0; nI < numCountries; nI++ )
   {
      nDX = nX;

      for( int j = 0; j < numCols; j++ )
      {
         if( strcmp( aCol[ j ][ 1 ], "RESIDENTS" ) == 0 )
         {
            sprintf( cValue, "%.0lf", countries[ nI ].RESIDENTS );
            xValue = cValue;
         }
         else if( strcmp( aCol[ j ][ 1 ], "CODE") == 0 )
         {
            xValue = countries[ nI ].CODE;
         }
         else
         {
            xValue = countries[ nI ].NAME;
         }

         svg_text( svg, nDX + 10, nY + 10, xValue, "Arial", 10, FONT_WEIGHT_NORMAL, 0x000000 );
         nDX += atoi( aCol[ j ][ 2 ] );
      }

      nY += 20;
   }
}

int main()
{
   SVG *svg;
   char *aCol[][ 3 ] =
   {
      { "Code", "CODE", "60" },
      { "Country", "NAME", "200" },
      { "Residents", "RESIDENTS", "90" }
   };

   Country countries[] =
   {
      { "LTU", "Lithuania", 3369600 },
      { "USA", "United States of America", 305397000 },
      { "POR", "Portugal", 10617600 },
      { "POL", "Poland", 38115967 },
      { "AUS", "Australia", 21446187 },
      { "FRA", "France", 64473140 },
      { "RUS", "Russia", 141900000 }
    };

   int numCols = sizeof( aCol ) / sizeof( aCol[ 0 ] );
   int numCountries = sizeof( countries ) / sizeof( countries[ 0 ] );

   svg = svg_init( "table.svg", 566, 793 );

   svg_text( svg, 50, 50, "Table of countries", "Arial", 16, FONT_WEIGHT_NORMAL, 0xFF0000 );

   draw_table( svg, 50, 75, aCol, numCols, countries, numCountries );

   svg_close( svg );

   return 0;
}
