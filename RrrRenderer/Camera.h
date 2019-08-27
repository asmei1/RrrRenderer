#pragma once
#include <Armadillo>
#include "Colors.h"

class Camera
{
public:
   Camera()
   {
      this->viewMatrix.zeros();
      this->eye.zeros();
      this->up.zeros();
      this->viewDirection.zeros();
   };

   ~Camera() = default;

   arma::dmat44 getViewMatrix() const
   {
      return this->viewMatrix;
   }

   arma::dmat44 lookAt(const arma::dvec3& eye, const arma::dvec3& viewDirection, const arma::dvec3& up = arma::dvec3{ 0, 1, 0 })
   {
      this->eye = eye;
      this->viewDirection = viewDirection;
      this->up = up;

      arma::dvec3 forward = arma::normalise(this->eye - this->viewDirection);   //z
      arma::dvec3 right = arma::normalise(arma::cross(this->up, forward));  //x
      arma::dvec3 upTemp = arma::cross(forward, right);                           //y

      this->viewMatrix = arma::dmat44{ {right.x(), upTemp.x(), forward.x(), 0},
                                       {right.y(), upTemp.y(), forward.y(), 0},
                                       {right.z(), upTemp.z(), forward.z(), 0},
                                       {-arma::dot(right, this->eye), -arma::dot(upTemp, this->eye), -arma::dot(forward, this->eye), 1} };
   
      return this->viewMatrix;
   }

   arma::dmat44 lookAt(const arma::dvec3& viewDirection)
   {
      return lookAt(arma::dvec3{0,0,0}, viewDirection);
   }

   arma::dvec3 getEyePosition() const
   {
      return this->eye;
   }

private:
   arma::dvec3 eye;
   arma::dvec3 viewDirection;
   arma::dvec3 up;

   //Matrix used for transform world to camera view
   arma::dmat44 viewMatrix;
};
