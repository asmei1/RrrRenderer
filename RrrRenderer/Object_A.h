#pragma once
#include <glm/glm.hpp>
#include <algorithm>
#include <functional>
#include "Colors.h"
#include "Ray.h"
#include "Transform_I.h"

#define GEOMETRIC_SOLUTION

class Object_A : public Transform_I
{
public:
   Object_A(const arma::mat& allObjectsPositionMatrixRef)
      : Transform_I(allObjectsPositionMatrixRef)
   {};
   //virtual ~Object_A() {};

   //t - this is the intersection distance from the ray origin to the hit point 
   virtual bool intersect(const Ray& ray, float& t) const = 0;
   virtual void getSurfaceData(const arma::vec3& Phit, arma::vec3& Nhit, arma::vec2& tex) const = 0;

   RrrColor::RGBA getColor() const;
protected:
   RrrColor::RGBA color = RrrColor::randomColor();
};

using ObjectUptr = std::unique_ptr<Object_A>;