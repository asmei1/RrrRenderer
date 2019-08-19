#pragma once
#include <vector>
#include <string>
#include <armadillo>

class ObjModel
{
public:
   struct Face{
      struct IdxGroup
      {
         int idxPos{ -1 };
         int idxTextCoord{ -1 };
         int idxVecNormal{ -1 };
      };
      std::vector<IdxGroup> idxGroups{3};
   };

public:
   ObjModel();
   ~ObjModel();

   bool parse(const std::string &filePath);

   size_t facesCount();
   Face getFace(size_t index);
   arma::vec3 getVert(size_t index);

private:
   void parseFace(const std::string & line);


   
   std::vector<Face> faces;
   std::vector<arma::vec3> vertices;
   std::vector<arma::vec3> normals;
   std::vector<arma::fvec2> textures;
};

