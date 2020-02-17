#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scenebase.h"
#include "geom.h"

class Scene : public SceneBase {
public:
   Scene(int *id, const char *filename=NULL) { // Read scene from filename
      if(filename == NULL) {
        Scene::init(new Geom(id), glm::mat4(1.0f), NULL, NULL); // I have a temporary scene generator
      } else {
        Scene::init(new Geom(id,filename), glm::mat4(1.0f), NULL, NULL);
      }
   }
};
