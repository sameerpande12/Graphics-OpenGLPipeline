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
        void handleMouseDrag(float x, float y);
        void handleResize(int width, int height);
        int render();

        void attach(Renderer *renderer);
   	void attach(gWindow *window);
        int getSelectionId(GLFWwindow* window,int button,double cursorX,double cursorY);
        void setMousePressed(bool val){mousePressed = val;}
        bool getMousePressStatus(){return mousePressed;}
        void pressShift(){numShiftsPressed++;}
        void releaseShift(){numShiftsPressed--;}
        int getNumShiftsPressed(){return numShiftsPressed;}
        bool getShiftPressedStatus(){return (numShiftsPressed>0);}
        void selectObject(int objectId){ selectedObjectId = objectId;}
        int  getSelectedObjectId(){return selectedObjectId;}
        void unSelectAllObjects(){selectedObjectId = -1;}
        bool selectedSomeObject(){return selectedObjectId >=0;}

        void setHeadId(int hid){headId = hid;}
        void setTorsoId(int torId){torsoId=torId;}
        void setBaseId(int bid){baseId = bid;}

protected:
        virtual gWindow* getwindow() = 0; // May return an extension of gWindow
	bool _quit;
	Renderer *renderer;
	gWindow  *gwindow;
        float lastx, lasty;
        bool mousePressed;
        int numShiftsPressed = 0;
        int selectedObjectId = -1;
        int baseId;
        int torsoId;
        int headId;
};
