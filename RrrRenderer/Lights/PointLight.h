#pragma once
#include "Light_A.h"


class PointLight : public Light_A
{
public:
   PointLight(const arma::dvec3& _pos, const float& _intensity, const RrrColor::RGBA& _color)
      : Light_A(_intensity, _color), pos(_pos)
   {}

   ShadingInfo getLightInfo(const arma::vec3& hitPoint) override;

   void transform(const arma::mat44& matrix) override;
   void move(const arma::vec3& move) override;
   void scale(const arma::vec3& scale) override;
   void rotate(const arma::vec3& rotate) override;

   arma::dvec3 getPosition() const noexcept
   {
      return this->pos;
   }

protected:
   std::string getDebugInfo() const override;

private:
   arma::dvec3 pos;
};

