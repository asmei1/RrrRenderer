#pragma once
#include "Objects/Object_A.h"
#include "Lights/Light_A.h"

struct Intersection;

class Scene
{
   struct ObjectsCounter
   {
      uint16_t spheres = 0;
      uint16_t distantLights = 0;
      uint16_t pointLights = 0;

   };

public:
   Scene();

   void addObjectToScene(ObjectUptr object);

   const std::vector<ObjectUptr>& getObjects() const;
   const std::vector<LightUptr>& getLights() const;
   void createSphere(const arma::vec3& position, float radius, Material* _material, RrrColor::RGBA color = RrrColor::randomColor());

   void createDirectionalLight(const arma::vec3& direction, float intensity, const RrrColor::RGBA& color);
   void createPointLight(const arma::vec3& position, float intensity, const RrrColor::RGBA& color);

   void transformWorld(const arma::dmat44& transformMatrix);

   bool trace(const Ray& ray, Intersection& interObjInfo, std::vector<const Object_A*> ignore = {}) const;

   friend std::ostream& operator<<(std::ostream& os, Scene& scene);

   void pitch(float angle);
   void yaw(float angle);
   void roll(float angle);
   void translate(const arma::vec3& transformVec);

private:
   arma::mat allObjectsPositionMatrix;
   std::vector<ObjectUptr> objects;
   std::vector<LightUptr> lights;

   ObjectsCounter objsCounter;
};

