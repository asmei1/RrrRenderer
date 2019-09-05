#pragma once
#include "Object_A.h"
class Sphere : public Object_A
{
public:
   Sphere(int positionIndex, float _radius, RrrColor::RGBA _color, const arma::dvec3& albedo = arma::dvec3{ 0.18, 0.18, 0.18 })
      : Object_A(albedo), posRefIndex(positionIndex), radius(_radius), radius2(_radius* _radius)
   {
      this->color = _color;
   };

   //~Sphere() = default;


   bool intersect(const Ray& ray, float& t) const override;
   void getSurfaceData(const arma::vec3& hitPoint, arma::vec3& viewDirection, const arma::vec2& uv, arma::vec3& hitNormal, arma::vec2& hitTextureCoordinate) const override;

   arma::dvec4 getPositionVec4() const;
   arma::dvec3 getPositionVec3() const;

   void transform(const arma::mat44& matrix) override;
   void move(const arma::vec3& move) override;
   void scale(const arma::vec3& scale) override;
   void rotate(const arma::vec3& rotate) override;

private:
   int posRefIndex = -1;
   float radius;
   float radius2;
};

