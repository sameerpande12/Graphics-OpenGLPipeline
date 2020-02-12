#pragma once 
#include "gWindow.h"

class GLFWwindow;

class gWindow_GLFW : public gWindow{

    public:
        gWindow_GLFW(const char *name, int width=WIDTH, int height=HEIGHT, int major=OPENGLREVMAJOR, int minor=OPENGLREVMINOR);
       ~gWindow_GLFW();

    private:
        GLFWwindow * window;
};