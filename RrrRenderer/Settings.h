#pragma once
#include <string>
#include <armadillo>
#include "Camera.h"

class Settings
{
public:
   Settings() 
   {}

   Settings(uint32_t _width, uint32_t _height, float _fov, const RrrColor::RGBA& _backgroundColor, int _maxDepth) 
   : width(_width), height(_height), fov(_fov), backgroundColor(_backgroundColor), maxDepth(_maxDepth)
   {};
   ~Settings() = default;

   void setWidth(uint32_t width);
   void setHeight(uint32_t height);
   void setFOV(float fov);
   void setBias(float bias);
   void setMaxDepth(int maxDepth);
   void setBackgroundColor(const RrrColor::RGBA& color);

   uint32_t getWidth() const;
   uint32_t getHeight() const;
   float getFOV() const;
   float getRatio() const;
   RrrColor::RGBA getBackgroundColor() const;
   float getBias() const;
   int getMaxDepth() const;

private:
   uint32_t width;
   uint32_t height;
   int maxDepth;
   float fov;
   float bias = 1e-4;
   RrrColor::RGBA backgroundColor; 

};

