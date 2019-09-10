#include "Renderer.h"
#include "Sphere.h"
#include "Helpers/FunctionHelper.h"
#include "DirectionLight.h"
#include "IntersectionInfo.h"
#include <Material.h>

Renderer::Renderer()
{
   this->camera.lookAt({ 0, 0, -1 });
}

void Renderer::prepareScene()
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(.2, 1);
   std::uniform_real_distribution<> disAlbedo(.05, .4);
   std::uniform_real_distribution<> disPos(-5, 5);

   this->settings.setBackgroundColor({ 153,190,210 });

   //lights
   this->scene.createDirectionalLight({ 1, -1, 0 }, 5, RrrColor::White);
   //this->scene.createDirectionalLight({ 1, -.5, .2 }, 4, RrrColor::White);
   //this->scene.createDirectionalLight({ 1, -1, 0 }, 5, RrrColor::White);
   //this->scene.createDirectionalLight({ -1, -1, 0 }, 5, RrrColor::Red);
   //this->scene.createDirectionalLight({ 0, -.8, .5 }, 5, RrrColor::Blue);

   //this->scene.createPointLight({ -2.5, 1.8, -4.1 }, 50, RrrColor::White);

   //objects

   //for (int i = 0; i < 20; i++)
   //{
   //   //    this->scene.createSphere(arma::vec3{ disPos(rd), disPos(rd), disPos(rd) - 6 }, dis(rd), disAlbedo(rd));
   //}
   ////this->scene.createSphere(arma::vec3{ -0.8, 0, -5 }, 0.7f);
   this->scene.createSphere(arma::vec3{ 0, 1.2, -4.4 }, 1, &testingMaterial);
   //this->scene.createSphere(arma::vec3{ 0, 1.2, -4.2 }, 0.5, GlassMaterial);
   //this->scene.createSphere(arma::vec3{ 0, 1.2, -4.2 }, 0.3, GlassMaterial);
   ////this->scene.createSphere(arma::vec3{ 0, -3.5, -4.5 }, 3.4, GlassMaterial, RrrColor::White);
   this->scene.createSphere(arma::vec3{ 0, -3.5, -4.5 }, 3.4, &ReflectiveMaterial, RrrColor::White);
   this->scene.createSphere(arma::vec3{ 4.3, 0, -4.7 }, 3, &ReflectiveMaterial, RrrColor::Green);

}

bool Renderer::loadSceneFromFile(const std::filesystem::path& scene)
{
   bool rV = false;
   std::vector<std::string> description;

   if (true == std::filesystem::exists(scene))
   {
      std::ifstream in(scene);
      std::string line;
      while (std::getline(in, line))
      {
         description.push_back(line);
      }
      rV = true;

      this->prepareScene(description);
   }

   return rV;
}

void Renderer::prepareScene(const std::vector<std::string>& sceneDescription)
{
   //camera
   const std::string cameraViewDirProp = "camViewDir";
   const std::string worldTranslateProp = "worldTranslate";
   const std::string worldPitchProp = "worldPitch";
   const std::string worldYawProp = "worldYaw";
   const std::string worldRollProp = "worldRoll";
   std::optional<arma::vec3> camViewDirVal = std::nullopt;
   std::optional<arma::vec3> worldTransVal = std::nullopt;
   std::optional<float> worldPitchVal = std::nullopt;
   std::optional<float> worldYawVal = std::nullopt;
   std::optional<float> worldRollVal = std::nullopt;


   const std::string backgroundProp = "backgroundColor";
   const std::string sizeProp = "size";

   const std::string distantLightObj = "disLight";
   const std::string intensityObj = "intensity";

   const std::string sphereObj = "sph";
   const std::string radiusObj = "radius";

   const std::string coordinatesObj = "pos";
   const std::string directionObj = "dir";
   const std::string materialObj = "mat";
   const std::string colorObj = "color";

   auto parseVec3 = [](const std::vector<std::string>& tokens, size_t index = 0) -> arma::vec3
   {
      arma::vec3 rV;
      try
      {
         rV.x() = std::stof(tokens[index + 1]);
         rV.y() = std::stof(tokens[index + 2]);
         rV.z() = std::stof(tokens[index + 3]);
      }
      catch (...)
      {
         assert(false && "Cannot parse vector");
      }
      return rV;
   };

   auto parseRrrColor = [](const std::vector<std::string>& tokens, size_t index = 0/*, bool rgba = false*/)->RrrColor::RGBA
   {
      RrrColor::RGBA rV;
      try
      {
         rV.r = std::stoi(tokens[index + 1]);
         rV.g = std::stoi(tokens[index + 2]);
         rV.b = std::stoi(tokens[index + 3]);
         /*      if(true == rgba)
               {
                  rV.a = std::stoi(tokens[index + 4]);
               }
         */
      }
      catch (...)
      {
         assert(false && "Cannot parse color");
      }
      return rV;
   };


   for (const auto line : sceneDescription)
   {
      if (line.empty())
      {
         continue;
      }

      //comment
      if (line[0] == '#')
      {
         continue;
      }

      auto tokens = rrr::split(line);

      //trim tokens
      for (auto& tok : tokens)
      {
         rrr::trim(tok);
      }

      if (true == tokens.empty())
      {
         continue;
      }
      if (sphereObj == tokens[0])
      {
         const Material* material = &testingMaterial;
         RrrColor::RGBA color = RrrColor::randomColor();
         arma::vec3 coords;
         coords.zeros();
         float radius = 1;
         for (size_t i = 1; i < tokens.size(); ++i)
         {
            if (coordinatesObj == tokens[i])
            {
               coords = parseVec3(tokens, i);

               i += 3;
            }
            else if (materialObj == tokens[i])
            {
               std::string type = tokens[i + 1];
               if ("testing" == type)
               {
                  material = &testingMaterial;
               }
               else if ("glass" == type)
               {
                  material = &GlassMaterial;
               }
               else if ("reflect" == type)
               {
                  material = &ReflectiveMaterial;
               }

               i += 1;
            }
            else if (colorObj == tokens[i])
            {
               color = parseRrrColor(tokens, i);
            }
            else if (radiusObj == tokens[i])
            {
               radius = std::stof(tokens[i + 1]);

               i += 1;
            }

         }
         //create sphere
         this->scene.createSphere(coords, radius, material, color);
      }
      else if (distantLightObj == tokens[0])
      {
         RrrColor::RGBA color = RrrColor::White;
         arma::vec3 dir;
         dir.zeros();


         //todo change it to vec, now is float
         //arma::vec3 intensity;
         float intensity = 1;

         for (size_t i = 1; i < tokens.size(); ++i)
         {
            if (directionObj == tokens[i])
            {
               dir = parseVec3(tokens, i);

               i += 3;
            }
            else if (intensityObj == tokens[i])
            {
               intensity = std::stof(tokens[i + 1]);

               i += 1;
            }
            else if (colorObj == tokens[i])
            {
               color = parseRrrColor(tokens, i);
            }
         }

         this->scene.createDirectionalLight(dir, intensity, color);
      }
      else if (backgroundProp == tokens[0])
      {
         RrrColor::RGBA bgColor = parseRrrColor(tokens);

         this->settings.setBackgroundColor(bgColor);
      }
      else if (sizeProp == tokens[0])
      {
         int width = std::stoi(tokens[1]);
         int height = std::stoi(tokens[2]);

         this->settings.setWidth(width);
         this->settings.setHeight(height);
      }
      else if (cameraViewDirProp == tokens[0])
      {
         camViewDirVal.emplace(arma::vec3{ parseVec3(tokens) });
      }
      else if (worldTranslateProp == tokens[0])
      {
         worldTransVal.emplace(arma::vec3{ parseVec3(tokens) });
      }
      else if (worldPitchProp == tokens[0])
      {
         worldPitchVal.emplace(std::stof(tokens[1]));
      }
      else if (worldYawProp == tokens[0])
      {
         worldYawVal.emplace(std::stof(tokens[1]));
      }
      else if (worldRollProp == tokens[0])
      {
         worldRollVal.emplace(std::stof(tokens[1]));
      }
   }

   if(camViewDirVal)
   {
      this->camera.lookAt(*camViewDirVal);
   }
   if(worldTransVal)
   {
      this->scene.translate(*worldTransVal);
   }
   if(worldPitchVal)
   {
      this->scene.pitch(*worldPitchVal);
   }   
   if(worldYawVal)
   {
      this->scene.yaw(*worldYawVal);
   }   
   if(worldRollVal)
   {
      this->scene.roll(*worldRollVal);
   }

}

void Renderer::render()
{
   int counter = 0;
   BMPImg img{ this->settings.getWidth(), this->settings.getHeight(), RrrColor::White, true };

   float scale = tan(rrr::deg2rad(this->settings.getFOV() * 0.5f));
   float imageRatio = this->settings.getRatio();

   //arma::vec3 orig;
   arma::dmat44 viewMatrix = this->camera.getViewMatrix();
   this->scene.transformWorld(viewMatrix);



   arma::vec3 color;
   for (uint32_t j = 0; j < this->settings.getHeight(); ++j)
   {
      for (uint32_t i = 0; i < this->settings.getWidth(); ++i)
      {
         float x = (2 * (i + 0.5f) / static_cast<float>(this->settings.getWidth()) - 1) * scale * imageRatio;
         float y = (1 - 2 * (j + 0.5f) / static_cast<float>(this->settings.getHeight())) * scale;

         arma::vec3 dir;
         //compute direction of ray
         rrr::multDirMatrixCM(viewMatrix, arma::vec3{ x, y, -1.f }, dir); //-1 is from picture plane distance

         dir = arma::normalise(dir);
         color = castRay(this->camera.getEyePosition(), dir, this->scene.getObjects(), this->scene.getLights());

         img.set(i, j, RrrColor::RGBA::fromArmaVec3F(color));
      }
   }
   img.flipVertical();
   img.save(std::string("./test/renderTriangle") + /*std::to_string(counter++) +*/ ".bmp");

   Ray::printInfo();
   std::cout << this->scene << std::endl;
}
//
//inline
//arma::vec3 mix(const RrrColor::RGBA& a, const float& mixValue)
//{
//   arma::vec3 r;
//   r.x() = a.r   * (1 - mixValue) + 0.8 * a.r * mixValue;
//   r.y() = a.g * (1 - mixValue) + 0.8 * a.g * mixValue;
//   r.z() = a.b  * (1 - mixValue) + 0.8 * a.b * mixValue;
//   return r;
//}

arma::vec3 Renderer::castRay(const arma::vec3& orig, const arma::vec3& dir, const std::vector<ObjectUptr>& objects, const std::vector<LightUptr>& lights, const uint8_t& depth)
{
   arma::vec3 hitColor = arma::vec3{ 0, 0, 0 };
   if (depth > this->settings.getMaxDepth())
   {
      hitColor = this->settings.getBackgroundColor().toArmaVec3F();
   }
   else
   {
      //IntersectionInfo interObjInfo;
      //if (trace({ orig, dir, Ray::RayType::PRIMARY }, objects, interObjInfo))
      //{
      //   //shaded point
      //   arma::vec3 hitPoint = orig + dir * interObjInfo.tNear;

      //   arma::vec3 hitNormal{ 0, 0, 0 };
      //   arma::vec3 viewingDirection{ 0, 0, 0 };
      //   arma::vec2 hitTextureCoordinates{ 0, 0 };

      //   interObjInfo.hitObject->getSurfaceData(hitPoint, viewingDirection, hitNormal, hitTextureCoordinates);

      //   for (const auto& light : lights)
      //   {
      //      ShadingInfo shInfo = light->getLightInfo(hitPoint);
      //      IntersectionInfo shadowIntersectionInfo;

      //      //else
      //      //if (false == trace({ hitPoint + (hitNormal * this->settings.getBias()), -shInfo.lightDirection, Ray::RayType::SHADOW }, objects, shadowIntersectionInfo))
      //      

      //      if (true == interObjInfo.hitObject->material->isReflective() && true == interObjInfo.hitObject->material->isRefractive())
      //      {
      //         arma::vec3 refractionColor;
      //         refractionColor.zeros();

      //         float kr;
      //         rrr::fresnel(viewingDirection, hitNormal, interObjInfo.hitObject->material->refractive, kr);
      //         bool outside = arma::dot(viewingDirection, hitNormal) > 0;
      //         arma::vec3 bias = this->settings.getBias() * hitNormal;

      //         if(kr < 1)
      //         {
      //            arma::vec3 refractionDir = rrr::refract(viewingDirection, hitNormal, interObjInfo.hitObject->material->refractive);
      //            
      //            arma::vec3 refractionRayOrig;
      //            if (true == outside) refractionRayOrig = hitPoint - bias;
      //            else refractionRayOrig = hitPoint + bias;

      //            refractionColor = castRay(refractionRayOrig, refractionDir, objects, lights, depth + 1);
      //         }

      //         arma::vec3 reflectionDir = arma::normalise(rrr::reflect(viewingDirection, hitNormal));

      //         arma::vec3 reflectionRayOrig;
      //         if (true == outside) reflectionRayOrig = hitPoint - bias;
      //         else reflectionRayOrig = hitPoint + bias;

      //         arma::vec3 reflectionColor = castRay(reflectionRayOrig, reflectionDir, objects, lights, depth + 1);

      //         hitColor += reflectionColor * kr + refractionColor * (1 - kr);
      //      }
      //      else if (true == interObjInfo.hitObject->material->isReflective())
      //      {
      //         arma::vec3 R = rrr::reflect(viewingDirection, hitNormal);
      //         hitColor += 0.8 * castRay(hitPoint + hitNormal * this->settings.getBias(), R, objects, lights, depth + 1);
      //      }
      //      else if (false == trace({ hitPoint + (hitNormal * this->settings.getBias()), -shInfo.lightDirection, Ray::RayType::SHADOW }, objects, shadowIntersectionInfo));
      //      {
      //         double temp = std::max(0.0, arma::dot(hitNormal, -shInfo.lightDirection));
      //         hitColor += (interObjInfo.hitObject->getColor().toArmaVec3F() % interObjInfo.hitObject->material->diffuse % shInfo.colorIntensity) * temp;
      //      }

      //      //std::cout << hitColor.toArmaVec() << std::endl;
      //   }
      //}
      //else
      //{
      //   hitColor = this->settings.getBackgroundColor().toArmaVec3F();
      //}
      IntersectionInfo interObjInfo;
      if (trace({ orig, dir, Ray::RayType::PRIMARY }, objects, interObjInfo))
      {
         //shaded point
         arma::vec3 hitPoint = orig + dir * interObjInfo.tNear;

         arma::vec3 hitNormal{ 0, 0, 0 };
         arma::vec2 hitTextureCoordinates{ 0, 0 };

         interObjInfo.hitObject->getSurfaceData(hitPoint, dir, hitNormal, hitTextureCoordinates);


         if (true == interObjInfo.hitObject->material->isReflective() && true == interObjInfo.hitObject->material->isRefractive())
         {
            arma::vec3 refractionColor;
            refractionColor.zeros();

            float kr = rrr::fresnel(dir, hitNormal, interObjInfo.hitObject->material->refractive);
            bool outside = arma::dot(dir, hitNormal) < 0;
            arma::vec3 bias = this->settings.getBias() * hitNormal;

            if (kr < 1)
            {
               arma::vec3 refractionDir = rrr::refract(dir, hitNormal, interObjInfo.hitObject->material->refractive);
               refractionDir = arma::normalise(refractionDir);

               arma::vec3 refractionRayOrig;
               if (true == outside) refractionRayOrig = hitPoint - bias;
               else refractionRayOrig = hitPoint + bias;

               refractionColor = castRay(refractionRayOrig, refractionDir, objects, lights, depth + 1);
            }

            arma::vec3 reflectionDir = arma::normalise(rrr::reflect(dir, hitNormal));

            arma::vec3 reflectionRayOrig;
            if (true == outside) reflectionRayOrig = hitPoint - bias;
            else reflectionRayOrig = hitPoint + bias;

            arma::vec3 reflectionColor = castRay(reflectionRayOrig, reflectionDir, objects, lights, depth + 1);

            hitColor += reflectionColor * kr + refractionColor * (1 - kr);
         }
         else if (true == interObjInfo.hitObject->material->isReflective())
         {
            arma::vec3 R = rrr::reflect(dir, hitNormal);
            hitColor += 0.8 * castRay(hitPoint + hitNormal * this->settings.getBias(), R, objects, lights, depth + 1);
         }
         else
         {
            for (const auto& light : lights)
            {
               ShadingInfo shInfo = light->getLightInfo(hitPoint);
               IntersectionInfo shadowIntersectionInfo;
               if (false == trace({ hitPoint + (hitNormal * this->settings.getBias()), -shInfo.lightDirection, Ray::RayType::SHADOW }, objects, shadowIntersectionInfo))
               {
                  double temp = std::max(0.0, arma::dot(hitNormal, -shInfo.lightDirection));
                  if (true == interObjInfo.hitObject->material->isReflective())
                     hitColor += (interObjInfo.hitObject->material->diffuse % shInfo.colorIntensity) * temp;
                  else
                     hitColor += (interObjInfo.hitObject->getColor().toArmaVec3F() % interObjInfo.hitObject->material->diffuse % shInfo.colorIntensity) * temp;

               }
            }

            //std::cout << hitColor.toArmaVec() << std::endl;
         }
      }
      else
      {
         hitColor = this->settings.getBackgroundColor().toArmaVec3F();
      }
   }

   return hitColor;
}

bool Renderer::trace(const Ray& ray, const std::vector<ObjectUptr>& objects, IntersectionInfo& interObjInfo)
{
   //todo export this
   std::vector<std::unique_ptr<Object_A>>::const_iterator iter = objects.begin();
   for (; objects.cend() != iter; ++iter)
   {
      float t = std::numeric_limits<float>::max();
      if ((*iter)->intersect(ray, t) && t < interObjInfo.tNear) {
         if (Ray::RayType::SHADOW == ray.type
            && true == (*iter)->material->isReflective()
            && true == (*iter)->material->isRefractive())
         {
            continue;
         }
         interObjInfo.hitObject = iter->get();
         interObjInfo.tNear = t;
      }
   }

   return interObjInfo.hitObject != nullptr;
}
