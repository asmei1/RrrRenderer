#pragma once
#include <armadillo>
#include "Colors.h"
#include "Transform_I.h"

struct ShadingInfo
{
   arma::vec3 lightDirection;
   arma::vec3 colorIntensity;
   float distance;
};

//Lights cannot store their coordinates with other object in mutual matrix
class Light_A : public Transform_I
{
public:

   Light_A(const float& _intensity, const RrrColor::RGBA& _color)
      : Transform_I(), intensity(_intensity), color(_color.toArmaVec3F())
   {}
   virtual ~Light_A() {}

   virtual ShadingInfo getLightInfo(const arma::vec3& hitPoint) = 0;

   float getIntensity() const noexcept
   {
      return this->intensity;
   }

   RrrColor::RGBA getColor() const noexcept
   {
      return RrrColor::RGBA::fromArmaVec3F(this->color);
   }

   friend std::ostream& operator<<(std::ostream& os, Light_A& light)
   {
      os << light.getDebugInfo();
      return os;
   }

protected:
   virtual std::string getDebugInfo() const = 0;


   float intensity;

   arma::vec3 color;
};

using LightUptr = std::unique_ptr<Light_A>;