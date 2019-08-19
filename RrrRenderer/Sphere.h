#pragma once
#include "Object_A.h"
class Sphere : public Object_A
{
public:
   Sphere(const arma::mat& allObjectsPositionMatrixRef, int positionIndex, float _radius, RrrColor::RGBA _color)
      : Object_A(allObjectsPositionMatrixRef), posRefIndex(positionIndex), radius(_radius), radius2(_radius* _radius)
   {
      this->color = _color;
   };

   //~Sphere() = default;


   bool intersect(const Ray& ray, float& t) const override;
   void getSurfaceData(const arma::vec3& pHit, arma::vec3& nHit, arma::vec2& tex) const override;

   arma::dvec4 getPositionVec4() const;
   arma::dvec3 getPositionVec3() const;

   void move(const arma::vec3& move) override;

private:
   int posRefIndex = -1;
   float radius;
   float radius2;
};

