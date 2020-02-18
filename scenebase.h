#pragma once
#include <list>
#include <glm/ext.hpp>
#include "vector"
class GeomBase;
class Camera;
class Renderer;

class SceneBase {
private:
   GeomBase *object;
   glm::mat4   objmat;

   SceneBase *sibling;
   SceneBase *firstchild;
   int sceneId;
public:
   inline void set(GeomBase *g) { object = g; }
   inline void set(glm::mat4 m) { objmat = m; }
   inline void set(SceneBase *ch) { firstchild = ch; }
   inline void set(int newId){sceneId = newId;}
   SceneBase() {} // For a child to manage
   SceneBase(GeomBase *obj, int id,glm::mat4 mat = glm::mat4(1.0f),
             SceneBase *next=NULL, SceneBase *child=NULL);
   void init(GeomBase *obj,int id, glm::mat4 mat, SceneBase *next, SceneBase *child);
   int render(Renderer *renderer, const Camera &camera, const glm::mat4 mat = glm::mat4(1.0f),bool selectionMode=false);
   int render(Renderer *renderer, const Camera &camera, const float *mat=NULL,bool selectionMode=false);
   SceneBase* addchild(GeomBase *obj, int id,glm::mat4 mat = glm::mat4(1.0f));
   int getObjectId(){return sceneId;}
   SceneBase* getSibling(){return sibling;}
   SceneBase* getFirstChild(){return firstchild;}
   std::vector<SceneBase*> getAllDescendantScenes();
   void translate(glm::vec3 displacment){
      set(glm::translate(objmat,displacment));
   }
   void rotate(float angle, glm::vec3 axis){
      set(glm::rotate(objmat,angle,axis));
   }
   glm::vec4 applyObjMat(glm::vec4 inputVector){
      return objmat * inputVector;
   }

};
