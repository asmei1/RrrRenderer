#pragma once
#include <armadillo>

class Ray
{
public:
   enum class RayType : uint8_t
   {
      PRIMARY,
      SHADOW
   };

   Ray(const arma::vec3& _orig, const arma::vec3& _dir, RayType _type = RayType::PRIMARY)
   : orig(_orig), dir(_dir), type(_type)
   {
      type == RayType::PRIMARY ? ++primaryCount : ++shadowCount;
   };
   ~Ray() = default;

   arma::vec3 orig;
   arma::vec3 dir;

   float tMin = 0;
   float tMax = 0;

   const RayType type;

   static void printInfo()
   {
      std::cout << "Primary rays: " << Ray::primaryCount << std::endl;
      std::cout << "Shadow  rays: " << Ray::shadowCount << std::endl;
   }

private:
   static inline uint32_t primaryCount = 0;
   static inline uint32_t shadowCount = 0;
};

