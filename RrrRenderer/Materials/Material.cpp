#include "Material.h"
#include <Objects/Object_A.h>
#include <Ray.h>
#include "Lights/Light_A.h"
#include "WorldTracer.h"
#include "Intersection.h"

Material::Material(float diffuseWeight, float specularWeight, float specularExponent)
   : Kd(diffuseWeight), Ks(specularWeight), n(specularExponent)
{
}

arma::vec3 Material::getShade(const arma::vec3& hitPoint, const Object_A* object, const Ray& ray, const WorldTracer& worldTracer) const
{
   arma::vec3 rVColor{ 0,0,0 };
   arma::vec3 specularColor{ 0,0,0 };
   arma::vec3 diffuseColor{ 0,0,0 };

   arma::vec3 hitNormal{ 0, 0, 0 };
   arma::vec2 hitTextureCoordinates{ 0, 0 };

   object->getSurfaceData(hitPoint, ray.dir, hitNormal, hitTextureCoordinates);

   for (const auto& light : worldTracer.scene.getLights())
   {
      ShadingInfo shInfo = light->getLightInfo(hitPoint);
      Intersection shadowIntersectionInfo;
      Ray shadowRay{ hitPoint + (hitNormal * worldTracer.settings.getBias()), -shInfo.lightDirection, Ray::RayType::SHADOW };
      if (false == worldTracer.scene.trace(shadowRay, shadowIntersectionInfo, { object }))
      {

         //diffuse
         /*double temp = std::fmax(0.0, arma::dot(hitNormal, -shInfo.lightDirection));
         diffuseColor += this->albedo % this->color % shInfo.colorIntensity * temp;
*/
         //specular
         arma::vec3 reflectVec = rrr::reflect(shInfo.lightDirection, hitNormal);
         specularColor += shInfo.colorIntensity % this->color * std::powf(std::max(0.0, arma::dot(reflectVec, -ray.dir)), this->n);

      }
   }

   rVColor = diffuseColor * this->Kd + specularColor * this->Ks + this->color * this->Ka;
   return rVColor;
}
arma::vec3 Material::getColor() const
{
   return this->color;
}

//bool Material::isReflective() const
//{
//   return this->reflective != NOT_REFLECTIVE;
//}
//
//bool Material::isRefractive() const
//{
//   return this->refractive != NOT_REFLECTIVE;
//}

void Material::setColor(const arma::vec3& color)
{
   this->color = color;
}

void Material::setColor(const RrrColor::RGBA& color)
{
   this->color = color.toArmaVec3F();
}

void Material::setDiffuseWeight(float kd)
{
   this->Kd = kd;
}

void Material::setSpecularWeight(float ks)
{
   this->Ks = ks;
}

void Material::setSpecularExponent(float n)
{
   this->n = n;
}

void Material::setAmbientWeight(float ambient)
{
   this->Ka = ambient;
}

