#pragma once
#include <armadillo>
#define PI 3.14159265359

namespace RrrColor
{
   struct RGBA
   {
      uint8_t blue;
      uint8_t green;
      uint8_t red;
      uint8_t alpha;
      RGBA(uint8_t _red = 0, uint8_t _green = 0, uint8_t _blue = 0, uint8_t _alpha = 255)
         : red(_red), green(_green), blue(_blue), alpha(_alpha) {}

      arma::vec3 toArmaVec() const
      {
         return arma::vec3{ 
            static_cast<double>(this->red),
            static_cast<double>(this->green),
            static_cast<double>(this->blue) 
         };
      }
   };

   //struct HSV
   //{
   //   unsigned char hue;
   //   unsigned char sat;
   //   unsigned char val;
   //};

   inline RGBA randomColor()
   {
      return RGBA(rand() % ((255 + 1)), rand() % ((255 + 1)), rand() % ((255 + 1)));
   }
   const static RGBA Transparent = RrrColor::RGBA(255, 255, 255, 0);
   const static RGBA Black = RrrColor::RGBA(0, 0, 0);
   const static RGBA White = RrrColor::RGBA(255, 255, 255);
   const static RGBA Red = RrrColor::RGBA(255, 0, 0);
   const static RGBA Green = RrrColor::RGBA(0, 255, 0);
   const static RGBA Blue = RrrColor::RGBA(0, 0, 255);
}
