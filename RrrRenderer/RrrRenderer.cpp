//Realistical render project maked on IPS 
#include <iostream>
#include "BMPImg.h"
#include "Geometry.h"

int main()
{
	BMPImg img{ 100, 100, true };
   Geometry::drawLine(img, { 13, 20 }, { 80, 40 }, RrrColor::Black);
   Geometry::drawLine(img, { 20, 13 }, { 40, 80 }, RrrColor::Black);
   Geometry::drawLine(img, { 80, 40 }, { 13, 20 }, RrrColor::Green);
	img.save("./render.bmp");
}

