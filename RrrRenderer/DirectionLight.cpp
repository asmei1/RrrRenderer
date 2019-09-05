#include "DirectionLight.h"

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
