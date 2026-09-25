#include<iostream>
#include"Image_Class.h"
using namespace std;

void applyframefilter(Image& image)
{
    int framewidth = 10;
    int framecolorRed = 255;
    int framecolorGreen = 255;
    int framecolorBlue = 255;
     for(int i=0 ; i<image.width ; ++i)
     {
        for(int j=0 ; j<image.height ; ++j)
        {
            if(i<framewidth || i>= image.width - framewidth || j< framewidth || j>= image.height - framewidth)
            {
                image.setPixel(i,j,0,framecolorRed);
                image.setPixel(i,j,1,framecolorGreen);
                image.setPixel(i,j,2,framecolorBlue);
            }
                
        }
     }
}