#pragma once
#include <armadillo>
#define PI 3.14159265359

namespace RrrColor
{
   struct RGBA
   {
      uint8_t b;
      uint8_t g;
      uint8_t r;
      uint8_t a;
      RGBA(uint8_t _red = 0, uint8_t _green = 0, uint8_t _blue = 0, uint8_t _alpha = 255)
         : r(_red), g(_green), b(_blue), a(_alpha) {}

      static RGBA fromArmaVec3F(const arma::vec3& color)
      {
         return RGBA{ 
            static_cast<uint8_t>(std::clamp(color.x(), 0., 1.) * 255),
            static_cast<uint8_t>(std::clamp(color.y(), 0., 1.) * 255),
            static_cast<uint8_t>(std::clamp(color.z(), 0., 1.) * 255),
         };
      }
      static RGBA fromArmaVec4F(const arma::vec4& color)
      {
         return RGBA{ 
            static_cast<uint8_t>(std::clamp(color.x(), 0., 1.) * 255),
            static_cast<uint8_t>(std::clamp(color.y(), 0., 1.) * 255),
            static_cast<uint8_t>(std::clamp(color.z(), 0., 1.) * 255),
            static_cast<uint8_t>(std::clamp(color.w(), 0., 1.) * 255),
         };
      }

      arma::vec3 toArmaVec3F() const
      {
         return { this->r / 255., this->g / 255., this->b / 255. };
      }

      arma::vec4 toArmaVec4F() const
      {
         return { this->r / 255., this->g / 255., this->b / 255., this->a / 255. };
      }

      std::string getColorAsStr() const
      {
         return (std::string("R: ") + std::to_string(this->r) + std::string(" G: ") + std::to_string(this->g) + std::string(" B: ") + std::to_string(this->b) + std::string(" A: ") + std::to_string(this->a));
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
