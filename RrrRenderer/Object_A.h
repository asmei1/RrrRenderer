#pragma once
#include <glm/glm.hpp>
#include <algorithm>
#include <functional>
#include <armadillo>
#include "Colors.h"
#include "Ray.h"
#include "Transform_I.h"
#include "Material.h"

#define GEOMETRIC_SOLUTION

class Object_A : public Transform_I
{
public:
   Object_A(const Material* _material, const RrrColor::RGBA& _color = RrrColor::randomColor())
      : material(_material), color(_color)
   {
   };
   virtual ~Object_A() {};

   const Material* material;

   //t - this is the intersection distance from the ray origin to the hit point 
   virtual bool intersect(const Ray& ray, float& t) const = 0;
   virtual void getSurfaceData(const arma::vec3& hitPoint, const arma::vec3& viewDirection, arma::vec3& hitNormal, arma::vec2& hitTextureCoordinate) const = 0;

   RrrColor::RGBA getColor() const;

   static void setAllObjectsPositionMatrix(const arma::mat* allObjectsPositionMatrix)
   {
      Object_A::allObjectsPositionMatrix = allObjectsPositionMatrix;
   }

   friend std::ostream& operator<<(std::ostream& os, Object_A& obj)
   {
      os << obj.getDebugInfo();
      return os;
   }

protected:
   virtual std::string getDebugInfo() const = 0;

   RrrColor::RGBA color = RrrColor::randomColor();

   static inline const arma::mat* allObjectsPositionMatrix = nullptr;
};

using ObjectUptr = std::unique_ptr<Object_A>;