#include "Renderer.h"
#include "Helpers/FunctionHelper.h"
#include "Intersection.h"
#include <Materials/MaterialSimpleFactory.h>

Renderer::Renderer()
   : worldTracer(this->settings, this->scene)
{
   this->camera.lookAt({ 0, 0, -1 });
}

//void Renderer::prepareScene()
//{
//   std::random_device rd;
//   std::mt19937 gen(rd());
//   std::uniform_real_distribution<> dis(.2, 1);
//   std::uniform_real_distribution<> disAlbedo(.05, .4);
//   std::uniform_real_distribution<> disPos(-5, 5);
//
//   this->settings.setBackgroundColor({ 153,190,210 });
//
//   //lights
//   this->scene.createDirectionalLight({ 1, -1, 0 }, 5, RrrColor::White);
//   //this->scene.createDirectionalLight({ 1, -.5, .2 }, 4, RrrColor::White);
//   //this->scene.createDirectionalLight({ 1, -1, 0 }, 5, RrrColor::White);
//   //this->scene.createDirectionalLight({ -1, -1, 0 }, 5, RrrColor::Red);
//   //this->scene.createDirectionalLight({ 0, -.8, .5 }, 5, RrrColor::Blue);
//
//   //this->scene.createPointLight({ -2.5, 1.8, -4.1 }, 50, RrrColor::White);
//
//   //objects
//
//   //for (int i = 0; i < 20; i++)
//   //{
//   //   //    this->scene.createSphere(arma::vec3{ disPos(rd), disPos(rd), disPos(rd) - 6 }, dis(rd), disAlbedo(rd));
//   //}
//   ////this->scene.createSphere(arma::vec3{ -0.8, 0, -5 }, 0.7f);
//   this->scene.createSphere(arma::vec3{ 0, 1.2, -4.4 }, 1, &testingMaterial);
//   //this->scene.createSphere(arma::vec3{ 0, 1.2, -4.2 }, 0.5, GlassMaterial);
//   //this->scene.createSphere(arma::vec3{ 0, 1.2, -4.2 }, 0.3, GlassMaterial);
//   ////this->scene.createSphere(arma::vec3{ 0, -3.5, -4.5 }, 3.4, GlassMaterial, RrrColor::White);
//   this->scene.createSphere(arma::vec3{ 0, -3.5, -4.5 }, 3.4, &ReflectiveMaterial, RrrColor::White);
//   this->scene.createSphere(arma::vec3{ 4.3, 0, -4.7 }, 3, &ReflectiveMaterial, RrrColor::Green);
//
//}

bool Renderer::loadSceneFromFile(const std::filesystem::path& scene)
{
   bool rV = false;
   std::string description;

   if (true == std::filesystem::exists(scene))
   {
      std::ifstream in(scene);
      std::string line;
      while (std::getline(in, line))
      {
         description += line + "\r\n";
      }
      rV = true;

      this->prepareScene(description);
   }

   return rV;
}

void Renderer::render(const std::string& fileName, bool debug)
{
   int counter = 0;
   BMPImg img{ this->settings.getWidth(), this->settings.getHeight(), RrrColor::White, true };

   float scale = static_cast<float>(tan(rrr::deg2rad(this->settings.getFOV() * 0.5f)));
   float imageRatio = this->settings.getRatio();

   //Look at
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

         Ray primaryRay{ this->camera.getEyePosition(), dir, Ray::RayType::PRIMARY };
         //color = castRay(this->camera.getEyePosition(), dir, this->scene.getObjects(), this->scene.getLights());
         color = this->worldTracer.castRay(primaryRay);

         img.set(i, j, RrrColor::RGBA::fromArmaVec3F(color));
      }
   }
   img.flipVertical();
   img.save(fileName);

   if(true == debug)
   {
      Ray::printInfo();
      std::cout << this->scene << std::endl;
   }
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
//
//arma::vec3 Renderer::castRay(const arma::vec3& orig, const arma::vec3& dir, const std::vector<ObjectUptr>& objects, const std::vector<LightUptr>& lights, const uint8_t& depth)
//{
//   arma::vec3 hitColor = arma::vec3{ 0, 0, 0 };
//   if (depth > this->settings.getMaxDepth())
//   {
//      hitColor = this->settings.getBackgroundColor().toArmaVec3F();
//   }
//   else
//   {
//      Intersection interObjInfo;
//      if (this->scene.trace({ orig, dir, Ray::RayType::PRIMARY }, interObjInfo))
//      {
//         //shaded point
//         arma::vec3 hitPoint = orig + dir * interObjInfo.tNear;
//
//         arma::vec3 hitNormal{ 0, 0, 0 };
//         arma::vec2 hitTextureCoordinates{ 0, 0 };
//
//         interObjInfo.hitObject->getSurfaceData(hitPoint, dir, hitNormal, hitTextureCoordinates);
//
//
//         if (true == interObjInfo.hitObject->material->isReflective() && true == interObjInfo.hitObject->material->isRefractive())
//         {
//            arma::vec3 refractionColor;
//            refractionColor.zeros();
//
//            float kr = rrr::fresnel(dir, hitNormal, interObjInfo.hitObject->material->refractive);
//            bool outside = arma::dot(dir, hitNormal) < 0;
//            arma::vec3 bias = this->settings.getBias() * hitNormal;
//
//            if (kr < 1)
//            {
//               arma::vec3 refractionDir = rrr::refract(dir, hitNormal, interObjInfo.hitObject->material->refractive);
//               refractionDir = arma::normalise(refractionDir);
//
//               arma::vec3 refractionRayOrig;
//               if (true == outside) refractionRayOrig = hitPoint - bias;
//               else refractionRayOrig = hitPoint + bias;
//
//               refractionColor = castRay(refractionRayOrig, refractionDir, objects, lights, depth + 1);
//            }
//
//            arma::vec3 reflectionDir = arma::normalise(rrr::reflect(dir, hitNormal));
//
//            arma::vec3 reflectionRayOrig;
//            if (true == outside) reflectionRayOrig = hitPoint - bias;
//            else reflectionRayOrig = hitPoint + bias;
//
//            arma::vec3 reflectionColor = castRay(reflectionRayOrig, reflectionDir, objects, lights, depth + 1);
//
//            hitColor += reflectionColor * kr + refractionColor * (1 - kr);
//         }
//         else if (true == interObjInfo.hitObject->material->isReflective())
//         {
//            arma::vec3 R = rrr::reflect(dir, hitNormal);
//            hitColor += 0.8 * castRay(hitPoint + hitNormal * this->settings.getBias(), R, objects, lights, depth + 1);
//         }
//         else
//         {
//            for (const auto& light : lights)
//            {
//               ShadingInfo shInfo = light->getLightInfo(hitPoint);
//               Intersection shadowIntersectionInfo;
//               if (false == this->scene.trace({ hitPoint + (hitNormal * this->settings.getBias()), -shInfo.lightDirection, Ray::RayType::SHADOW }, shadowIntersectionInfo))
//               {
//                  double temp = std::max(0.0, arma::dot(hitNormal, -shInfo.lightDirection));
//                  if (true == interObjInfo.hitObject->material->isReflective())
//                     hitColor += (interObjInfo.hitObject->material->diffuse % shInfo.colorIntensity) * temp;
//                  else
//                     hitColor += (interObjInfo.hitObject->getColor().toArmaVec3F() % interObjInfo.hitObject->material->diffuse % shInfo.colorIntensity) * temp;
//
//               }
//            }
//
//            //std::cout << hitColor.toArmaVec() << std::endl;
//         }
//      }
//      else
//      {
//         hitColor = this->settings.getBackgroundColor().toArmaVec3F();
//      }
//   }
//
//   return hitColor;
//}
//
//
void Renderer::prepareScene(const std::string& sceneDescription)
{
   //camera
   const std::string cameraObj = "camera";
   const std::string cameraViewDirProp = "viewDir";

   const std::string worldObj = "world";
   const std::string worldTranslateProp = "worldTranslate";
   const std::string worldPitchProp = "worldPitch";
   const std::string worldYawProp = "worldYaw";
   const std::string worldRollProp = "worldRoll";

   const std::string globalObj = "global";
   const std::string backgroundProp = "backgroundColor";
   const std::string sizeProp = "size";
   const std::string fovProp = "fov";

   std::optional<arma::vec3> camViewDirVal = std::nullopt;
   std::optional<arma::vec3> worldTransVal = std::nullopt;
   std::optional<float> worldPitchVal = std::nullopt;
   std::optional<float> worldYawVal = std::nullopt;
   std::optional<float> worldRollVal = std::nullopt;

   const std::string distantLightObj = "disLight";
   const std::string pointLightObj = "pointLight";
   const std::string intensityObj = "intensity";

   const std::string sphereObj = "sph";
   const std::string radiusObj = "radius";

   const std::string positionObj = "pos";
   const std::string directionObj = "dir";
   const std::string materialObj = "mat";
   const std::string colorObj = "color";

   auto checkValues = [](const std::vector<std::string>& tokens, size_t neededValues, const std::string& propertyName)->bool
   {
      if (tokens.size() != neededValues)
      {
         rrr::log("Invalid arguments: [" + propertyName + "] property.");
         return false;
      }
      return true;
   };

   auto parseVec3 = [&checkValues](const std::vector<std::string>& tokens, const std::string& propertyName) -> arma::vec3
   {
      arma::vec3 rV;
      if (true == checkValues(tokens, 3, propertyName))
      {
         try
         {
            rV.x() = std::stof(tokens[0]);
            rV.y() = std::stof(tokens[1]);
            rV.z() = std::stof(tokens[2]);
         }
         catch (...)
         {
            assert(false && "Cannot parse vector");
         }
      }
      return rV;
   };

   const std::string lineDelimiter = "\r\n";
   const std::string properAndArgsDelimiter = ":";
   const std::string propertiesDelimiter = ",";

   auto lines = rrr::split(sceneDescription, lineDelimiter);

   for (const auto& line : lines)
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
      //we get a single line and split into two parts: property/object and rest arguments
      auto mainTokens = rrr::split(line, properAndArgsDelimiter, false);

      if (mainTokens.size() != 2)
      {
         continue;
      }
      rrr::trim(mainTokens);

      //split rest of arguments to tokesn
      auto tokens = rrr::split(mainTokens[1], propertiesDelimiter);
      //trim tokens
      rrr::trim(tokens);

      //split the tokens to property and it values and place it in container
      std::vector<std::pair<const std::string, std::vector<std::string>>> propertiesAndValues;
      for (auto t : tokens)
      {
         auto temp = rrr::split(t);
         const std::string propName = temp[0];
         //remove property name from argument list
         temp.erase(temp.begin());
         rrr::trim(temp);
         propertiesAndValues.push_back({ propName, temp });
      }

      if (sphereObj == mainTokens[0])
      {
         std::optional<Material*> material;
         RrrColor::RGBA color = RrrColor::randomColor();
         arma::vec3 coords;
         coords.zeros();
         float radius = 1;
         for (const auto& [propName, args] : propertiesAndValues)
         {
            if (positionObj == propName)
            {
               coords = parseVec3(args, positionObj);
            }
            else if (materialObj == propName)
            {
               material = MaterialSimpleFactory::parseStringToMaterial(args);
               if (material == std::nullopt)
               {
                  assert(false && "Cannot parse material");
               }
            }
            else if (colorObj == propName)
            {
               if (true == checkValues(args, 3, colorObj))
               {
                  color = rrr::parseColorFromStr(args);
               }
            }
            else if (radiusObj == propName)
            {
               if (true == checkValues(args, 1, radiusObj))
               {
                  radius = std::stof(args[0]);
               }
            }

         }
         //create sphere
         this->scene.createSphere(coords, radius, *material, color);
      }
      else if (distantLightObj == mainTokens[0])
      {
         RrrColor::RGBA color = RrrColor::White;
         arma::vec3 dir;
         dir.zeros();

         //todo change it to vec, now is float
         //arma::vec3 intensity;
         float intensity = 1;

         for (const auto& [propName, args] : propertiesAndValues)
         {
            if (directionObj == propName)
            {
               dir = parseVec3(args, directionObj);
            }
            else if (colorObj == propName)
            {
               if (true == checkValues(args, 3, colorObj))
               {
                  color = rrr::parseColorFromStr(args);
               }
            }
            else if (intensityObj == propName)
            {
               if (true == checkValues(args, 1, intensityObj))
               {
                  intensity = std::stof(args[0]);
               }
            }
         }

         this->scene.createDirectionalLight(dir, intensity, color);
      }
      else if (pointLightObj == mainTokens[0])
      {
         RrrColor::RGBA color = RrrColor::White;
         arma::vec3 pos;
         pos.zeros();

         float intensity = 1;

         for (const auto& [propName, args] : propertiesAndValues)
         {
            if (positionObj == propName)
            {
               pos = parseVec3(args, positionObj);
            }
            else if (colorObj == propName)
            {
               if (true == checkValues(args, 3, colorObj))
               {
                  color = rrr::parseColorFromStr(args);
               }
            }
            else if (intensityObj == propName)
            {
               if (true == checkValues(args, 1, intensityObj))
               {
                  intensity = std::stof(args[0]);
               }
            }
         }

         this->scene.createPointLight(pos, intensity, color);
      }
      else if (globalObj == mainTokens[0])
      {
         for (const auto& [propName, args] : propertiesAndValues)
         {
            if (backgroundProp == propName)
            {
               if (true == checkValues(args, 3, colorObj))
               {
                  RrrColor::RGBA bgColor = rrr::parseColorFromStr(args);

                  this->settings.setBackgroundColor(bgColor);
               }
            }
            else if (sizeProp == propName)
            {
               if (true == checkValues(args, 2, sizeProp))
               {
                  int width = std::stoi(args[0]);
                  int height = std::stoi(args[1]);

                  this->settings.setWidth(width);
                  this->settings.setHeight(height);
               }
            }
         }
      }
      else if (cameraObj == mainTokens[0])
      {
         for (const auto& [propName, args] : propertiesAndValues)
         {
            if (cameraViewDirProp == propName)
            {
               camViewDirVal.emplace(arma::vec3{ parseVec3(args, cameraViewDirProp) });
            }
            else if (fovProp == propName)
            {
               if (true == checkValues(args, 1, fovProp))
               {
                  float fov = std::stof(args[0]);

                  this->settings.setFOV(fov);
               }
            }
         }
      }
      else if (worldObj == mainTokens[0])
      {
         for (const auto& [propName, args] : propertiesAndValues)
         {
            if (worldTranslateProp == propName)
            {
               worldTransVal.emplace(arma::vec3{ parseVec3(args, worldTranslateProp) });
            }
            else if (worldPitchProp == propName)
            {
               if (true == checkValues(args, 1, worldPitchProp))
               {
                  worldPitchVal.emplace(std::stof(args[0]));
               }
            }
            else if (worldYawProp == propName)
            {
               if (true == checkValues(args, 1, worldYawProp))
               {
                  worldYawVal.emplace(std::stof(args[0]));
               }
            }
            else if (worldRollProp == propName)
            {
               if (true == checkValues(args, 1, worldRollProp))
               {
                  worldRollVal.emplace(std::stof(args[0]));
               }
            }
         }
      }
   }

   //its moved further, after parsing rest of file, because it should be called in proper way
   if (camViewDirVal)
   {
      this->camera.lookAt(*camViewDirVal);
   }
   if (worldTransVal)
   {
      this->scene.translate(*worldTransVal);
   }
   if (worldPitchVal)
   {
      this->scene.pitch(*worldPitchVal);
   }
   if (worldYawVal)
   {
      this->scene.yaw(*worldYawVal);
   }
   if (worldRollVal)
   {
      this->scene.roll(*worldRollVal);
   }

}
