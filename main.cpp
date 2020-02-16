#include <stdio.h>
#include "GL/glew.h"

#include "uiGLFW.h"
#include "gwindowGLFW.h"
#include "render.h"
#include "scene.h"
#include <glm/ext.hpp>
#include <iostream>
int main( int argc, char* args[] )
{
   gWindow_GLFW window("Test"); // Create a window. Use default OpenGL settings.

   int M, m;
   glGetIntegerv(GL_MAJOR_VERSION, &M);
   glGetIntegerv(GL_MINOR_VERSION, &m);
   printf("OpenGL version: %d.%d\n", M, m);

   Scene* primaryScene = new Scene();                 // Should come from a file. Temporary scene, with default shader

   glm::vec3 baseCentre = glm::vec3(0,0,-1);


   Geom * floor = new Geom("xyPlaneVertices.csv",3);
   glm::mat4 floorTransform = glm::mat4(1.0f);
   floorTransform = glm::translate(floorTransform,baseCentre+ glm::vec3(0,0,-1));
   floorTransform = glm::scale(floorTransform,glm::vec3(10,10,10));
   primaryScene->addchild(floor,floorTransform);
   
   Geom* base = new Geom("sphereVertices.csv",2);
   glm::mat4 basetransform = glm::mat4(1.f);
   
   basetransform = glm::scale(basetransform,glm::vec3(1,1,1));
   basetransform = glm::translate(basetransform,baseCentre);
   primaryScene->addchild(base,basetransform);
   
   Geom* torso = new Geom("sphereVertices.csv",1);
   glm::mat4 torsotransform = glm::mat4(1.f);
   
   torsotransform = glm::translate(torsotransform,baseCentre+ glm::vec3(0,0,1.1));
   torsotransform = glm::scale(torsotransform,glm::vec3(0.5,0.5,0.5));
   primaryScene->addchild(torso,torsotransform);



   Geom* head = new Geom("sphereVertices.csv",1);
   glm::mat4 headtransform = glm::mat4(1.f);
   headtransform = glm::translate(headtransform,baseCentre + glm::vec3(0,0,1.7));
   headtransform = glm::scale(headtransform,glm::vec3(0.33,0.33,0.33));
   primaryScene->addchild(head,headtransform);
   
   Geom** spheres = new Geom*[12];
   for(int i =0 ;i<12;i++){
      Geom* sphere = new Geom("sphereVertices.csv");
      glm::mat4 sphereTransform = glm::mat4(1.f);
      
      float radius = 0.25;
      float largeRadius = 2;
      float angle = M_PI/6 * i;

      glm::vec3 newCentre = baseCentre +  glm::vec3(0,0,-1)+ glm::vec3(0,0,radius);
      newCentre = newCentre + glm::vec3(largeRadius*cos(angle),largeRadius*sin(angle),0);
      sphereTransform = glm::translate(sphereTransform,newCentre);
      sphereTransform = glm::scale(sphereTransform,glm::vec3(radius,radius,radius));
      primaryScene->addchild(sphere,sphereTransform);
   }


   Renderer renderer(window.Width(), window.Height(), primaryScene); // Renderer renders scene from its camera
   UI_GLFW ui(&renderer, &window);	// User interface: intermediary between a renderer and a window
   window.renderloop(renderer);		// Keep rendering until an "End condition"
}
