#pragma once
#include <armadillo>
#include "Colors.h"
#include "Transform_I.h"

//Lights cannot store their coordinates with other object in mutual matrix
class Light_A : public Transform_I
{
public:

   Light_A(const float& _intensity, const RrrColor::RGBA& _color)
      : Transform_I(), intensity(_intensity), color(_color)
   {}
   virtual ~Light_A() {}


   float getIntensity() const noexcept
   {
      return this->intensity;
   }

   RrrColor::RGBA getColor() const noexcept
   {
      this->color;
   }


protected:
   float intensity;

   RrrColor::RGBA color;
};

