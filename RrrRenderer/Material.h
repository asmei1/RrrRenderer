#pragma once
#include <armadillo>

#define NOT_REFLECTIVE 0
#define NOT_REFRACTIVE 0

struct Material
{
   arma::vec3 diffuse;
   float refractive;
   float reflective;

   bool isReflective() const
   {
      return this->reflective != NOT_REFLECTIVE;
   }

   bool isRefractive() const
   {
      return this->refractive != NOT_REFLECTIVE;
   }

   static const Material* getMaterialFromString(const std::string& mat);
};
const static inline Material testingMaterial{ {0.18f, 0.18f, 0.18f}, NOT_REFRACTIVE, NOT_REFLECTIVE };
const static inline Material ReflectiveMaterial{ {0.4f, 0.4f, 0.4f}, NOT_REFRACTIVE, 0.5f };
const static inline Material ReflectiveMaxMaterial{ {0.4f, 0.4f, 0.4f}, NOT_REFRACTIVE, 1.5f };
const static inline Material GlassMaterial{ {0.4f, 0.4f, 0.4f}, 1.5f, 0.5f };
