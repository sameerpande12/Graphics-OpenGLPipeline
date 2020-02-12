#include <GL/glew.h>
//#include "glm/glm.hpp"
//#include "glm/gtc/type_ptr.hpp"

#include "ui.h"
#include "shader.h"
#include "scene.h"
#include "render.h"

void Renderer::useShader(Shader *shader)
{
   if(shader != current_shader)
      { shader->use(); current_shader = shader;}
}
bool Renderer::init(int width, int height, Scene *scene, float fov, float near, float far)
{
    this->fov = fov;
    this->near = near;
    this->far = far;

    //Initialize clear color
    glClearColor( 0.3f, 0.5f, 0.9f, 1.f );
    
    resize(width, height);

    rendermat = NULL;
    this->scene = scene;
    return ( glGetError() == GL_NO_ERROR );
}

Renderer::Renderer(int width, int height, Scene *scene, float fov, float near, float far):
               				camera(width, height, fov, near, far)
{
   init(width, height, scene, fov, near, far);
}

int Renderer::update()
{
   //No per frame update built-in
   return true;
}

int Renderer::render(float *mat)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(mat != NULL)
        rendermat = mat;
    return scene->render(this, camera, rendermat);
}

void Renderer::resize(int width, int height)
{
    if(height < 0)
        return;

    float ratio = (height > 0)? (float) width / (float) height : 1.0f;

    // Setup viewport
    glViewport(0, 0, width, height);

    // Change to the projection matrix and set our viewing volume
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
}
