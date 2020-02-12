#pragma once
#include "glConstants.h"

#define WIDTH 640
#define HEIGHT 480

class gWindow{
    public:
        void setSize(int width,int height);

        void setGLcontext(int major,int minor,bool coreProfile=false);

        int Width();
        int Height();
        

    protected:
        int width,height;
        int major,minor;
        bool coreProfile;

        gWindow(int width=WIDTH,int height = HEIGHT, int maj=OPENGLREVMAJOR,int min=OPENGLREVMINOR,bool iscore = COREPROFILE);

        virtual ~gWindow(){;}
        
        

};