#include<iostream>
#include<string>
#include"Image_Class.h"
using namespace std;

void applyframefilter(Image& image , int colorchoice , int type )
{
    int thickness = min (image.width , image.height)/30;
    if(thickness < 5) thickness=5;
    
    int Red=255 , Green=255 , Blue=255;
    if(colorchoice == 2) {Red=0 ; Green=0 ; Blue=0;}
    if(colorchoice==3) {Red=255 ; Green=0 ; Blue=0;}
    if(colorchoice==4) {Red=0 ; Green=255 ; Blue=0;}
    if(colorchoice==5) {Red=0 ; Green=0 ; Blue=255;}
   
     for(int i=0 ; i<image.height ; ++i)
     {
        for(int j=0 ; j<image.width ; ++j)
        {
            bool simpleframe = (j < thickness || j >= image.width - thickness || i< thickness || i >= image.height- thickness);
            int space = thickness + 20;
            int innerthickness = 10;
            bool outerline = (j<thickness || j>= image.width - thickness ||i< thickness || i>= image.height - thickness);

            bool innerline = ((j>= space && j<space + innerthickness && i>= space && i< image.height - space)
            ||(j>= image.width - space - innerthickness && j<image.width - space && i>= space && i<image.height - space)
            ||(i>= space && i<space + innerthickness && j>= space && j<image.width - space)
            ||(i>=image.height - space - innerthickness && i<image.height - space && j>= space && j< image.width - space));
            
            bool fancyframe = outerline || innerline;

            if(type==1 && simpleframe) 
            {
                image(j,i,0) = Red;
                image(j,i,1) = Green;
                image(j,i,2) = Blue;
            }
            else if(type==2 && fancyframe) 
            {
                image(j,i,0) = Red;
                image(j,i,1) = Green;
                image(j,i,2) = Blue;
            }
                
        }
     }
}