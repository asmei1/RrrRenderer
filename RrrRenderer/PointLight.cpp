#include "PointLight.h"
#include <assert.h>

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
