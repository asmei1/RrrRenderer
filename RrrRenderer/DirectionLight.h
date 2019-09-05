#pragma once
#include "Light_A.h"
class DirectionLight : public Light_A
{
public:
   //direction is 0,0,-1
   DirectionLight(const float& _intensity, const RrrColor::RGBA& _color)
      : Light_A(_intensity, _color)
   {}

   DirectionLight(const arma::dvec3& _dir, const float& _intensity, const RrrColor::RGBA& _color)
      : Light_A(_intensity, _color), dir(_dir)
   {
   }

   void transform(const arma::mat44& matrix) override;
   void move(const arma::vec3& move) override;
   void scale(const arma::vec3& scale) override;
   void rotate(const arma::vec3& rotate) override;

   arma::dvec3 getDirection() const noexcept
   {
      return this->dir;
   }

private:
   arma::dvec3 dir;
};

