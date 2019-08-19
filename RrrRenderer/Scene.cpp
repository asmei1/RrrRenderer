#include "Scene.h"
#include "Sphere.h"

#include <random>

//void Scene::runRenderingScene()
//{
//   uint32_t numSpheres = 32;
//   /*gen.seed(0);
//   for (uint32_t i = 0; i < numSpheres; ++i) 
//   {
//      float a = (0.5 - dis(gen)) * 10;
//      float b = (0.5 - dis(gen)) * 10;
//      float c = (0.5 + dis(gen) * 10);
//      
//      //arma::vec3 pos{ (0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10) };
//      arma::vec3 pos{ a, b, c };
//      float randRadius = (0.5 + dis(gen) * 0.5);
//      objects.push_back(ObjectUptr(new Sphere(pos, randRadius)));
//   }*/
//
//   objects.push_back(ObjectUptr(new Sphere(arma::vec3{0, 0, 0}, 0.7)));
//   objects.push_back(ObjectUptr(new Sphere(arma::vec3{0.3, 0.1, 0}, 0.8)));
//   //objects.push_back(ObjectUptr(new Sphere(arma::vec3{1, 1, -2}, 1)));
//   //objects.push_back(ObjectUptr(new Sphere(arma::vec3{1, 0, -3}, 0.3)));
//   this->renderer.render(this->settings, objects);
//}

//void Scene::addObjectsToScene(const std::vector<ObjectUptr>& objects)
//{
//   this->objects.insert(this->objects.end(), objects.begin(), objects.end());
//}
//
void Scene::addObjectToScene(ObjectUptr object)
{
   this->objects.push_back(std::move(object));
}

std::vector<ObjectUptr>& Scene::getObjects()
{
   return this->objects;
}

void Scene::createSphere(const arma::vec3& _position, float _radius, RrrColor::RGBA _color)
{
   int positionIndex = this->allObjectsPositionMatrix.n_cols;
   this->allObjectsPositionMatrix.insert_cols(positionIndex, arma::dvec4{ _position.x(), _position.y(), _position.z(), 1 });

   ObjectUptr sphere(new Sphere(this->allObjectsPositionMatrix, positionIndex, _radius, _color));
   this->objects.push_back(std::move(sphere));
}

void Scene::transformWorld(const arma::dvec4& transformMatrix)
{
   this->allObjectsPositionMatrix = transformMatrix * this->allObjectsPositionMatrix;
}
