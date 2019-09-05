#pragma once
#include <glm/glm.hpp>
#include <algorithm>
#include <functional>
#include <armadillo>
#include "Colors.h"
#include "Ray.h"
#include "Transform_I.h"

#define GEOMETRIC_SOLUTION

class Object_A : public Transform_I
{
public:
   Object_A(const arma::dvec3& _albedo = arma::dvec3{0.18, 0.18, 0.18})
   {};
   //virtual ~Object_A() {};

   //t - this is the intersection distance from the ray origin to the hit point 
   virtual bool intersect(const Ray& ray, float& t) const = 0;
   virtual void getSurfaceData(const arma::vec3& hitPoint, arma::vec3& viewDirection, const arma::vec2& uv, arma::vec3& hitNormal, arma::vec2& hitTextureCoordinate) const = 0;

   RrrColor::RGBA getColor() const;

   static void setAllObjectsPositionMatrix(const arma::mat* allObjectsPositionMatrix)
   {
      Object_A::allObjectsPositionMatrix = allObjectsPositionMatrix;
   }

protected:
   RrrColor::RGBA color = RrrColor::randomColor();
   arma::dvec3 albedo;

   static inline const arma::mat* allObjectsPositionMatrix = nullptr;
};

using ObjectUptr = std::unique_ptr<Object_A>;