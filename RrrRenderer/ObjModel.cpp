#include "ObjModel.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "Helpers/FunctionHelper.h"

ObjModel::ObjModel()
{
}


ObjModel::~ObjModel()
{
}

bool ObjModel::parse(const std::string & filePath)
{
   std::ifstream in;
   in.open(filePath, std::ifstream::in);

   if (in.fail())
   {
      return false;
   }

   std::string line;

   while (!in.eof())
   {
      std::getline(in, line);
      std::istringstream iss(line);
      iss.ignore(2);
      if (line.compare(0, 2, "v ") == 0)
      {
         arma::vec3 vec;
         iss >> vec[0]; //x
         iss >> vec[1]; //y
         iss >> vec[2]; //z
         this->vertices.push_back(vec);
      }
      else if (line.compare(0, 2, "f ") == 0)
      {
         //pass line without "f "
         parseFace(line.erase(0, 2));
      }
      else if (line[0] == '#')//comment
      {
         std::cerr << line.erase(0, 1) << std::endl;
      }

   }

   return true;
}

size_t ObjModel::facesCount()
{
   return this->faces.size();
}

ObjModel::Face ObjModel::getFace(size_t index)
{
   return this->faces[index];
}

arma::vec3 ObjModel::getVert(size_t index)
{
   //todo check index properly
  // if (index > this->vertices.size()) return this->vertices[0];
   return this->vertices[index];
}

void ObjModel::parseFace(const std::string & line)
{
   Face f;
   std::vector<std::string> tokens = rrr::split(line, ' ');
   for (size_t i = 0; i < tokens.size(); ++i)
   {
      std::vector<std::string> strFace = rrr::split(tokens[i], '/');

      f.idxGroups[i].idxPos = atoi(strFace[0].c_str()) - 1;
      if (strFace.size() > 1)
      {
         f.idxGroups[i].idxTextCoord = atoi(strFace[1].c_str());
         if (strFace.size() > 2)
         {
            f.idxGroups[i].idxVecNormal = atoi(strFace[2].c_str());
            if (strFace[1] == "")
            {
               f.idxGroups[i].idxTextCoord = -1;
            }
         }
      }

   }
      this->faces.push_back(f);
}
