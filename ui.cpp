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
      int width,height;
      glfwGetWindowSize(window,&width,&height);
      glm::vec3 rayInWorld = renderer->camera.viewPortToWorldRayDirection(cursorX,cursorY,width,height);
      glm::vec3 cameraPosInWorld = renderer->camera.getPosition();
      int id = renderer->getClosestIntersectionObject(cameraPosInWorld,rayInWorld);
      std::cout<<"objid ="<<id<<"\n";
      
      return 0;       
}
