#pragma once
#include "Material.h"

class MetallicMaterial : public Material
{
public:
   MetallicMaterial(float diffuseWeight = 0.4f, float specularWeight = 0.4f, float specularExponent = 100.0f);

};

