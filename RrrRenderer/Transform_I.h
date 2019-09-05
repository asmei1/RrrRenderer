#pragma once
#include <armadillo>
#include <cassert>

class Transform_I
{
public:
   Transform_I() {}
   virtual ~Transform_I() {}

   
   virtual void transform(const arma::mat44& matrix) = 0;
   virtual void move(const arma::vec3& move) = 0;
   virtual void scale(const arma::vec3& scale) = 0;
   virtual void rotate(const arma::vec3& rotate) = 0;

};
