#include "DirectionLight.h"

ShadingInfo DirectionLight::getLightInfo(const arma::vec3& hitPoint)
{
   ShadingInfo shInfo;
   shInfo.lightDirection = this->dir;
   shInfo.distance = std::numeric_limits<float>::max();
   //apply fallout
   shInfo.colorIntensity = this->intensity * this->color;

   return shInfo;
}

void DirectionLight::transform(const arma::mat44& matrix)
{
   assert(false && "Not implemented for now");
}

void DirectionLight::move(const arma::vec3& move)
{
   //point lighy is not affected to move
}

void DirectionLight::scale(const arma::vec3& scale)
{
   //point lighy is not affected to scale
}

void DirectionLight::rotate(const arma::vec3& rotate)
{
   assert(false && "Not implemented for now");
}

std::string DirectionLight::getDebugInfo() const
{
   return (std::string("DirectionLight: dir: (") + "x: " + std::to_string(this->dir.x()) + " y: " + std::to_string(this->dir.y()) + " z: " + std::to_string(this->dir.z()) + ")" +
      " Color: (" + this->getColor().getColorAsStr() + ") intensity: " + std::to_string(this->intensity));
}
