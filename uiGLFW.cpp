#include "uiConstants.h"
#include "uiGLFW.h"

#include <iostream>

//========================================================================
// Handle key strokes
//========================================================================

UI_GLFW *UI_GLFW::currentUI = NULL;

gWindow_GLFW* UI_GLFW::getwindow()
{
   return ((gWindow_GLFW *)gwindow);
}

void UI_GLFW::makeCurrent()
{
   currentUI = this;
}

UI_GLFW::UI_GLFW(Renderer *renderer, gWindow_GLFW *window) : UI (renderer, window)
{
   // The last one started is automatically currentUI
   makeCurrent();
   setEventAction();
}

void UI_GLFW::handleKeysGLFW(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS){
        if(key==GLFW_KEY_LEFT_SHIFT || key==GLFW_KEY_RIGHT_SHIFT){
                // std::cout<<"Pressed shift"<<'\n';
               currentUI->UI::pressShift();
        }

        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        currentUI->UI::handleKeys(key, cursorX, cursorY);
    }
    else if(action == GLFW_RELEASE){
        if(key==GLFW_KEY_LEFT_SHIFT || key==GLFW_KEY_RIGHT_SHIFT){
               currentUI->UI::releaseShift();
               std::cout<<"Released shift"<<'\n';
        }
    }
    if(currentUI->quit())
         glfwSetWindowShouldClose(window, GL_TRUE);
}

//========================================================================
// Callback function for mouse button events
//========================================================================

void UI_GLFW::handleMouseClickGLFW(GLFWwindow* window, int button, int action, int mods)
{
    double cursorX, cursorY;
    if (action == GLFW_PRESS)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT){
            currentUI->UI::setMousePressed(true);
            std::cout<<"pressed left mouse key\n";
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(window, &cursorX, &cursorY);
        currentUI->UI::handleMouseDown(button, cursorX, cursorY);
        currentUI->UI::getSelectionId(window,button,cursorX,cursorY);
    }
    else
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT){
            currentUI->UI::setMousePressed(false);
            std::cout<<"released left mouse key\n";
        }
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwGetCursorPos(window, &cursorX, &cursorY);
        currentUI->UI::handleMouseUp(button, cursorX, cursorY);
    }
}

//========================================================================
// Callback function for cursor motion events
//========================================================================

void UI_GLFW::handleMouseMotionGLFW(GLFWwindow* window, double x, double y)
{
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
    {
        // currentUI->UI::handleMouseMotion(x - currentUI->cursorX, y - currentUI->cursorY);
        // std::cout<<" numshifts pressed = "<<currentUI->getNumShiftsPressed()<<"\n";
        currentUI->cursorX = x;
        currentUI->cursorY = y;
        currentUI->UI::handleMouseMotion(x, y);
    }
}

//========================================================================
// Callback function for framebuffer resize events
//========================================================================

// Should this be handeld by Renderer?
void UI_GLFW::handleResizeGLFW(GLFWwindow* window, int width, int height)
{
    currentUI->UI::handleResize(width, height);
}

void UI_GLFW::setEventAction()
{
    GLFWwindow *win = getwindow()->internalWindow();
    glfwSetKeyCallback(win, handleKeysGLFW);
    glfwSetFramebufferSizeCallback(win, handleResizeGLFW);
    glfwSetMouseButtonCallback(win, handleMouseClickGLFW);
    glfwSetCursorPosCallback(win, handleMouseMotionGLFW);
}
