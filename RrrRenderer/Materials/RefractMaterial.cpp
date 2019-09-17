#include "RefractMaterial.h"
#include "Helpers/FunctionHelper.h"
#include <Ray.h>
#include "Lights/Light_A.h"
#include "WorldTracer.h"
#include "Intersection.h"

RefractMaterial::RefractMaterial(float refractive)
{
   this->refractive = refractive;
}

arma::vec3 RefractMaterial::getShade(const arma::vec3& hitPoint, const Object_A* object, const Ray& ray, const WorldTracer& worldTracer) const
{

   arma::vec3 rVColor{ 0,0,0 };

   //arma::vec3 hitNormal{ 0, 0, 0 };
   //arma::vec2 hitTextureCoordinates{ 0, 0 };

   //object->getSurfaceData(hitPoint, ray.dir, hitNormal, hitTextureCoordinates);

   //arma::vec3 refractionColor;
   //refractionColor.zeros();

   //float kr = rrr::fresnel(ray.dir, hitNormal, this->refractive);
   //bool outside = arma::dot(ray.dir, hitNormal) < 0;
   //arma::vec3 bias = worldTracer.settings.getBias() * hitNormal;

   //if (kr < 1)
   //{
   //   arma::vec3 refractionDir = rrr::refract(ray.dir, hitNormal, 1.4f);
   //   //refractionDir = arma::normalise(refractionDir);

   //   arma::vec3 refractionRayOrig;
   //   if (true == outside) refractionRayOrig = hitPoint - bias;
   //   else refractionRayOrig = hitPoint + bias;

   //   Ray refractedRay{ refractionRayOrig, refractionDir, Ray::RayType::REFRACT };

   //   Intersection inter;
   //   refractionColor = worldTracer.castRay(refractedRay, 1);
   //   if (worldTracer.scene.trace(refractedRay, inter))
   //   {
   //     // refractionColor = { 1,0,1 };
   //   }
   //   else
   //      refractionColor = worldTracer.settings.getBackgroundColor().toArmaVec3F();
   //}

   //arma::vec3 reflectionDir = arma::normalise(rrr::reflect(ray.dir, hitNormal));

   //arma::vec3 reflectionRayOrig;
   //if (true == outside) reflectionRayOrig = hitPoint - bias;
   //else reflectionRayOrig = hitPoint + bias;

   //Ray reflectionRay{ reflectionRayOrig, reflectionDir, Ray::RayType::REFLECT };
   //Intersection inter;
   //arma::vec3 reflectionColor = worldTracer.castRay(reflectionRay); 
   ////if (worldTracer.scene.trace(reflectionRay, inter))
   //if(worldTracer.scene.trace(reflectionRay, inter, {object}))
   //{
   //   reflectionColor = reflectionColor * kr;
   //}
   //else
   //   reflectionColor = worldTracer.settings.getBackgroundColor().toArmaVec3F();

   //rVColor = refractionColor *(1 - kr) + reflectionColor;

   return rVColor;
}

