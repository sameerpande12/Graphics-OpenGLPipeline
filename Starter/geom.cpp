#include "geom.h"
#include "render.h"
#include "shader.h"

int Geom::read(const char *filename)
{
   float points[] = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
   };

   GLuint vbo = 0;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

   glBindVertexArray(vao);

   shader = new Shader("data/vs.glsl", "data/fs.glsl"); 
   // shader = new Shader();

   return vao;
}

int Geom::render(Renderer *renderer, glm::mat4 rendermat) const
{
    renderer->useShader(shader);
    shader->setXform((const GLfloat*)glm::value_ptr(rendermat));
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    return glGetError();
}
