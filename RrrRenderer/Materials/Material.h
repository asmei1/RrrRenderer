#pragma once
#include <armadillo>
#include <Colors.h>

#define NOT_REFLECTIVE 0
#define NOT_REFRACTIVE 0

class Ray;
class WorldTracer;
class Object_A;

class Material
{
public:
   Material(float diffuseWeight = 0.8f, float specularWeight = 0.2f, float specularExponent = 10.0f);

   virtual arma::vec3 getShade(const arma::vec3& hitPoint, const Object_A* object, const Ray& ray, const WorldTracer& worldTracer) const;

   arma::vec3 getColor() const;
   //bool isReflective() const;
   //bool isRefractive() const;


   void setColor(const arma::vec3& color);
   void setColor(const RrrColor::RGBA& color);
   void setDiffuseWeight(float kd);
   void setSpecularWeight(float ks);
   void setSpecularExponent(float n);
   void setAmbientWeight(float ambient);

protected:
   arma::vec3 albedo{ 0.18, 0.18, 0.18 };
   float Kd = 0.8f; // phong model diffuse weight 
   float Ks = 0.2f; // phong model specular weight 
   float n = 10.f;   // phong specular exponent 
   float Ka = 0.1f;

   arma::vec3 color;
   
};
