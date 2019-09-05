#pragma once
#include "Light_A.h"


class PointLight : public Light_A
{
public:
   //position is 0,0,0
   PointLight(const float& _intensity, const RrrColor::RGBA& _color)
      : Light_A(_intensity, _color), pos({0,0,-1})
   {}

   PointLight(const arma::dvec3& _pos, const float& _intensity, const RrrColor::RGBA& _color)
      : Light_A(_intensity, _color), pos(_pos)
   {}

   void transform(const arma::mat44& matrix) override;
   void move(const arma::vec3& move) override;
   void scale(const arma::vec3& scale) override;
   void rotate(const arma::vec3& rotate) override;
   arma::dvec3 getPosition() const noexcept
   {
      return this->pos;
   }

private:
   arma::dvec3 pos;
};

