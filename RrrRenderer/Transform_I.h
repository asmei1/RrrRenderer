#pragma once
#include <armadillo>
#include <cassert>

class Transform_I
{
public:
   Transform_I(const arma::mat& _allObjectsPositionMatrix)
      : allObjectsPositionMatrix(_allObjectsPositionMatrix)
   {}

   virtual void move(const arma::vec3& move) = 0;
   //virtual void scale(const arma::vec3& scale);
   //virtual void rotate(const arma::vec3& rotate);


protected:
   const arma::mat& allObjectsPositionMatrix;
};
