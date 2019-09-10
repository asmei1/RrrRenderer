#include "FunctionHelper.h"
#include <sstream>
//RrrColor::BGRA HSVtoRGB(RrrColor::HSV hsv) {
//   RrrColor::BGRA rgb;
//   uint8_t region, remainder, p, q, t;
//
//   if (hsv.sat == 0) {
//      rgb.r = hsv.val;
//      rgb.g = hsv.val;
//      rgb.b = hsv.val;
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
//      rgb.r = hsv.val; rgb.g = t; rgb.b = p;
//      break;
//   case 1:
//      rgb.r = q; rgb.g = hsv.val; rgb.b = p;
//      break;
//   case 2:
//      rgb.r = p; rgb.g = hsv.val; rgb.b = t;
//      break;
//   case 3:
//      rgb.r = p; rgb.g = q; rgb.b = hsv.val;
//      break;
//   case 4:
//      rgb.r = t; rgb.g = p; rgb.b = hsv.val;
//      break;
//   default:
//      rgb.r = hsv.val; rgb.g = p; rgb.b = q;
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
//   rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
//   rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);
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
//   if (rgbMax == rgb.r)
//      hsv.hue = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
//   else if (rgbMax == rgb.g)
//      hsv.hue = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
//   else
//      hsv.hue = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);
//
//   return hsv;
//}

std::vector<std::string> rrr::split(const std::string& str, const std::string& delimiter, bool includeEmptyTokens)
{
   std::vector<std::string> rV;
   size_t pos = 0;
   size_t prev = 0;
   std::string token;

   while ((pos = str.find(delimiter, prev)) != std::string::npos)
   {
      token = str.substr(prev, pos - prev);
      if (false == token.empty())
      {
         rV.push_back(token);
      }
      else if (true == includeEmptyTokens)
      {
         rV.push_back(token);
      }

      prev = pos + delimiter.length();
   }
   //take last token to rV
   rV.push_back(str.substr(prev));

   return rV;
}

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

arma::vec3 rrr::reflect(const arma::vec3& N, const arma::vec3& I)
{
   return I - 2 * arma::dot(I, N) * N;
}


arma::vec3 rrr::refract(const arma::vec3& N, const arma::vec3& I, const float& ior)
{
   //initialize return value
   arma::vec3 rV;
   rV.zeros();
   //cosine of the angle between the surface normal and the incident ray direction
   float cosi = static_cast<float>(std::clamp(arma::dot(I, N), -1., 1.));
   //refraction indication of first medium, for simplyfied, its 1 (as air or vacuum)
   float etai = 1;
   //refraction indication of second medium (of object that ray hit or its about to leave)
   float etat = ior;
   arma::vec3 n = N;

   if (cosi < 0)
   {
      //Outside of the surface, cos(O) should be positive
      cosi = -cosi;
   }
   else
   {
      // we are inside the surface, cos(theta) is already positive but reverse normal direction
      n = -N;
      std::swap(etai, etat);
   }

   float eta = etai / etat;
   float k = 1 - etat * eta * (1 - cosi * cosi);

   //check if its total internal reflection. There is no refraction in this case
   if (k >= 0)
   {
      rV = eta * I * (eta * cosi - std::sqrt(k)) % n;
   }

   return rV;
}

float rrr::fresnel(const arma::vec3& I, const arma::vec3& N, const float& ior)
{
   //initialize return value
   float kr;

   //cosine of the angle between the surface normal and the incident ray direction
   float cosi = static_cast<float>(std::clamp(arma::dot(I, N), -1., 1.));
   //refraction indication of first medium, for simplyfied, its 1 (as air or vacuum)
   float etai = 1;
   //refraction indication of second medium (of object that ray hit or its about to leave)
   float etat = ior;

   if(cosi > 0)
   {
      std::swap(etai, etat);
   }
   //compute sini with Snell's law
   float sint = etai / etat * std::sqrtf(std::max(0.f, 1 - cosi * cosi));
   if (sint >= 1)
   {
      kr = 1;
   }
   else
   {
      float cost = std::sqrtf(std::max(0.f, 1 - sint * sint));

      cosi = std::fabs(cosi);

      float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
      float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
      kr = (Rs * Rs + Rp * Rp) / 2;

      //std::cout << I.x() << " " << I.y() << " " << I.z() << " " << N.x() << " " << N.y() << " " << N.z() << " " << std::endl;
      //std::cout << sint << " " << cost << " " << cosi << " " << Rs << " " << Rp << "" << kr << std::endl;

   }

   return kr;
}

void rrr::ltrim(std::string& s)
{
   s.erase(s.begin(),
      std::find_if(s.begin(), s.end(), [](int ch)
         {
            return !std::isspace(ch);
         })
   );
}

void rrr::rtrim(std::string& s)
{
   s.erase(
      std::find_if(s.rbegin(), s.rend(), [](int ch)
         {
            return !std::isspace(ch);
         }).base(), s.end());
}

void rrr::trim(std::string& s)
{
   ltrim(s);
   rtrim(s);
}




