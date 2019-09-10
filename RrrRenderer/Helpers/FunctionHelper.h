#pragma once
#include <vector>
#include "BMPImg.h"
//
//RrrColor::BGRA HSVtoRGB(RrrColor::HSV);
//RrrColor::HSV RGBtoHSV(RrrColor::BGRA);
namespace rrr
{
   std::vector<std::string> split(const std::string& str, const std::string& delimiter = " ", bool includeEmptyTokens = false);

   uint8_t truncate(int val);
   int roundUp(int numToRound, int multiple);
   std::vector<std::string> split(const std::string& s, char delimiter);

   bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);

   void multVecMatrixCM(const arma::dmat44& x, const arma::vec4& src, arma::vec3& dst);
   void multDirMatrixCM(const arma::dmat44& x, const arma::vec3& src, arma::vec3& dst);

   //https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
   arma::vec3 reflect(const arma::vec3& N, const arma::vec3& I);
   arma::vec3 refract(const arma::vec3& N, const arma::vec3& I, const float& ior);
   float fresnel(const arma::vec3& N, const arma::vec3& I, const float& ior);


   // trim from start (in place)
   void ltrim(std::string& s);
   // trim from end (in place)
   void rtrim(std::string& s);
   // trim from both ends (in place)
   void trim(std::string& s);

   inline double deg2rad(const double& deg)
   {
      return deg * PI / 180;
   }


}