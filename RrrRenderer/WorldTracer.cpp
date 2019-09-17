#include "WorldTracer.h"
#include "Intersection.h"
#define ONLY_PRIMARY_RAYS 1
#define SHADOW_RAYS 2
#define ALL 100

#define TYPE_OF_RENDERING ALL

arma::vec3 WorldTracer::castRay(const Ray & ray, const uint8_t & depth) const
{
   arma::vec3 hitColor = arma::vec3{ 0, 0, 0 };
   if (depth > this->settings.getMaxDepth())
   {
      hitColor = this->settings.getBackgroundColor().toArmaVec3F();
   }
   else
   {
      Intersection interObjInfo;

#if TYPE_OF_RENDERING == ONLY_PRIMARY_RAYS
      if (true == this->scene.trace(ray, interObjInfo))
      {
         arma::vec3 hitPoint = ray.orig + ray.dir * interObjInfo.tNear;
         //arma::vec3 hitNormal{ 0, 0, 0 };
         hitColor = interObjInfo.hitObject->material->getColor();
      }
      else
      {
         hitColor = this->settings.getBackgroundColor().toArmaVec3F();
      }
#elif TYPE_OF_RENDERING == SHADOW_RAYS
      if (this->scene.trace(ray, interObjInfo))
      {
         //shaded point
         arma::vec3 hitPoint = ray.orig + ray.dir * interObjInfo.tNear;

         arma::vec3 hitNormal{ 0, 0, 0 };
         arma::vec2 hitTextureCoordinates{ 0, 0 };

         interObjInfo.hitObject->getSurfaceData(hitPoint, ray.dir, hitNormal, hitTextureCoordinates);



         for (const auto& light : this->scene.getLights())
         {
            ShadingInfo shInfo = light->getLightInfo(hitPoint);
            Intersection shadowIntersectionInfo;
            if (false == this->scene.trace({ hitPoint + (hitNormal * this->settings.getBias()), -shInfo.lightDirection, Ray::RayType::SHADOW }, shadowIntersectionInfo, {interObjInfo.hitObject}))
            {
               double temp = std::max(0.0, arma::dot(hitNormal, -shInfo.lightDirection));
               hitColor += interObjInfo.hitObject->material->getColor() % shInfo.colorIntensity * temp;

            }
         }
         //std::cout << hitColor.toArmaVec() << std::endl;
      }
      else
      {
         hitColor = this->settings.getBackgroundColor().toArmaVec3F();
      }

#elif TYPE_OF_RENDERING == ALL
      if (this->scene.trace(ray, interObjInfo))
      {
         //shaded point
         arma::vec3 hitPoint = ray.orig + ray.dir * interObjInfo.tNear;

         hitColor = interObjInfo.hitObject->material->getShade(hitPoint, interObjInfo.hitObject, ray, *this);

         //std::cout << hitColor.toArmaVec() << std::endl;
      }
      else
      {
         hitColor = this->settings.getBackgroundColor().toArmaVec3F();
      }
#endif
   }

   return hitColor;
}
