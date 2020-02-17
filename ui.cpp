#include "ui.h"
#include "render.h"
#include "gwindow.h"
#include "uiConstants.h"
#include <iostream>
#include "GL/glut.h"
#include "GL/glew.h"

struct Color{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};


UI::UI(Renderer *renderer, gWindow *window)
{
  _quit = false;
  attach(renderer);
  attach(window);

  lastx = lasty = -1.0;
}

void UI::attach(Renderer *renderer)
{
   this->renderer = renderer;
}

void UI::attach(gWindow *window)
{
   this->gwindow = window;
}

int UI::render()
{
   bool r = renderer->update();
   return r? renderer->render() : r;
}

void UI::handleKeys(int key, float x, float y )
{
   switch (key)
   {
      case CHARDEF(Q):
      case KEYDEF(ESCAPE):
            _quit = true;
            break;
      case KEYDEF(LEFT):
            std::cout<<"Pressed left"<<"\n";
            break;
      case KEYDEF(RIGHT):
            break;
      case KEYDEF(UP):
            break;
      case KEYDEF(DOWN):
            break;
   }
}


void UI::handleMouseDown(int button, float x, float y )
{
   lastx = x; lasty = y;
   if(button != 0) return;
}

void UI::handleMouseUp(int button, float x, float y )
{
   lastx = x; lasty = y;
   if(button != 0) return;
}


void UI::handleMouseMotion(float x, float y)
{
   lastx = x; lasty = y;
}

void UI::handleResize(int width, int height)
{
    renderer->resize(width, height);
}

void printVec(std::string str,glm::vec3 vec){
         std::cout<<str<<" ";
         std::cout<<vec[0]<<","<<vec[1]<<","<<vec[2]<<"\n";
}
int UI::getSelectionId(GLFWwindow* window,int button,double cursorX,double cursorY){
//http://antongerdelan.net/opengl/raycasting.html
      int width,height;
      glfwGetWindowSize(window,&width,&height);

      float xNdc = (2.0 * cursorX)/(float)(width) - 1;
      float yNdc = 1 - (2.0 * cursorY)/(float)(height);
      float zNdc = -1;
      glm::vec3 rayInNdc = glm::vec3(xNdc,yNdc,zNdc);

      glm::vec4 rayInClip = glm::vec4(rayInNdc[0], rayInNdc[1],-1.0f,1.0f);
      glm::vec4 rayInCam = glm::inverse(renderer->camera.getProjectionMatrix()) * rayInClip;
      rayInCam = glm::vec4(rayInCam[0],rayInCam[1],-1,0);//since it is a ray

      glm::vec4 rayInWorld4d = glm::inverse(renderer->camera.viewmatrix())*rayInCam;
      glm::vec3 rayInWorld = glm::vec3(rayInWorld4d[0],rayInWorld4d[1],rayInWorld4d[2]);

      rayInWorld = glm::normalize(rayInWorld);

      glm::vec3 cameraPosInWorld = renderer->camera.getPosition();


      // printVec("ray Direction ",rayInWorld);
      // printVec("ray Origin ", cameraPosInWorld);

      int id = renderer->getClosestIntersectionObject(cameraPosInWorld,rayInWorld);
      std::cout<<"objid ="<<id<<"\n";
      
      return 0;       
}
