#include "Geometry.h"

void Geometry::drawLine(BMPImg & img, Point_s start, Point_s end, BGRA_s color)
{
   for (float t = 0.; t < 1.; t += .01) 
   {
      int x = start.x + (end.x - start.x)*t;
      int y = start.y + (end.y - start.y)*t;
      img.set(x, y, color);
   }
}
