#pragma once
#include "Objects/Object_A.h"

struct Intersection
{
   Object_A* hitObject = nullptr;
   float tNear = std::numeric_limits<float>::max();
};
