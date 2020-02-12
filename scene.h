#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scenebase.h"
#include "geom.h"

class Scene : public SceneBase {
public:
   Scene(const char *filename=NULL) { // Read scene from filename
      if(filename == NULL) {
        Scene::init(new Geom(), glm::mat4(1.0f), NULL, NULL); // I have a temporary scene generator
      } else {
        printf("Scene reading from file Unimplemented");
      }
   }
};
