#pragma once
#include "glConstants.h"

#include "gWindow.h"



void gWindow::setSize(int width,int height){
    this->width = width;
    this->height = height;
}

void gWindow::setGLcontext(int major,int minor,bool coreProfile){
    this->major = major;
    this->minor = minor;
    this->coreProfile = coreProfile;
}

gWindow::gWindow(int width,int height , int maj,int min,bool iscore){
        setSize(width,height);
        setGLcontext(maj,min,iscore);

};

int gWindow::Width(){return width;}
int gWindow::Height(){return height;}


        

