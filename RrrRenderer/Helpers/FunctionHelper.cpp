#include "FunctionHelper.h"

//RrrColor::BGRA HSVtoRGB(RrrColor::HSV hsv) {
//   RrrColor::BGRA rgb;
//   uint8_t region, remainder, p, q, t;
//
//   if (hsv.sat == 0) {
//      rgb.red = hsv.val;
//      rgb.green = hsv.val;
//      rgb.blue = hsv.val;
//      return rgb;
//   }
//   region = hsv.hue / 43;
//   remainder = (hsv.hue - (region * 43)) * 6;
//
//   p = (hsv.val * (255 - hsv.sat)) >> 8;
//   q = (hsv.val * (255 - ((hsv.sat * remainder) >> 8))) >> 8;
//   t = (hsv.val * (255 - ((hsv.sat * (255 - remainder)) >> 8))) >> 8;
//
//   switch (region)
//   {
//   case 0:
//      rgb.red = hsv.val; rgb.green = t; rgb.blue = p;
//      break;
//   case 1:
//      rgb.red = q; rgb.green = hsv.val; rgb.blue = p;
//      break;
//   case 2:
//      rgb.red = p; rgb.green = hsv.val; rgb.blue = t;
//      break;
//   case 3:
//      rgb.red = p; rgb.green = q; rgb.blue = hsv.val;
//      break;
//   case 4:
//      rgb.red = t; rgb.green = p; rgb.blue = hsv.val;
//      break;
//   default:
//      rgb.red = hsv.val; rgb.green = p; rgb.blue = q;
//      break;
//   }
//
//   return rgb;
//}
//
//RrrColor::HSV RGBtoHSV(RrrColor::BGRA rgb) {
//
//   RrrColor::HSV hsv;
//   unsigned char rgbMin, rgbMax;
//
//   rgbMin = rgb.red < rgb.green ? (rgb.red < rgb.blue ? rgb.red : rgb.blue) : (rgb.green < rgb.blue ? rgb.green : rgb.blue);
//   rgbMax = rgb.red > rgb.green ? (rgb.red > rgb.blue ? rgb.red : rgb.blue) : (rgb.green > rgb.blue ? rgb.green : rgb.blue);
//
//   hsv.val = rgbMax;
//   if (hsv.val == 0)
//   {
//      hsv.hue = 0;
//      hsv.sat = 0;
//      return hsv;
//   }
//
//   hsv.sat = 255 * long(rgbMax - rgbMin) / hsv.val;
//   if (hsv.sat == 0)
//   {
//      hsv.hue = 0;
//      return hsv;
//   }
//
//   if (rgbMax == rgb.red)
//      hsv.hue = 0 + 43 * (rgb.green - rgb.blue) / (rgbMax - rgbMin);
//   else if (rgbMax == rgb.green)
//      hsv.hue = 85 + 43 * (rgb.blue - rgb.red) / (rgbMax - rgbMin);
//   else
//      hsv.hue = 171 + 43 * (rgb.red - rgb.green) / (rgbMax - rgbMin);
//
//   return hsv;
//}

uint8_t truncate(int val) {
   if (val < 0) return 0;
   if (val > 0) return 255;

   return val;
}

int roundUp(int numToRound, int multiple)
{
   if (multiple == 0)
   {
      return numToRound;
   }

   int remainder = numToRound % multiple;
   if (remainder == 0)
   {
      return numToRound;
   }

   return numToRound + multiple - remainder;
}
