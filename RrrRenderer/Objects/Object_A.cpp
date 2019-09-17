#include "Object_A.h"

Object_A::~Object_A()
{
   if(nullptr != material)
   {
      delete material;
   }
}

