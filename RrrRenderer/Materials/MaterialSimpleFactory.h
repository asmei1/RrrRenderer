#pragma once
#include <armadillo>
#include "Material.h"
#include <optional>

class MaterialSimpleFactory
{
public:
   MaterialSimpleFactory() = delete;

   enum class MaterialType
   {
      Testing,
      Glass,
      Mirror,
      Plastic,
      Metalic,
      Refract,
   };

   static Material* createMaterial(MaterialType materialType, const arma::vec3& color);
   static std::optional<Material*> parseStringToMaterial(const std::vector<std::string>& mat);
};
