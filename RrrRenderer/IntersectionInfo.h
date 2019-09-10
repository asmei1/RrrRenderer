#pragma once
#include <Object_A.h>

struct IntersectionInfo
{
   Object_A* hitObject = nullptr;
   float tNear = std::numeric_limits<float>::max();
};