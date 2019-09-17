#pragma once
#include "Settings.h"
#include "Ray.h"
#include "Scene.h"
#include "Objects/Object_A.h"
#include "Lights/Light_A.h"

class WorldTracer
{
public:
   WorldTracer(const Settings& _settings, const Scene& _scene)
      : settings(_settings), scene(_scene)
   {}

   arma::vec3 castRay(const Ray& ray, const uint8_t& depth = 0) const;

   const Settings& settings;
   const Scene& scene;
};

