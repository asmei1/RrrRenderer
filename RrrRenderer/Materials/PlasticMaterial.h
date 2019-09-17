#pragma once
#include "Material.h"

class PlasticMaterial : public Material
{
public:
   PlasticMaterial(float diffuseWeight = 0.4f, float specularWeight = 0.4f, float specularExponent = 20.0f);

};

