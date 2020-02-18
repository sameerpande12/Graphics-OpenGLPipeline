#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "scenebase.h"
#include "geom.h"

class Scene : public SceneBase {
public:
   Scene(int *id, const char *filename=NULL) { // Read scene from filename
      int sceneId = *id;
      if(filename == NULL) {
        Scene::init(new Geom(id),sceneId, glm::mat4(1.0f), NULL, NULL); // I have a temporary scene generator
      } else {
        Scene::init(new Geom(id,filename),sceneId, glm::mat4(1.0f), NULL, NULL);
      }
   }
  // int render(Renderer *renderer, const Camera &camera, const float *mat,bool selectionMode)
  // {
  //   if(mat == NULL) 
  //       return render(renderer, camera, glm::mat4(1.0f),selectionMode);
  //   else
  //       return render(renderer, camera, glm::make_mat4(mat),selectionMode);
  // }

  // int render(Renderer *renderer, const Camera &camera, glm::mat4 mat,bool selectionMode) {
  //  glm::mat4 nextmat = mat * objmat; // objmat must not be NULL
  //  object->render(renderer, camera.matrix(nextmat),camera.viewmatrix(nextmat),selectionMode);
  //  bool result = true;
  //  for(SceneBase* cur = firstchild; cur != NULL; cur = cur->getSibling()) {
  //     result &= cur->render(renderer, camera, nextmat,selectionMode);
  //  }
  //  return result;
  // }
};
