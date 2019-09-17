#include "MirrorMaterial.h"
#include <Objects/Object_A.h>
#include <Ray.h>
#include "Lights/Light_A.h"
#include "WorldTracer.h"
#include "Intersection.h"

MirrorMaterial::MirrorMaterial(float reflective)
{
   this->reflective = reflective;
}

arma::vec3 MirrorMaterial::getShade(const arma::vec3& hitPoint, const Object_A* object, const Ray& ray, const WorldTracer& worldTracer) const
{
   arma::vec3 rVColor{ 0,0,0 };

   arma::vec3 hitNormal{ 0, 0, 0 };
   arma::vec2 hitTextureCoordinates{ 0, 0 };

   object->getSurfaceData(hitPoint, ray.dir, hitNormal, hitTextureCoordinates);

   arma::vec3 reflectionDir = rrr::reflect(ray.dir, hitNormal);

   arma::vec3 reflectionRayOrig = hitPoint;

   Ray reflectionRay{ reflectionRayOrig, reflectionDir, Ray::RayType::REFLECT };
   Intersection inter;
   arma::vec3 reflectionColor = worldTracer.castRay(reflectionRay);
   
   if (worldTracer.scene.trace(reflectionRay, inter, {object}))
   {
      rVColor = reflectionColor;
   }
   else
   {
      rVColor = worldTracer.settings.getBackgroundColor().toArmaVec3F();
   }

   return rVColor * this->reflective;
}