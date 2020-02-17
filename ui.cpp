#include "ui.h"
#include "render.h"
#include "gwindow.h"
#include "uiConstants.h"
#include <iostream>
#include "GL/glut.h"
#include "GL/glew.h"
#define BUFSIZE 1024

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
      // std::cout<<"cursor Pos:("<<cursorX<<" "<<cursorY<<")\n";
      Color color;
      int width,height;
      glfwGetWindowSize(window,&width,&height);
      // std::cout<<"window width= "<<width<<" height = "<<height<<"\n";
      // std::cout<<"pixel pos: ("<<cursorX<<" ,"<<height-cursorY - 1<<")\n";
      // glReadPixels(cursorX ,height - cursorY - 1,1,1,GL_RGBA,GL_FLOAT,&color);
      // std::cout<<"color : ("<<color.r<<","<<color.g<<","<<color.b<<","<<color.a<<")\n\n";

      float screenX = cursorX/width - 0.5;
      float screenY = (height-cursorY-1)/height - 0.5;
      // std::cout<<viewPortX<<","<<viewPortY<<"\n";
      glm::mat4 viewmatrix = renderer->camera.viewmatrix();
      glm::vec3 right = glm::vec3(viewmatrix[0][0],viewmatrix[1][0],viewmatrix[2][0]);//in world coordinate
      glm::vec3 up = glm::vec3(viewmatrix[0][1],viewmatrix[1][1],viewmatrix[2][1]);//in world coordinate
      glm::vec3 forward = glm::vec3(viewmatrix[0][2],viewmatrix[1][2],viewmatrix[2][2]);

      printVec("right",right);
      printVec("up",up);
      printVec("forward",forward);
      float tanVal = tan(renderer->camera.camFov/2);
      float aspectRatio = width/height;
      glm::vec3 rayDirection = glm::normalize((tanVal* aspectRatio *  screenX * right +  tanVal * screenY * up)  - forward);
      Scene* scene = renderer->scene;
      // int id = scene->getClosestIntersectionObject();
      
      return 0;       
}
