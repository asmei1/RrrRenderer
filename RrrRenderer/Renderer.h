#pragma once
#include <armadillo>
#include <filesystem>
#include <optional>

#include "Scene.h"
#include "Settings.h"
#include "Ray.h"
#include "Intersection.h"
#include "BMPImg.h"
#include "WorldTracer.h"

class Renderer
{
public:
   Renderer();

   //void prepareScene();
   void prepareScene(const std::string& sceneDescription);
   bool loadSceneFromFile(const std::filesystem::path& scene);

   void render(const std::string & fileName, bool debugInfo = false);

private:
   WorldTracer worldTracer;
   Camera camera;
   Scene scene;
   Settings settings{840, 680, 60, RrrColor::Black, 10};
};

