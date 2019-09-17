#pragma once
#include "Material.h"

class RefractMaterial : public Material
{
public:
   RefractMaterial(float refractive = 1.f);

   arma::vec3 getShade(const arma::vec3& hitPoint, const Object_A* object, const Ray& ray, const WorldTracer& worldTracer) const override;
protected:
   float refractive;
};

