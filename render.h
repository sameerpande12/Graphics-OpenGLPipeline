#pragma once

#include "glConstants.h"
#include "camera.h"

class Scene;
class Shader;

class Renderer {
public:
   Renderer(int width, int height, Scene *scene, float fov = FOV_DEFAULT, float near = NEAR_DEFAULT, float far = FAR_DEFAULT);
   bool init(int width, int height, Scene *scene, float fov, float, float far);
   int update();
   int render(float *mat = NULL);
   void resize(int width, int height);
   void setMat(float *mat) { rendermat = mat; }
   void useShader(Shader *shader);

private:
   float fov, near, far; // Should I bother remembering? May be useful later for UI purpose.?
   Camera camera;    // A renderer owns a camera
   float *rendermat; // Renderer can use a global matrix for its scene. It is identity be default.
   Shader *current_shader; // Cache a shader. so it does not need to be set again unnecessarily
   Scene *scene;     // This is what I render
};
