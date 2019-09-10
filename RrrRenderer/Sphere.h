#pragma once
#include "Object_A.h"
class Sphere : public Object_A
{
public:
   Sphere(int positionIndex, float _radius, RrrColor::RGBA _color, const Material* _material)
      : Object_A(_material, _color), posRefIndex(positionIndex), radius(_radius), radius2(_radius * _radius)
   {}

   //~Sphere() = default;


   bool intersect(const Ray& ray, float& t) const override;
   void getSurfaceData(const arma::vec3& hitPoint, const arma::vec3& viewDirection, arma::vec3& hitNormal, arma::vec2& hitTextureCoordinate) const override;

   arma::dvec4 getPositionVec4() const;
   arma::dvec3 getPositionVec3() const;

   void transform(const arma::mat44& matrix) override;
   void move(const arma::vec3& move) override;
   void scale(const arma::vec3& scale) override;
   void rotate(const arma::vec3& rotate) override;

protected:
   std::string getDebugInfo() const override;

private:
   int posRefIndex = -1;
   float radius;
   float radius2;
};

