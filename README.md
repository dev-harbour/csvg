<div align="center">
   <h1 align="center">csvg: A Simple SVG Library in C</h1>
</div>
<br />

`csvg` is a minimalistic library for creating Scalable Vector Graphics (SVG) files using the C programming language. This library adheres to the [W3C SVG](https://www.w3.org/TR/SVG2/) standard and is designed to simplify various graphic tasks.

### Getting Started

For more info see [getting started](examples/README.md).

### Example

``` c
#include "csvg.h"

int main()
{
   int x, y, x1, y1, x2, y2;
   double a;
   int i, r = 200;

   SVG *svg = svg_init( "example_01.svg", 830, 450 );

   svg_set_background( svg, 0x530972 );

   x = 415;
   y = 225;

   a = 2 * M_PI / 6;

   svg_hexagon( svg, x, y, r + 10, 6, 0, 0xFAF2FE );
   svg_filled_hexagon( svg, x, y, r, 0, 0x5C6BBF );

   for( i = 0; i < 2; i++ )
   {
      x1 = x + r * cos( a * i + M_PI / 6 );
      y1 = y + r * sin( a * i + M_PI / 6 );
      x2 = x + r * cos( a * ( i + 1 ) + M_PI / 6 );
      y2 = y + r * sin( a * ( i + 1 ) + M_PI / 6 );
      svg_filled_triangle( svg, x, y, x1, y1, x2, y2, 0x283492 );
   }

   svg_circle( svg, x, y, 100, 66, 0xFFFFFF );

   x1 = x + r * cos( a * 5 + M_PI / 6 );
   y1 = y + r * sin( a * 5 + M_PI / 6 );
   x2 = x + r * cos( a * ( 5 + 1 ) + M_PI / 6 );
   y2 = y + r * sin( a * ( 5 + 1 ) + M_PI / 6 );
   svg_filled_triangle( svg, x, y, x1, y1, x2, y2, 0x3848AA );
   
   svg_close( svg );
   return 0;
}
```

![Main](docs/assets/img/example_01.svg)

### Contributing
Contributions are welcome! Feel free to submit a pull request.
