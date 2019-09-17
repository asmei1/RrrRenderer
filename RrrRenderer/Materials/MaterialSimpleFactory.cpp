#include "MaterialSimpleFactory.h"
#include "TestingMaterial.h"
#include <Helpers/FunctionHelper.h>
#include "MirrorMaterial.h"
#include "PlasticMaterial.h"
#include "MetallicMaterial.h"
#include "RefractMaterial.h"

Material* MaterialSimpleFactory::createMaterial(MaterialType materialType, const arma::vec3& color)
{
   Material* rVMat = nullptr;
   if(materialType == MaterialType::Testing)
   {
      rVMat = new TestingMaterial;
   }
   else if(materialType == MaterialType::Mirror)
   {
      rVMat = new MirrorMaterial;
   }
   else if(materialType == MaterialType::Plastic)
   {
      rVMat = new PlasticMaterial;
   }
   else if(materialType == MaterialType::Metalic)
   {
      rVMat = new MetallicMaterial;
   }
   else if(materialType == MaterialType::Refract)
   {
      rVMat = new RefractMaterial;
   }

   rVMat->setColor(color);

   return rVMat;
}

std::optional<Material*> MaterialSimpleFactory::parseStringToMaterial(const std::vector<std::string>& mat)
{
   std::optional<Material*> rV = std::nullopt;

   const std::string testingMaterialTag = "testing";
   const std::string mirrorMaterialTag = "mirror";
   const std::string plasticMaterialTag = "plastic";
   const std::string metallicMaterialTag = "metallic";
   const std::string refractMaterialTag = "refract";
   const std::string colorTag = "color";
   RrrColor::RGBA color = RrrColor::randomColor();


   for(size_t i = 0; i < mat.size(); ++i)
   {
      if(testingMaterialTag == mat[i])
      {
         rV = new TestingMaterial;
      }
      else if(mirrorMaterialTag == mat[i])
      {
         rV = new MirrorMaterial;
      }
      else if(plasticMaterialTag == mat[i])
      {
         rV = new PlasticMaterial;
      }
      else if(metallicMaterialTag == mat[i])
      {
         rV = new MetallicMaterial;
      }
      else if(refractMaterialTag == mat[i])
      {
         rV = new RefractMaterial;
      }
      else if(colorTag == mat[i])
      {
         color.r = std::stoi(mat[i + 1]);
         color.g = std::stoi(mat[i + 2]);
         color.b = std::stoi(mat[i + 3]);

         i += 3;
      }
   }

   if(rV)
   {
      (*rV)->setColor(color);
   }

   return rV;
}
