#include "camera.h"
#include "iostream"
Camera::Camera(int width, int height, float fov, float near, float far)
{
    // projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
    
    projection(width, height, fov, near, far); 
    zFar = far;
    zNear = near;
    position(4,3,3, true);
    lookat(0, 0, 0, true);
    upward(0, 0, 1, true);

    // orientation = glm::quat(up);
}

void Camera::calcProjView()
{
   viewmat = glm::lookAt(pos, at, up);
   pvmat = projmat * viewmat;
}

void Camera::view(glm::vec3 pos, glm::vec3 at, glm::vec3 up)
{
   viewmat = glm::lookAt(pos, at, up);
}

void Camera::projection(int width, int height, float fovd, float near, float far, bool update) 
{  
   camFov = fovd;
   projmat = glm::perspective(glm::radians(fovd), (float) width / (float)height, near, far);
   zFar = far;
   zNear = near;
   if(update) calcProjView();
}

void Camera::position(float x, float y, float z, bool update)
{
   pos = glm::vec3(x, y, z);
   if(update) calcProjView();
}

void Camera::lookat(float x, float y, float z, bool update)
{
   at = glm::vec3(x, y, z);
   if(update) calcProjView();
}

void Camera::upward(float x, float y, float z, bool update)
{
   up = glm::vec3(x, y, z);
   if(update) calcProjView();
}

const glm::mat4 Camera::viewmatrix()
{
   return viewmat; 
}

const glm::mat4 Camera::pvmatrix()
{
   return pvmat;
}

const glm::mat4 Camera::matrix() const
{
    // return glm::mat4(1.0f); // Test identity
    // return projmat * viewmat; // Remember, matrix multiplication is the other way around
    return pvmat; // Remember, matrix multiplication is the other way around
}

const glm::mat4 Camera::matrix(const glm::mat4 modelmat) const
{
    // ModelViewProjection
    return pvmat * modelmat; // Remember, matrix multiplication is the other way around
}

const glm::mat4 Camera::viewmatrix(const glm::mat4 modelmat) const
{
    // ModelViewProjection
    return viewmat * modelmat; // Remember, matrix multiplication is the other way around
}

const glm::vec3 Camera::getPosition()const
{
   return pos;
}

glm::vec3 Camera::viewPortToWorldRayDirection(double cursorX, double cursorY, int width, int height){
//http://antongerdelan.net/opengl/raycasting.html <- theory source for this function 


      float xNdc = (2.0 * cursorX)/(float)(width) - 1;
      float yNdc = 1 - (2.0 * cursorY)/(float)(height);
      float zNdc = -1;
      glm::vec3 rayInNdc = glm::vec3(xNdc,yNdc,zNdc);

      glm::vec4 rayInClip = glm::vec4(rayInNdc[0], rayInNdc[1],-1.0f,1.0f);
      glm::vec4 rayInCam = glm::inverse(getProjectionMatrix()) * rayInClip;
      rayInCam = glm::vec4(rayInCam[0],rayInCam[1],-1,0);//since it is a ray

      glm::vec4 rayInWorld4d = glm::inverse(viewmatrix())*rayInCam;
      glm::vec3 rayInWorld = glm::vec3(rayInWorld4d[0],rayInWorld4d[1],rayInWorld4d[2]);

      rayInWorld = glm::normalize(rayInWorld);
      return rayInWorld;
}
