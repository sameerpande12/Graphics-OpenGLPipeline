#pragma once
#include "geombase.h"
#include "render.h"


class Geom : public GeomBase {
public:
   int read(const char *filename);
   int render(Renderer *renderer, glm::mat4 rendermat,glm::mat4 viewrendermat,bool reflectMirror,bool reflectScene) const;
   
   Geom(int *idptr, const char *filename=NULL,bool sphere=true,glm::vec3 tlight = glm::vec3(0,0,3),float diff=1,float specularCoeff=0,float shine = 0,bool useTex = true,glm::vec4 col=glm::vec4(1,1,1,1),bool useCol = false) 
   {
      id = *idptr; 
      *idptr = *idptr + 1;
      isSphere = sphere;
      diffuseness = diff;
      shininess = shine;
      specularCoefficient = specularCoeff;
      topLight = tlight;
      useTexture = useTex;
      useDefaultColour = useCol;
      color = col;
      read(filename);
      
   }
   
   
   float getIntersectionTValue(glm::vec3 rayOrigin, glm::vec3 rayDir);
   bool isSphere=true;

   float featureValue;//serves as radius for sphere and dVal for plane
   glm::vec3 featureVec;//serves as centre for sphere and normal for plane

   glm::vec3 minBounds;//useful in case of intersection with plane
   glm::vec3 maxBounds;//useful in case of intersection with plane

   void setLightIntensity(int lightNum,glm::vec3 light){
      if(lightNum%2==0)
         lightIntensity2 = light;
      
      else
         lightIntensity1 = light;
   }


   glm::vec3 getLightIntensity(int lightNum){
      if(lightNum%2==0)
         return lightIntensity2;
      else
         return lightIntensity1; 
   }

private:
   bool useDrawElements;
   int numIndices=-1;
   float delta = 0.0001;
   float shininess;
   float diffuseness;
   float specularCoefficient;
   glm::vec3 topLight;
   bool useTexture;
   glm::vec4 color;
   bool useDefaultColour;
   glm::vec3 lightIntensity1 = glm::vec3(1,1,1);
   glm::vec3 lightIntensity2 = glm::vec3(1,1,1);
};

