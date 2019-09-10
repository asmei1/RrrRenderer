#pragma once
#include "Object_A.h"
#include "Light_A.h"



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

   std::vector<ObjectUptr>& getObjects();
   std::vector<LightUptr>& getLights();
   void createSphere(const arma::vec3& position, float radius, const Material* _material, RrrColor::RGBA color = RrrColor::randomColor());

   void createDirectionalLight(const arma::vec3& direction, float intensity, const RrrColor::RGBA& color);
   void createPointLight(const arma::vec3& position, float intensity, const RrrColor::RGBA& color);

   void transformWorld(const arma::dmat44& transformMatrix);


   friend std::ostream& operator<<(std::ostream& os, Scene& scene);

   void pitch(float angle);
   void yaw(float angle);
   void roll(float angle);
   void translate(const arma::vec3 transformVec);

private:
   arma::mat allObjectsPositionMatrix;
   std::vector<ObjectUptr> objects;
   std::vector<LightUptr> lights;

   ObjectsCounter objsCounter;
};

