#include "gwindowGLFW.h"
#include <cstdlib>
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


static void error_callback(int error, const char * description){
    fprintf(stderr, "Error: %s\n",description);
}

gWindow_GLFW::gWindow_GLFW(const char *name, int w, int h, int maj, int min) : gWindow(w, h, maj, min){

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