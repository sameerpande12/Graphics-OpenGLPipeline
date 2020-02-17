#pragma once
#include "geombase.h"

class Renderer;

class Geom : public GeomBase {
public:
   int read(const char *filename);
   int render(Renderer *renderer, glm::mat4 rendermat,glm::mat4 viewrendermat,bool selectionMode) const;
   
   Geom(int *idptr, const char *filename=NULL,bool sphere=true) {id = *idptr; *idptr = *idptr + 1;read(filename);isSphere = sphere;}
   glm::mat4 getModelMatrix(){return modelMatrix;}
   
   void setModelMatrix(glm::mat4 model){modelMatrix = model;}
   
   
   float getIntersectionTValue(glm::vec3 rayOrigin, glm::vec3 rayDir);
   bool isSphere=true;

   float featureValue;//serves as radius for sphere and dVal for plane
   glm::vec3 featureVec;//serves as centre for sphere and normal for plane

private:
   bool useDrawElements;
   int numIndices=-1;
   glm::mat4 modelMatrix;
};

