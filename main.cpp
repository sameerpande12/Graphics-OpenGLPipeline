#include <stdio.h>
#include "GL/glew.h"

#include "uiGLFW.h"
#include "gwindowGLFW.h"
#include "render.h"
#include "scene.h"
#include <glm/ext.hpp>

int main( int argc, char* args[] )
{

   gWindow_GLFW window("Test"); // Create a window. Use default OpenGL settings.

   int M, m;
   glGetIntegerv(GL_MAJOR_VERSION, &M);
   glGetIntegerv(GL_MINOR_VERSION, &m);
   printf("OpenGL version: %d.%d\n", M, m);

   Scene* baseScene = new Scene();                 // Should come from a file. Temporary scene, with default shader
   Geom* sphere1 = new Geom("vertices.csv");
   glm::mat4 transform1 = glm::mat4(1.f);
   transform1 = glm::translate(transform1,glm::vec3(0,0,0));

   baseScene->addchild(sphere1,transform1);
   Renderer renderer(window.Width(), window.Height(), baseScene); // Renderer renders scene from its camera
   UI_GLFW ui(&renderer, &window);	// User interface: intermediary between a renderer and a window
   window.renderloop(renderer);		// Keep rendering until an "End condition"
}
