#pragma once
#include "BMPImg.h"

struct Point_s
{
   int x{ 0 };
   int y{ 0 };
};

class Geometry
{
public:
   static void drawLine(BMPImg & img, Point_s start, Point_s end, BGRA_s color);
   static void test(BMPImg &img)
   {
      img.set(0, 0, { 255, 0, 0 });
      img.set(2, 2, { 255, 0, 0 });
      img.set(2, 0, { 0, 255, 0 });

   }
};

