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


      printVec("ray Direction ",rayInWorld);
      printVec("ray Origin ", cameraPosInWorld);

      int id = renderer->getClosestIntersectionObject(cameraPosInWorld,rayInWorld);
      std::cout<<"objid ="<<id<<"\n\n";
      // // std::cout<<"cursor Pos:("<<cursorX<<" "<<cursorY<<")\n";
      // Color color;
      
      // // std::cout<<"window width= "<<width<<" height = "<<height<<"\n";
      // // std::cout<<"pixel pos: ("<<cursorX<<" ,"<<height-cursorY - 1<<")\n";
      // // glReadPixels(cursorX ,height - cursorY - 1,1,1,GL_RGBA,GL_FLOAT,&color);
      // float zBuf;
      // glReadPixels(cursorX,height-cursorY-1,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&zBuf );
      // float zNear = renderer->camera.zNear;
      // float zFar = renderer->camera.zFar;
      // // std::cout<<"zbuf value "<<zBuf<<'\n';

      // // std::cout<<"color : ("<<color.r<<","<<color.g<<","<<color.b<<","<<color.a<<")\n\n";

      // float screenX = cursorX/width - 0.5;
      // float screenY = (height-cursorY-1)/height - 0.5;
      // std::cout<<"screenCoordinate "<<screenX<<","<<screenY<<"\n";
      // glm::mat4 viewmatrix = renderer->camera.viewmatrix();
      // glm::vec3 right = glm::vec3(viewmatrix[0][0],viewmatrix[1][0],viewmatrix[2][0]);//in world coordinate
      // glm::vec3 up = glm::vec3(viewmatrix[0][1],viewmatrix[1][1],viewmatrix[2][1]);//in world coordinate
      // glm::vec3 forward = glm::vec3(viewmatrix[0][2],viewmatrix[1][2],viewmatrix[2][2]);

      // // printVec("right",right);
      // // printVec("up",up);
      // // printVec("forward",forward);


      // float tanVal = tan(  M_PI/180*   renderer->camera.camFov/2);
      // float aspectRatio = width/height;
      // glm::vec3 rayDirection = glm::normalize(  tanVal *aspectRatio *  screenX * right +   tanVal * screenY * up  - forward );
      // glm::vec3 rayOrigin = renderer->camera.pos;
      
      
      // // printVec("rayDir in WorldSpace:",rayDirection);
      // // printVec("ray Origin in World Space: ",rayOrigin);
      // int id = renderer->getClosestIntersectionObject(rayOrigin,rayDirection);
      
      // std::cout<<"objId = "<<id<<"\n\n\n";

      
      
      return 0;       
}
