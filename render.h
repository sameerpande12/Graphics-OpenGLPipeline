#pragma once

#include "glConstants.h"
#include "camera.h"
#include "iostream"
#include "unordered_map"
// #include "geombase.h"
// #include "geom.h"
class Scene;
class Shader;
class Geom;
class Renderer {
public:
   Renderer(int width, int height, Scene *scene, float fov = FOV_DEFAULT, float near = NEAR_DEFAULT, float far = FAR_DEFAULT);
   bool init(int width, int height, Scene *scene, float fov, float, float far);
   int update();
   int render(float *mat = NULL,bool renderMirror_not_scene=false,bool reflectScene=false,glm::vec4 reflectionPlane=glm::vec4(0,0,1,0));
   void resize(int width, int height);
   void setMat(float *mat) { rendermat = mat; }
   void useShader(Shader *shader);
   void setCameraPosition(glm::vec3 pos);
      // A renderer owns a camera
   Camera camera;
   Scene *scene;     // This is what I render
   std::unordered_map<int,Geom*> objectMap;
   int  getClosestIntersectionObject(glm::vec3 origin,glm::vec3 Direction);
   void translateObject(int id,glm::vec3 displacment);
   void rotateObject(int id, float angle, glm::vec3 axis);
   void moveSphereOnPlane(int id, float x, float y,int width,int height);
   void moveSphereInCamSpace(int id, float x, float y,int width,int height);
   void setCameraLookAt(glm::vec3 lookat);
   void setFloorId(int fid){floorId = fid;}
   int getFloorID(){return floorId;}
private:
   float fov, near, far; // Should I bother remembering? May be useful later for UI purpose.?
   int floorId;
   float *rendermat; // Renderer can use a global matrix for its scene. It is identity be default.
   Shader *current_shader; // Cache a shader. so it does not need to be set again unnecessarily
   
};
