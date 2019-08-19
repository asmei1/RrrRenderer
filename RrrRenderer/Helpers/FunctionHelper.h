#pragma once
#include "BMPImg.h"
//
//RrrColor::BGRA HSVtoRGB(RrrColor::HSV);
//RrrColor::HSV RGBtoHSV(RrrColor::BGRA);
namespace rrr
{
   uint8_t truncate(int val);
   int roundUp(int numToRound, int multiple);
   std::vector<std::string> split(const std::string& s, char delimiter);
}