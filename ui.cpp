#include "ui.h"
#include "render.h"
#include "gwindow.h"
#include "uiConstants.h"
#include <iostream>
#define BUFSIZE 1024
struct Color{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};
void processHits (GLint hits, GLuint buffer[]);

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
      std::cout<<"cursor Pos:("<<cursorX<<" "<<cursorY<<")\n";
      Color color;
      int width,height;
      glfwGetWindowSize(window,&width,&height);
      // std::cout<<"window width= "<<width<<" height = "<<height<<"\n";
      std::cout<<"pixel pos: ("<<cursorX<<" ,"<<height-cursorY - 1<<")\n";
      glReadPixels(cursorX ,height - cursorY - 1,1,1,GL_RGBA,GL_FLOAT,&color);
      std::cout<<"color : ("<<color.r<<","<<color.g<<","<<color.b<<","<<color.a<<")\n\n";

      //https://www.glprogramming.com/red/chapter13.html
      GLuint selectBuf[BUFSIZE];
      GLuint hits;
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);
      glSelectBuffer(BUFSIZE, selectBuf);
      (void) glRenderMode(GL_SELECT);


      glInitNames();
      glPushName(0);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // std::cout<<"getSelectionId be"<<"\n";
      renderer->render(NULL,true);
      // std::cout<<"getSelectionId end"<<"\n";
      
      hits = glRenderMode(GL_RENDER);
      processHits(hits,selectBuf);

      return 0;       
}
void processHits (GLint hits, GLuint buffer[])////https://www.glprogramming.com/red/chapter13.html
{
   unsigned int i, j;
   GLuint ii, jj, names, *ptr;

   printf ("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++) { /*  for each hit  */
      names = *ptr;
      printf (" number of names for this hit = %d\n", names);
         ptr++;
      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
      printf ("   names are ");
      for (j = 0; j < names; j++) { /*  for each name */
         printf ("%d ", *ptr);
         if (j == 0)  /*  set row and column  */
            ii = *ptr;
         else if (j == 1)
            jj = *ptr;
         ptr++;
      }
      printf ("\n");
   }
}
