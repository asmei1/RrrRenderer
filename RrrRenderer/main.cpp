//Realistical render project maked on IPS 
#include <iostream>
#include "Renderer.h"

int main(int argc, char* argv[])
{
   Renderer renderer;
   std::vector<std::string> params;
   for (int i = 0; i < argc; ++i)
   {
      params.push_back(argv[i]);
   }

   if (params.size() > 2)
   {
      if ((params[1] == "--file") || (params[1] == "-f"))
      {
         renderer.loadSceneFromFile(std::filesystem::path{ params[2] });
      }
   }
   else
   {
      renderer.prepareScene();
   }

   renderer.render();
}



