#pragma once
#include <string>
#include <armadillo>
#include "Camera.h"

class Settings
{
public:
   Settings(uint32_t _width, uint32_t _height, float _fov) : width(_width), height(_height), fov(_fov) {};
   ~Settings() = default;

   void setWidth(uint32_t width) noexcept
   {
      this->width = width;
   };

   uint32_t getWidth() const noexcept
   {
      return this->width;
   };

   void setHeight(uint32_t height) noexcept
   {
      this->height = height;
   };

   uint32_t getHeight() const noexcept
   {
      return this->height;
   };

   void setFOV(float fov) noexcept
   {
      this->fov = fov;
   };

   float getFOV() const noexcept
   {
      return this->fov;
   };

   float getRatio() const noexcept
   {
      return this->width / (float)this->height;
   }


private:
   uint32_t width;
   uint32_t height;
   float fov;

};

