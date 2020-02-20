#include "gwindowGLFW.h"
#include "ui.h"
#include "render.h"

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//========================================================================
// Quit macros
//========================================================================

#define QUIT(m,v)      { fprintf(stderr, "%s:%s\n", m, v); exit(1); }
#define QUITBOX(m,v)   { exit(1); }     // TODO Throw a dialog box
#define ABORT(m,v)     { fprintf(stderr, "%s:%s\n", m, v); return FALSE; }
#define ABORTBOX(m,v)  { return FALSE; }// TODO Throw a dialog box

//========================================================================
// Print errors
//========================================================================

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

gWindow_GLFW::gWindow_GLFW(const char *name, int w, int h, int maj, int min) : gWindow(w, h, maj, min)
{

    // glewExperimental = GL_TRUE;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        QUIT("gWindow_GLFW", "Could not Initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);

    if(coreProfile) {
       glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__ 
       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
   }

    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window) {
        glfwTerminate();
        QUIT("gWindow_GLFW", "Could not create Window");
    }

    glfwMakeContextCurrent(window);

    if ( GLEW_OK != glewInit() ) {
        glfwTerminate();
        QUIT("gWindow_GLFW","glewInit failed");
    }

    glfwSwapInterval(1);
    glfwGetFramebufferSize(window, &width, &height);
}

gWindow_GLFW::~gWindow_GLFW()
{
    glfwTerminate();
    window = NULL;
}

int gWindow_GLFW::renderloop(Renderer &renderer)
{
//    glEnable(GL_CULL_FACE);
   while (!glfwWindowShouldClose(window))
   {
    //    glClearStencil(0);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //    glEnable(GL_DEPTH_BUFFER_BIT);
    //    glDisable(GL_STENCIL_TEST);

    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_STENCIL_TEST);
    renderer.render(NULL,false,false);//render all but mirror

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glStencilFunc(GL_ALWAYS,1,~0);//always set the values to 1 to all those things that pass the z test
    glColorMask(0,0,0,0);//disable writing to color buffer
    renderer.render(NULL,true,false);//render mirror
    //now above steps have tagged all visible pixels of mirror

    glDepthRange(1,1);
    glDepthFunc(GL_ALWAYS);
    glStencilFunc(GL_EQUAL,1,~0);
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    renderer.render(NULL,true,false);//render mirror

    glDepthFunc(GL_LESS);
    glColorMask(1,1,1,1);
    glDepthRange(0,1);

    renderer.render(NULL,false,true);//render all but mirror. Also reflect the scene

    glColorMask(0,0,0,0);
    glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);
    glDepthFunc(GL_ALWAYS);
    renderer.render(NULL,true,false);//render mirror only, do not update color buffer
    
    glDepthFunc(GL_LESS);
    glColorMask(1,1,1,1);


    //   if( first * second * third * fourth * fifth  ==0)
        // QUIT("renderloop", "Renderer refused to continue");
      glfwSwapBuffers(window);
      glfwWaitEvents();
    
      
      // glfwPollEvents();
   }

   return 0; // Should we return some error code?
}
