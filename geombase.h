#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class Renderer;
class Shader;

class GeomBase {

public:
   virtual int render(Renderer *renderer, glm::mat4 rendermat,glm::mat4 viewrendermat) const = 0;
   virtual int read(const char *filename) = 0;
   void attachshader(Shader *shad) { shader = shad; }

protected:
   GLuint vao;
   GLuint tex;
   Shader *shader;
}; 
