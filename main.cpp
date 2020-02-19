#include <stdio.h>
#include "GL/glew.h"

#include "uiGLFW.h"
#include "gwindowGLFW.h"
#include "render.h"
#include "scene.h"
#include <glm/ext.hpp>
#include <iostream>
#include "unordered_map"
#include "unordered_set"
#define cout std::cout
#define STARTID 1
int main( int argc, char* args[] )
{
   gWindow_GLFW window("Test"); // Create a window. Use default OpenGL settings.
   glm::vec3 topLight = glm::vec3(0,0,3.1);
   std::unordered_map<int,Geom*> objects;
   int M, m;
   glGetIntegerv(GL_MAJOR_VERSION, &M);
   glGetIntegerv(GL_MINOR_VERSION, &m);
   printf("OpenGL version: %d.%d\n", M, m);

   int id = STARTID;
   Scene* primaryScene = new Scene(&id);                 // Should come from a file. Temporary scene, with default shader
   glm::vec3 baseCentre = glm::vec3(0,0,1);

   Geom * floor = new Geom(&id,"xyPlaneVertices.csv",false/*,id++*/);
   glm::mat4 floorTransform = glm::mat4(1.0f);
   float floorXScale = 30;
   float floorYScale = 30;
   float floorHeight = -1;
   floorTransform = glm::translate(floorTransform,baseCentre+ glm::vec3(0,0,floorHeight));
   
   
   floorTransform = glm::scale(floorTransform,glm::vec3(floorXScale,floorYScale,floorXScale));
   floor->setModelMatrix(floorTransform);

   floor->featureValue = -1;
   floor->featureVec = glm::vec3(0,0,1);
   floor->minBounds = glm::vec3(-.5 * floorXScale,-.5 * floorYScale,floorHeight);
   floor->maxBounds = glm::vec3(0.5 * floorYScale, 0.5 * floorYScale,floorHeight);


   objects[floor->id]=floor;
   primaryScene->addchild(floor,floor->id,floor->getModelMatrix());
   cout<<"floor->id "<<floor->id<<"\n";


      
   
   Geom* base = new Geom(&id,"sphereVertices.csv",true,topLight,1,0,0,true);
   glm::mat4 basetransform = glm::mat4(1.f);
   basetransform = glm::scale(basetransform,glm::vec3(1,1,1));
   basetransform = glm::translate(basetransform,baseCentre);

   base->featureValue = 1;
   base->featureVec = baseCentre;
   base->setModelMatrix(basetransform);
   objects[base->id]=base;
   primaryScene->addchild(base,base->id,base->getModelMatrix());
   cout<<baseCentre[0]<<" "<<baseCentre[1]<<" "<<baseCentre[2]<<'\n';

   Geom* torso = new Geom(&id,"sphereVertices.csv",true,topLight,1,0,0,true);
   glm::mat4 torsotransform = glm::mat4(1.f);
   glm::vec3 torsoCentre = baseCentre+ glm::vec3(0,0,1.15);
   torsotransform = glm::translate(torsotransform,torsoCentre);
   torsotransform = glm::scale(torsotransform,glm::vec3(0.5,0.5,0.5));

   torso->featureValue = 0.5;
   torso->featureVec = torsoCentre;
   torso->setModelMatrix(torsotransform);
   objects[torso->id]=torso;
   primaryScene->addchild(torso,torso->id,torso->getModelMatrix());
   // cout<<"torso "<<torso->id<<"\n";
   cout<<torsoCentre[0]<<" "<<torsoCentre[1]<<" "<<torsoCentre[2]<<'\n';


   Geom* head = new Geom(&id,"sphereVertices.csv",true,topLight,1,0,0,true);
   glm::mat4 headtransform = glm::mat4(1.f);
   glm::vec3 headCentre = baseCentre + glm::vec3(0,0,1.75);
   headtransform = glm::translate(headtransform,headCentre);
   headtransform = glm::scale(headtransform,glm::vec3(0.33,0.33,0.33));
   // cout<<"headTop "<<headCentre[2] + 0.33<<"\n";

   head->featureValue = 0.33;
   head->featureVec = headCentre;
   head->setModelMatrix(headtransform);
   objects[head->id]=head;
   primaryScene->addchild(head,head->id,head->getModelMatrix());
   // cout<<"head "<<head->id<<"\n";
   
   Geom** spheres = new Geom*[12];
   std::unordered_set<int> sphereIdSet;
   
   glm::vec4 orange = glm::vec4(255.0/255.0,165/255.0,0,1);
   glm::vec4 magenta = glm::vec4(1,0.712,0.756,1);
   glm::vec4 cyan = glm::vec4(0,1,1,1);
   for(int i =0 ;i<12;i++){
      float shine = 12;
      float diffCoeff = 0;
      float specCoeff = 1;
      bool useTexture = true;
      bool useColor = true;
      if(i%2==1)shine = 4;

      glm::vec4 color;
      if(i%3==0)color = magenta;
      else if(i%3==1)color = orange;
      else color = cyan;

      Geom* sphere = new Geom(&id,"sphereVertices.csv",true,topLight,diffCoeff,specCoeff,shine,useTexture,color,useColor);
      glm::mat4 sphereTransform = glm::mat4(1.f);
      
      float radius = 0.25;
      float largeRadius = 2;
      float angle = M_PI/6 * i;

      glm::vec3 newCentre = baseCentre +  glm::vec3(0,0,-1)+ glm::vec3(0,0,radius);
      newCentre = newCentre + glm::vec3(largeRadius*cos(angle),largeRadius*sin(angle),0);
      sphereTransform = glm::translate(sphereTransform,newCentre);
      sphereTransform = glm::scale(sphereTransform,glm::vec3(radius,radius,radius));

      sphere->featureValue = radius;
      sphere->featureVec = newCentre;
      objects[sphere->id] = sphere;
      sphere->setModelMatrix(sphereTransform);
      primaryScene->addchild(sphere,sphere->id,sphere->getModelMatrix());
      sphereIdSet.insert(sphere->id);

      // cout<<"sphere("<<i<<") "<<sphere->id<<"\n";
   }


   Renderer renderer(window.Width(), window.Height(), primaryScene); // Renderer renders scene from its camera
   renderer.objectMap = objects;
   renderer.setFloorId(floor->id);

   UI_GLFW ui(&renderer, &window);	// User interface: intermediary between a renderer and a window
   ui.setBaseId(base->id);
   ui.setTorsoId(torso->id);
   ui.setHeadId(head->id);
   ui.setFloorId(floor->id);
   ui.setSphereIdSet(sphereIdSet);
   window.renderloop(renderer);		// Keep rendering until an "End condition"
}
