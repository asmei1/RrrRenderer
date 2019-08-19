#pragma once
#include <armadillo>

class Ray
{
public:
   Ray(const arma::vec3& _orig, const arma::vec3& _dir)
   : orig(_orig), dir(_dir)
   {
      Ray::counter++;
   };
   ~Ray() = default;

   arma::vec3 orig;
   arma::vec3 dir;
   float tMin = 0;
   float tMax = 0;

   static inline uint32_t counter = 0;
};

