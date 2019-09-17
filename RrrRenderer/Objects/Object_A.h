#pragma once
#include <glm/glm.hpp>
#include <algorithm>
#include <functional>
#include <armadillo>
#include "Colors.h"
#include "Ray.h"
#include "Transform_I.h"
#include "Materials/Material.h"

#define GEOMETRIC_SOLUTION

class WorldTracer;

class Object_A : public Transform_I
{
public:
   Object_A(Material* _material, const RrrColor::RGBA& _color = RrrColor::randomColor())
      : material(_material)
   {
      this->material->setColor(_color);
   };
   virtual ~Object_A();

   Material* material;

   //t - this is the intersection distance from the ray origin to the hit point 
   virtual bool intersect(const Ray& ray, float& t) const = 0;
   virtual void getSurfaceData(const arma::vec3& hitPoint, const arma::vec3& viewDirection, arma::vec3& hitNormal, arma::vec2& hitTextureCoordinate) const = 0;

   static void setAllObjectsPositionMatrix(const arma::mat* allObjectsPositionMatrix)
   {
      Object_A::allObjectsPositionMatrix = allObjectsPositionMatrix;
   }

   friend std::ostream& operator<<(std::ostream& os, Object_A& obj)
   {
      os << obj.getDebugInfo();
      return os;
   }

   arma::vec3 getShade(const arma::vec3& hitPoint, const Ray& ray, const WorldTracer& worldTracer) const
   {
      return this->material->getShade(hitPoint, this, ray, worldTracer);
   }

protected:
   virtual std::string getDebugInfo() const = 0;

   static inline const arma::mat* allObjectsPositionMatrix = nullptr;
};

using ObjectUptr = std::unique_ptr<Object_A>;