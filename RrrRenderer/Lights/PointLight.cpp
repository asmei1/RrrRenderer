#include "PointLight.h"
#include <assert.h>

ShadingInfo PointLight::getLightInfo(const arma::vec3& hitPoint)
{
   ShadingInfo shInfo;
   shInfo.lightDirection = hitPoint - this->pos;

   float magnitude = static_cast<float>(arma::norm(shInfo.lightDirection));
   shInfo.distance = std::sqrtf(magnitude);

   //normalise 
   //shInfo.lightDirection = arma::normalise(shInfo.lightDirection);
   shInfo.lightDirection.x() /= shInfo.distance;
   shInfo.lightDirection.y() /= shInfo.distance;
   shInfo.lightDirection.z() /= shInfo.distance;

   //apply fallout
   shInfo.colorIntensity = (this->color * this->intensity) / (4 * PI * magnitude);

   return shInfo;
}

void PointLight::transform(const arma::mat44& matrix)
{
   assert(false && "Not implemented for now");
}

void PointLight::move(const arma::vec3& move)
{
   assert(false && "Not implemented for now");
}

void PointLight::scale(const arma::vec3& scale)
{
   //point lighy is not affected to rotate
}

void PointLight::rotate(const arma::vec3& rotate)
{
   //point lighy is not affected to rotate
}

std::string PointLight::getDebugInfo() const
{
   return (std::string("PointLight: pos: (") + "x: " + std::to_string(this->pos.x()) + " y: " + std::to_string(this->pos.y()) + " z: " + std::to_string(this->pos.z()) + ")" +
      " Color: (" + this->getColor().getColorAsStr() + ") intensity: " + std::to_string(this->intensity) );
}
