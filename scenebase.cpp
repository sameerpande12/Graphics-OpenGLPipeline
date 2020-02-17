#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scenebase.h"
#include "camera.h"
#include "geombase.h"
#include "render.h"

int SceneBase::render(Renderer *renderer, const Camera &camera, const float *mat,bool selectionMode)
{
   if(mat == NULL) 
      return render(renderer, camera, glm::mat4(1.0f),selectionMode);
   else
      return render(renderer, camera, glm::make_mat4(mat),selectionMode);
}

int SceneBase::render(Renderer *renderer, const Camera &camera, glm::mat4 mat,bool selectionMode) {
   glm::mat4 nextmat = mat * objmat; // objmat must not be NULL
   object->render(renderer, camera.matrix(nextmat),camera.viewmatrix(nextmat),selectionMode);
   bool result = true;
   for(SceneBase* cur = firstchild; cur != NULL; cur = cur->sibling) {
      result &= cur->render(renderer, camera, nextmat);
   }
   return result;
}

SceneBase* SceneBase::addchild(const GeomBase *obj, glm::mat4 mat) {
   SceneBase *sn = new SceneBase(obj, mat, firstchild, NULL);
   firstchild = sn;
   return sn;
}

void SceneBase::init(const GeomBase *obj, glm::mat4 mat, SceneBase *next, SceneBase *child)
{
   set(obj); set(mat);
   this->sibling = next;
   this->firstchild = child;
}

SceneBase::SceneBase(const GeomBase *obj, glm::mat4 mat, SceneBase *next, SceneBase *child)
{
   init(obj, mat, next, child);
}
