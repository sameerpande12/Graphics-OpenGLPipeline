#include <GL/glew.h>
//#include "glm/glm.hpp"
//#include "glm/gtc/type_ptr.hpp"
#include "limits"
#define INF std::numeric_limits<double>::infinity();
#include <vector>
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

int Renderer::render(float *mat,bool selectionMode)
{
    if(mat != NULL)
        rendermat = mat;
    return scene->render(this, camera, rendermat,selectionMode);
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
void Renderer::setCameraPosition(glm::vec3 pos){
    camera.position(pos[0],pos[1],pos[2]);

}

int Renderer::getClosestIntersectionObject(glm::vec3 origin,glm::vec3 Direction){
    double tmin = INF;
    int objId = -1;
    for(auto i = objectMap.begin();i!=objectMap.end();i++){
        double tVal = objectMap[i->first]->getIntersectionTValue(origin,Direction);
        if(tVal >= 0 && tVal < tmin){
            tmin = tVal;
            objId = i->first;
        }
    }
    return objId;
    
};

void Renderer::translateObject(int id,glm::vec3 displacment){
    std::vector<SceneBase*> allScenes = scene->getAllDescendantScenes();
    for(int i =0 ;i<allScenes.size();i++){
        SceneBase* childScene = allScenes[i];
        if(childScene->getObjectId()==id){
            childScene->translate(displacment);
        }
    }

};

void Renderer::rotateObject(int id, float angle, glm::vec3 axis){
    std::vector<SceneBase*> allScenes = scene->getAllDescendantScenes();
    for(int i =0 ;i<allScenes.size();i++){
        SceneBase* childScene = allScenes[i];
        if(childScene->getObjectId()==id){
            childScene->rotate(angle,axis);
        }
    }
}