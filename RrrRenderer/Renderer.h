#pragma once
#include <armadillo>
#include "Scene.h"
#include "Settings.h"
#include "Object_A.h"
#include "Ray.h"
#include "BMPImg.h"
#include "Sphere.h"

class Renderer
{
public:
   Renderer(){};

   void prepareScene();

   void render();
   RrrColor::RGBA castRay(const Ray& ray, const std::vector<ObjectUptr>& objects);
   bool trace(const Ray& ray, const std::vector<ObjectUptr>& objects, float& tNear, const Object_A *& hitObject);

private:
   Camera camera;
   Scene scene;
   Settings settings{840, 680, 60, RrrColor::Black};
};

