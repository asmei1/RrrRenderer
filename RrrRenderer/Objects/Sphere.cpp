#include "Sphere.h"
#include "Helpers/FunctionHelper.h"

bool Sphere::intersect(const Ray& ray, float& t) const
{
   float t0, t1;
#ifdef GEOMETRIC_SOLUTION
   arma::vec3 L = this->getPositionVec3() - ray.orig;
   float tca = static_cast<float>(arma::dot(L, ray.dir));

   if (tca < 0)
   {
      return false;
   }

   float d2 = static_cast<double>(arma::dot(L, L) - tca * tca);
   if (d2 > this->radius2)
   {
      return false;
   }
   float thc = sqrt(radius2 - d2);
   t0 = tca - thc;
   t1 = tca + thc;

#else
   // analytic solution
   arma::vec3 L = this->getPositionVec3() - ray.orig;

   float a = arma::dot(ray.dir, ray.dir);
   float b = 2 * arma::dot(ray.dir, L);
   float c = arma::dot(L, L) - radius2;
   if (!rrr::solveQuadratic(a, b, c, t0, t1))
   {
      return false;
   }

#endif // GEOMETRIC_SOLUTION


   if (t0 > t1)
   {
      std::swap(t0, t1);
   }

   if (t0 < 0)
   {
      t0 = t1;
      if (t1 < 0)
      {
         return false;
      }
   }

   t = t0;

   return true;
}

std::string Sphere::getDebugInfo() const
{
   arma::vec3 pos = this->getPositionVec3();
   return (std::string("Sphere: pos: (") + "x: " + std::to_string(pos.x()) + " y: " + std::to_string(pos.y()) + " z: " + std::to_string(pos.z()) + ")" +
      " Color: (" + RrrColor::RGBA::fromArmaVec3F(this->material->getColor()).getColorAsStr() + ") radius: " + std::to_string(this->radius));
}

void Sphere::getSurfaceData(const arma::vec3& hitPoint, const arma::vec3& viewDirection, arma::vec3& hitNormal, arma::vec2& hitTextureCoordinate) const
{
   //get normal
   hitNormal = arma::normalise(hitPoint - this->getPositionVec3());
   // In this particular case, the normal is simular to a point on a unit sphere
   // centred around the origin. We can thus use the normal coordinates to compute
   // the spherical coordinates of pHit.
   // atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
   // acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
   hitTextureCoordinate.x() = (1 + atan2(hitNormal.z(), hitNormal.x()) / PI) * 0.5;
   hitTextureCoordinate.y() = acosf(hitNormal.y()) / PI;
}

arma::dvec4 Sphere::getPositionVec4() const
{
   assert(this->posRefIndex != -1 && "Wrong index of position");

   return allObjectsPositionMatrix->col(this->posRefIndex);
}

arma::dvec3 Sphere::getPositionVec3() const
{
   assert(this->posRefIndex != -1 && "Wrong index of position");

   arma::dvec4 temp = allObjectsPositionMatrix->col(this->posRefIndex);
   return arma::dvec3{ temp.x(), temp.y(), temp.z() };
}

void Sphere::transform(const arma::mat44& matrix)
{
   assert(false && "Not implemented yet");
}

void Sphere::scale(const arma::vec3& scale)
{
   assert(false && "Not implemented yet");
}

void Sphere::rotate(const arma::vec3& rotate)
{
   assert(false && "Not implemented yet");
}

void Sphere::move(const arma::vec3& move)
{
   assert(false && "Not implemented yet");
}
