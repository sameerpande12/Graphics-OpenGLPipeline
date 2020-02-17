#pragma once

#include <stdlib.h>
#include "gwindowGLFW.h"

class Renderer;
class gWindow;

class UI {

public:
	UI(Renderer *renderer, gWindow *window);
	bool quit() { return _quit; }	
	void signalquit() { _quit = true; }	
        void handleKeys( int key, float x, float y );
        void handleMouseUp ( int button, float x, float y );
        void handleMouseDown(int button, float x, float y );
        void handleMouseMotion( float dx, float dy );
        void handleResize(int width, int height);
        int render();

        void attach(Renderer *renderer);
   	void attach(gWindow *window);
        int getSelectionId(GLFWwindow* window,int button,double cursorX,double cursorY);

protected:
        virtual gWindow* getwindow() = 0; // May return an extension of gWindow
	bool _quit;
	Renderer *renderer;
	gWindow  *gwindow;
        float lastx, lasty;
};
