#pragma once
#include <armadillo>
#include <filesystem>
#include <optional>

#include "Scene.h"
#include "Settings.h"
#include "Object_A.h"
#include "Light_A.h"
#include "Ray.h"
#include "IntersectionInfo.h"
#include "BMPImg.h"
#include "Sphere.h"

class Renderer
{
public:
   Renderer();

   void prepareScene();
   void prepareScene(const std::vector<std::string>& sceneDescription);
   bool loadSceneFromFile(const std::filesystem::path& scene);

   void render();
   arma::vec3 castRay(const arma::vec3& orig, const arma::vec3& dir, const std::vector<ObjectUptr>& objects, const std::vector<LightUptr>& lights, const uint8_t& depth = 0);
   bool trace(const Ray& ray, const std::vector<ObjectUptr>& objects, IntersectionInfo& interObjInfo);

private:
   Camera camera;
   Scene scene;
   Settings settings{840, 680, 60, RrrColor::Black, 10};
};

