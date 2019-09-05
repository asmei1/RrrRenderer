#pragma once
#include "BMPImg.h"
//
//RrrColor::BGRA HSVtoRGB(RrrColor::HSV);
//RrrColor::HSV RGBtoHSV(RrrColor::BGRA);
namespace rrr
{
   uint8_t truncate(int val);
   int roundUp(int numToRound, int multiple);
   std::vector<std::string> split(const std::string& s, char delimiter);
   
   bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);
   
   void multVecMatrixCM(const arma::dmat44& x, const arma::vec4& src, arma::vec3& dst);
   void multDirMatrixCM(const arma::dmat44& x, const arma::vec3& src, arma::vec3& dst);
   
   inline double deg2rad(const double& deg)
   {
      return deg * PI / 180;
   }


}