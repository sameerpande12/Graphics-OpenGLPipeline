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

int Renderer::render(float *mat,bool renderMirror,bool reflectScene)
{
    if(mat != NULL)
        rendermat = mat;
    return scene->render(this, camera, rendermat,renderMirror, reflectScene);
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
void Renderer::setCameraLookAt(glm::vec3 look){
    camera.lookat(look[0],look[1],look[2]);
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

void Renderer::translateObject(int id,glm::vec3 displacment){//works consdering sphere
    std::vector<SceneBase*> allScenes = scene->getAllDescendantScenes();
    for(int i =0 ;i<allScenes.size();i++){
        SceneBase* childScene = allScenes[i];
        if(childScene->getObjectId()==id){
            childScene->translate(displacment);
            Geom* object = objectMap[id];
            if(object->isSphere){
                glm::vec4 newPosition = childScene->applyObjMat(glm::vec4(0,0,0,1));
                object->featureVec = glm::vec3(newPosition[0],newPosition[1],newPosition[2]);
            }
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

void printVe(std::string str,glm::vec3 vec){
         std::cout<<str<<" ";
         std::cout<<vec[0]<<","<<vec[1]<<","<<vec[2]<<"\n";
};
void Renderer::moveSphereOnPlane(int id, float cursorX, float cursorY,int width, int height){//assumes id is sphere and x,y are mouse coordinates
    Geom* sphere = objectMap[id]; 
    float z = sphere->featureVec[2];
    
    glm::vec3 rayDirectionWorld = camera.viewPortToWorldRayDirection(cursorX,cursorY,width,height);
    
    glm::vec3 rayOrigin = camera.getPosition();
    
    if(rayDirectionWorld[2]==0)return;

    float t = (z - rayOrigin[2])/rayDirectionWorld[2];
    if(t<0)return;

    glm::vec3 newPosition = rayOrigin + t * rayDirectionWorld ;

    glm::vec3 translation = newPosition - sphere->featureVec;    
    translateObject(id,translation);

}

void Renderer::moveSphereInCamSpace(int id, float cursorX, float cursorY,int width, int height){//assumes id is sphere and x,y are mouse coordinates
    Geom* sphere = objectMap[id];
    
    glm::vec3 oldPosInWorldCord = sphere->featureVec;
    glm::vec3 oldPosInCamCord = glm::vec3(camera.viewmatrix() * glm::vec4(oldPosInWorldCord,1));

    glm::vec3 rayInCam = camera.viewPortToCameraRayDirection(cursorX,cursorY,width,height);
    float camZ  = oldPosInCamCord[2];

    if(rayInCam[2]==0)return ;

    float t = (camZ)/rayInCam[2];
    glm::vec3 newPosInCamCord = t * rayInCam;
    glm::vec3 newPosInWorldCord =   glm::vec3( glm::inverse(camera.viewmatrix()) * glm::vec4(newPosInCamCord,1));
    glm::vec3 translation = newPosInWorldCord - oldPosInWorldCord;
    translateObject(id,translation);
    
}