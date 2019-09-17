//Realistical render project maked on IPS 
#include <iostream>
#include "Renderer.h"

int main(int argc, char* argv[])
{
   std::string rVFileName = "res.bmp";
   bool debugInfo = false;

   Renderer renderer;
   std::vector<std::string> params;
   for (int i = 0; i < argc; ++i)
   {
      params.push_back(argv[i]);
   }

   if (params.size() > 2)
   {
      for(size_t i = 0; i < params.size(); ++i)
      {
         if ((params[i] == "--scene") || (params[i] == "-s"))
         {
            renderer.loadSceneFromFile(std::filesystem::path{ params[i + 1] });

            i += 1;
         }
         else if ((params[i] == "--file") || (params[i] == "-f"))
         {
            rVFileName = params[i + 1];
            i += 1;
         }
         else if ((params[i] == "--debug") || (params[i] == "-d"))
         {
            debugInfo = true;
         }
      }
   }
   else
   {
      //testing only
      renderer.loadSceneFromFile("x64\\Release\\simple.sce");
   }

   renderer.render(rVFileName, debugInfo);
}



