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
   std::cout<<argc<<" ;;\n";
   gWindow_GLFW window("Test"); // Create a window. Use default OpenGL settings.

   int M, m;
   glGetIntegerv(GL_MAJOR_VERSION, &M);
   glGetIntegerv(GL_MINOR_VERSION, &m);
   printf("OpenGL version: %d.%d\n", M, m);

   Scene* baseScene = new Scene();                 // Should come from a file. Temporary scene, with default shader
   
   
   Geom* base = new Geom("sphereVertices.csv",1);
   glm::mat4 basetransform = glm::mat4(1.f);
   basetransform = glm::scale(basetransform,glm::vec3(0.5,0.5,0.5));
   basetransform = glm::translate(basetransform,glm::vec3(0,0,-1));
   
   baseScene->addchild(base,basetransform);

   Geom* torso = new Geom("sphereVertices.csv",2);
   glm::mat4 torsotransform = glm::mat4(1.f);
   torsotransform = glm::scale(torsotransform,glm::vec3(0.5,0.5,0.5));
   torsotransform = glm::translate(torsotransform,glm::vec3(0,0,.5));
   baseScene->addchild(torso,torsotransform);
   


   Renderer renderer(window.Width(), window.Height(), baseScene); // Renderer renders scene from its camera
   UI_GLFW ui(&renderer, &window);	// User interface: intermediary between a renderer and a window
   window.renderloop(renderer);		// Keep rendering until an "End condition"
}
