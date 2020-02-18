#pragma once
#include "geombase.h"
#include "render.h"


class Geom : public GeomBase {
public:
   int read(const char *filename);
   int render(Renderer *renderer, glm::mat4 rendermat,glm::mat4 viewrendermat,bool selectionMode) const;
   
   Geom(int *idptr, const char *filename=NULL,bool sphere=true,float diff=1,float specularCoeff=0) 
   {
      id = *idptr; 
      *idptr = *idptr + 1;
      read(filename);
      isSphere = sphere;
      diffuseness = diff;
      shininess = specularCoeff;
      
   }
   
   
   float getIntersectionTValue(glm::vec3 rayOrigin, glm::vec3 rayDir);
   bool isSphere=true;

   float featureValue;//serves as radius for sphere and dVal for plane
   glm::vec3 featureVec;//serves as centre for sphere and normal for plane

   glm::vec3 minBounds;//useful in case of intersection with plane
   glm::vec3 maxBounds;//useful in case of intersection with plane

private:
   bool useDrawElements;
   int numIndices=-1;
   float delta = 0.0001;
   float shininess;
   float diffuseness;
};

