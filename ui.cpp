#include "ui.h"
#include "render.h"
#include "gwindow.h"
#include "scene.h"
#include "uiConstants.h"
#include "geombase.h"
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
            // std::cout<<"Pressed left"<<"\n";
            break;
      case KEYDEF(RIGHT):
            break;
      case KEYDEF(UP):
            break;
      case KEYDEF(DOWN):
            break;
      case KEYDEF(LEFT_SHIFT):
            // std::cout<<"pressed left shift\n";
            break;
      case KEYDEF(RIGHT_SHIFT):
            break;
            // std::cout<<"right shift is pressed\n";
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

void UI::handleMouseDrag(float x, float y){
   if(getMousePressStatus()){
      float dy = (lasty - y)/(float)(gwindow->Height());
      float dx = (x - lastx)/(float(gwindow->Width()));
      
      if(!selectedSomeObject() || selectedObjectId == floorId){
         if(getShiftPressedStatus()){
            glm::vec3 camNegZ = glm::normalize(renderer->camera.at - renderer->camera.pos);
            renderer->setCameraPosition(renderer->camera.pos + camNegZ * dy * 2.0f);
         }
         else{
            // std::cout<<dy<<"\n";
            glm::mat4 viewmat = renderer->camera.viewmatrix();
            glm::vec3 right = glm::vec3(viewmat[0][0],viewmat[1][0],viewmat[2][0]);
            glm::vec3 up = glm::vec3(viewmat[0][1],viewmat[1][1],viewmat[2][1]);
            renderer->setCameraLookAt(renderer->camera.at + 2.0f * up * dy);
            renderer->setCameraLookAt(renderer->camera.at + 2.0f * right * dx);

         }
      }
      else if(selectedObjectId == baseId){
         renderer->rotateObject(baseId,dx*2 ,glm::vec3(0,0,1));
         renderer->rotateObject(torsoId,dx*2 ,glm::vec3(0,0,1));
         renderer->rotateObject(headId,dx*2 ,glm::vec3(0,0,1));
      }
      else if(selectedObjectId == torsoId){
         renderer->rotateObject(torsoId,dx*2 ,glm::vec3(0,0,1));
         renderer->rotateObject(headId,dx*2 ,glm::vec3(0,0,1));
      }
      else if( selectedObjectId == headId){
         renderer->rotateObject(headId,dx*2 ,glm::vec3(0,0,1));
      }
      else if(isSideBallId(selectedObjectId)){
         if(getShiftPressedStatus()){
            renderer->moveSphereInCamSpace(selectedObjectId,x,y,gwindow->Width(),gwindow->Height());
         }
         else{      
            renderer->moveSphereOnPlane(selectedObjectId,x,y,gwindow->Width(),gwindow->Height());
         }
      }
   }

   lastx = x;
   lasty = y;
//  std::cout<<y<<"\n";

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
      // std::cout<<"Selected Object = "<<id<<"\n";

      double t ;
      t = (-0.75 - cameraPosInWorld[2])/rayInWorld[2];
      glm::vec3 intersection = cameraPosInWorld + rayInWorld * (float)t;
      // std::cout<<"getSelectionId cursorX "<<cursorX<<" cursorY"<<cursorY<<"\n";
      // printVec("intersection with z = -0.75->", intersection);

      return id;
}
