#pragma once
#include "Object_A.h"

class Scene
{
public:
   //void runRenderingScene();

  // void addObjectsToScene(const std::vector<ObjectUptr>& objects);
   void addObjectToScene(ObjectUptr object);

   std::vector<ObjectUptr>& getObjects();
   void createSphere(const arma::vec3& _position, float _radius, RrrColor::RGBA _color = RrrColor::randomColor());

   void transformWorld(const arma::dmat44& transformMatrix);

private:
   arma::mat allObjectsPositionMatrix;
   std::vector<ObjectUptr> objects;
};

