#include "Geometry.h"

void Geometry::drawLine(BMPImg & img, Point_s start, Point_s end, const RrrColor::BGRA & color)
{
   for (int i = start.x; i < end.x; i++)
   {
      float t = (i - start.x) / (float)(end.x - start.y);
      int y = start.y * (1.0f - t) + end.y * t;
      img.set(i, y, color);
   }
}
