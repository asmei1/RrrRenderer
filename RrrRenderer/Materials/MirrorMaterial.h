#pragma once
#include "Material.h"
class MirrorMaterial : public Material
{
public:
   MirrorMaterial(float reflective = 0.9f);

   arma::vec3 getShade(const arma::vec3& hitPoint, const Object_A* object, const Ray& ray, const WorldTracer& worldTracer) const override;

protected:
   float reflective;
   
};


