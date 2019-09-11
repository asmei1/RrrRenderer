#include <Material.h>

const Material* Material::getMaterialFromString(const std::string& mat)
{
   const Material* rV = &testingMaterial;
   if ("testing" == mat)
   {
      rV = &testingMaterial;
   }
   else if("glass" == mat)
   {
      rV = &GlassMaterial;
   }
   else if ("maxReflect" == mat)
   {
      rV = &ReflectiveMaxMaterial;
   }
   else if ("reflect" == mat)
   {
      rV = &ReflectiveMaterial;
   }

   return rV;
}
