#include "Renderer.h"
#include "Sphere.h"
#include "Helpers/FunctionHelper.h"

void Renderer::prepareScene()
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1);


   this->scene.createSphere(arma::vec3{ 0, 0, -6 }, 0.7f);
   this->scene.createSphere(arma::vec3{ -0.8, 0, -5 }, 0.7f);

}
 
void Renderer::render()
{
   int counter = 0;
   BMPImg img{ this->settings.getWidth(), this->settings.getHeight(), RrrColor::White, true };

   float scale = tan(rrr::deg2rad(this->settings.getFOV() * 0.5f));
   float imageRatio = this->settings.getRatio();
   
   //arma::vec3 orig;
   arma::dmat44 viewMatrix = camera.lookAt({ 0, 1, -10 }); 
   std::cout << viewMatrix << std::endl;

   this->scene.transformWorld(viewMatrix);
   
   RrrColor::RGBA color;
   for(uint32_t j = 0; j < this->settings.getHeight(); ++j)
   {
      for (uint32_t i = 0; i < this->settings.getWidth(); ++i)
      {
         float x = (2 * (i + 0.5f) / static_cast<float>(this->settings.getWidth()) - 1) * scale * imageRatio;
         float y = (1 - 2 * (j + 0.5f) / static_cast<float>(this->settings.getHeight())) * scale;
         arma::vec3 dir;

         rrr::multDirMatrixCM(viewMatrix, arma::vec3{ x, y, -1.f }, dir); //-1 is from picture plane distance
         
         dir = arma::normalise(dir);
         color = (castRay(Ray{ this->camera.getEyePosition(), dir }, this->scene.getObjects()));

         img.set(i, j, color);
      }
   }
   img.flipVertical();
   img.save(std::string("./test/renderTriangle") + /*std::to_string(counter++) +*/ ".bmp");


   std::cout << "Number of rays: " << Ray::counter << std::endl;
}

inline
arma::vec3 mix(const RrrColor::RGBA& a, const float& mixValue)
{
   arma::vec3 r;
   r.x() = a.red   * (1 - mixValue) + 0.8 * a.red * mixValue;
   r.y() = a.green * (1 - mixValue) + 0.8 * a.green * mixValue;
   r.z() = a.blue  * (1 - mixValue) + 0.8 * a.blue * mixValue;
   return r;
}

RrrColor::RGBA Renderer::castRay(const Ray& ray, const std::vector<ObjectUptr>& objects)
{
   RrrColor::RGBA hitColor = this->settings.getBackgroundColor();
   const Object_A* hitObject = nullptr;
   arma::vec2 uv;
   float t; //// this is the intersection distance from the ray origin to the hit point 

   if (trace(ray, objects, t, hitObject))
   {
      //shaded point
      arma::vec3 hitPoint = ray.orig + ray.dir * t;

      arma::vec3 hitNormal{ 0, 0, 0 };
      arma::vec3 viewingDirection{ 0, 0, 0 };
      arma::vec2 hitTextureCoordinates{ 0, 0 };

      hitObject->getSurfaceData(hitPoint, viewingDirection, uv, hitNormal, hitTextureCoordinates);
      //// Use the normal and texture coordinates to shade the hit point.
      //// The normal is used to compute a simple facing ratio and the texture coordinate
      //// to compute a basic checker board pattern
      ////float scale = 4;
      ////float pattern = (fmodf(hitTextureCoordinates.x() * scale, 1) > 0.5) ^ (fmodf(hitTextureCoordinates.y() * scale, 1) > 0.5);
      ////arma::vec3 temp = arma::dot(viewingDirection, -ray.dir) * mix(hitObject->getColor(), pattern);
      ////

      ////hitColor.red = temp.x();
      ////hitColor.green = temp.y();
      ////hitColor.blue = temp.z();


      //Now, we check, if dot product is < 0 - if yes, clamp it to 0, because direction of viewingDir and ray dir is opposite - 
      //this point does not illuminate the light
      double temp = std::max(0.0, arma::dot(viewingDirection, -ray.dir));

      hitColor.red   = static_cast<uint8_t>(temp * hitObject->getColor().red);
      hitColor.green = static_cast<uint8_t>(temp * hitObject->getColor().green);
      hitColor.blue  = static_cast<uint8_t>(temp * hitObject->getColor().blue);
      
   }

   return hitColor;
}

bool Renderer::trace(const Ray& ray, const std::vector<ObjectUptr>& objects, float& tNear, const Object_A *& hitObject)
{
   //todo export this
   tNear = std::numeric_limits<float>::max();
   std::vector<std::unique_ptr<Object_A>>::const_iterator iter = objects.begin();
   for (; objects.cend() != iter; ++iter)
   {
      float t = std::numeric_limits<float>::max();
      if ((*iter)->intersect(ray, t) && t < tNear) {
         hitObject = iter->get();
         tNear = t;
      }
   }

   return hitObject != nullptr;
}
