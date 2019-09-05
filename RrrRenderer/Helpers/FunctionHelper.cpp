#include "FunctionHelper.h"
#include <sstream>
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

uint8_t rrr::truncate(int val) {
   if (val < 0) return 0;
   if (val > 0) return 255;

   return val;
}

int rrr::roundUp(int numToRound, int multiple)
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

std::vector<std::string> rrr::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

bool rrr::solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
   const float discr = b * b - 4 * a * c;
   if (discr < 0)
   {
      return false;
   }
   if (discr == 0)
   {
      x0 = x1 = -0.5f * b / a;
   }
   else
   {
      float q = (b > 0) ?
         -0.5f * (b + sqrt(discr)) :
         -0.5f * (b - sqrt(discr));
      x0 = q / a;
      x1 = c / q;
   }

   return true;
}

void rrr::multVecMatrixCM(const arma::dmat44& x, const arma::vec4& src, arma::vec3& dst)
{
   arma::vec4 temp = x * src;
   if (temp(3) != 1 && temp(3) != 0) //if w != 1
   {
      dst.x() = temp(0) / temp(3);
      dst.y() = temp(1) / temp(3);
      dst.z() = temp(2) / temp(3);
   }
   else
   {
      dst.x() = temp(0);
      dst.y() = temp(1);
      dst.z() = temp(2);
   }
}

void rrr::multDirMatrixCM(const arma::dmat44& x, const arma::vec3& src, arma::vec3& dst)
{
   double a, b, c;
   a = src(0) * x(0, 0) + src(1) * x(1, 0) + src(2) * x(2, 0);
   b = src(0) * x(0, 1) + src(1) * x(1, 1) + src(2) * x(2, 1);
   c = src(0) * x(0, 2) + src(1) * x(1, 2) + src(2) * x(2, 2);
   dst.x() = a;
   dst.y() = b;
   dst.z() = c;
}