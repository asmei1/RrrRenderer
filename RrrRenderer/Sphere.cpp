#include "Sphere.h"


bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
   float discr = b * b - 4 * a * c;
   if (discr < 0)
   {
      return false;
   }
   if (discr == 0)
   {
      x0 = x1 = -0.5 * b / a;
   }
   else
   {
      float q = (b > 0) ?
         -0.5 * (b + sqrt(discr)) :
         -0.5 * (b - sqrt(discr));
      x0 = q / a;
      x1 = c / q;
   }

   return true;
}

bool Sphere::intersect(const Ray& ray, float& t) const
{
   float t0, t1;
#ifdef GEOMETRIC_SOLUTION
   arma::vec3 L = this->getPositionVec3() - ray.orig;
   float tca = arma::dot(L, ray.dir);

   if (tca < 0)
   {
      return false;
   }

   float d2 = arma::dot(L, L) - tca * tca;
   if (d2 > this->radius2)
   {
      return false;
   }
   float thc = sqrt(radius2 - d2);
   t0 = tca - thc;
   t1 = tca + thc;

#else
   // analytic solution
   arma::vec3 L = this->position - ray.orig;

   float a = arma::dot(ray.dir, ray.dir);
   float b = 2 * arma::dot(ray.dir, L);
   float c = arma::dot(L, L) - radius2;
   if (!solveQuadratic(a, b, c, t0, t1))
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

void Sphere::getSurfaceData(const arma::vec3& pHit, arma::vec3& nHit, arma::vec2& tex) const
{
   nHit = pHit - this->getPositionVec3();
   nHit = arma::normalise(nHit);
   // In this particular case, the normal is simular to a point on a unit sphere
   // centred around the origin. We can thus use the normal coordinates to compute
   // the spherical coordinates of pHit.
   // atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
   // acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
   tex.x() = (1 + atan2(nHit.z(), nHit.x()) / PI) * 0.5;
   tex.y() = acosf(nHit.y()) / PI;
}

arma::dvec4 Sphere::getPositionVec4() const
{
   assert(this->posRefIndex != -1 && "Wrong index of position");

   return allObjectsPositionMatrix.col(this->posRefIndex);
}

arma::dvec3 Sphere::getPositionVec3() const
{
   assert(this->posRefIndex != -1 && "Wrong index of position");

   arma::dvec4 temp = allObjectsPositionMatrix.col(this->posRefIndex);
   return arma::dvec3{ temp.x(), temp.y(), temp.z() };
}

void Sphere::move(const arma::vec3& move)
{
}
