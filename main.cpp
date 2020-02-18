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

   std::unordered_map<int,Geom*> objects;
   int M, m;
   glGetIntegerv(GL_MAJOR_VERSION, &M);
   glGetIntegerv(GL_MINOR_VERSION, &m);
   printf("OpenGL version: %d.%d\n", M, m);

   int id = STARTID;
   Scene* primaryScene = new Scene(&id);                 // Should come from a file. Temporary scene, with default shader
   glm::vec3 baseCentre = glm::vec3(0,0,0);

   

   Geom * floor = new Geom(&id,"xyPlaneVertices.csv",false/*,id++*/);
   glm::mat4 floorTransform = glm::mat4(1.0f);
   float floorScale = 10;
   float floorHeight = -1;
   floorTransform = glm::translate(floorTransform,baseCentre+ glm::vec3(0,0,floorHeight));
   
   
   floorTransform = glm::scale(floorTransform,glm::vec3(floorScale,floorScale,floorScale));
   floor->setModelMatrix(floorTransform);

   floor->featureValue = -1;
   floor->featureVec = glm::vec3(0,0,1);
   floor->minBounds = glm::vec3(-.5 * floorScale,-.5 * floorScale,floorHeight);
   floor->maxBounds = glm::vec3(0.5 * floorScale, 0.5 * floorScale,floorHeight);


   objects[floor->id]=floor;
   primaryScene->addchild(floor,floor->id,floor->getModelMatrix());
   cout<<"floor "<<floor->id<<"\n";
   
   Geom* base = new Geom(&id,"sphereVertices.csv"/*,id++*/);
   glm::mat4 basetransform = glm::mat4(1.f);
   basetransform = glm::scale(basetransform,glm::vec3(1,1,1));
   basetransform = glm::translate(basetransform,baseCentre);

   base->featureValue = 1;
   base->featureVec = baseCentre;
   base->setModelMatrix(basetransform);
   objects[base->id]=base;
   primaryScene->addchild(base,base->id,base->getModelMatrix());
   cout<<"base "<<base->id<<"\n";
   
   Geom* torso = new Geom(&id,"sphereVertices.csv"/*,id++*/);
   glm::mat4 torsotransform = glm::mat4(1.f);
   glm::vec3 torsoCentre = baseCentre+ glm::vec3(0,0,1.1);
   torsotransform = glm::translate(torsotransform,torsoCentre);
   torsotransform = glm::scale(torsotransform,glm::vec3(0.5,0.5,0.5));

   torso->featureValue = 0.5;
   torso->featureVec = torsoCentre;
   torso->setModelMatrix(torsotransform);
   objects[torso->id]=torso;
   primaryScene->addchild(torso,torso->id,torso->getModelMatrix());
   cout<<"torso "<<torso->id<<"\n";


   Geom* head = new Geom(&id,"sphereVertices.csv"/*,id++*/);
   glm::mat4 headtransform = glm::mat4(1.f);
   glm::vec3 headCentre = baseCentre + glm::vec3(0,0,1.7);
   headtransform = glm::translate(headtransform,headCentre);
   headtransform = glm::scale(headtransform,glm::vec3(0.33,0.33,0.33));

   head->featureValue = 0.33;
   head->featureVec = headCentre;
   head->setModelMatrix(headtransform);
   objects[head->id]=head;
   primaryScene->addchild(head,head->id,head->getModelMatrix());
   cout<<"head "<<head->id<<"\n";
   
   Geom** spheres = new Geom*[12];
   std::unordered_set<int> sphereIdSet;
   for(int i =0 ;i<12;i++){
      Geom* sphere = new Geom(&id,"sphereVertices.csv"/*,id++*/);
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

      cout<<"sphere("<<i<<") "<<sphere->id<<"\n";
   }


   Renderer renderer(window.Width(), window.Height(), primaryScene); // Renderer renders scene from its camera
   renderer.objectMap = objects;

   UI_GLFW ui(&renderer, &window);	// User interface: intermediary between a renderer and a window
   ui.setBaseId(base->id);
   ui.setTorsoId(torso->id);
   ui.setHeadId(head->id);
   ui.setFloorId(floor->id);
   ui.setSphereIdSet(sphereIdSet);
   window.renderloop(renderer);		// Keep rendering until an "End condition"
}
