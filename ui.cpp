#include "ui.h"
#include "render.h"
#include "gwindow.h"
#include "uiConstants.h"
#include <iostream>

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

int UI::getSelectionId(GLFWwindow* window,int button,double cursorX,double cursorY){
   std::cout<<cursorX<<" "<<cursorY<<"\n";
        Color color;
        std::cout<<"begin reading color\n";
        int width,height;
        glfwGetWindowSize(window,&width,&height);
        std::cout<<"window width= "<<width<<" height = "<<height<<"\n";
        glReadPixels(width -cursorX - 1,height - cursorY - 1,1,1,GL_RGBA,GL_FLOAT,&color);
        std::cout<<color.r<<","<<color.g<<","<<color.b<<","<<color.a<<"\n";
      return 0;       
}