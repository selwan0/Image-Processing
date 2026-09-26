#include<iostream>
#include"Image_Class.h"
using namespace std;

void applyinvertfilter(Image& image)
{
    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image.getPixel(i , j , 0);
            int green = image.getPixel(i , j , 1);
            int blue = image.getPixel(i , j , 2);
            image.setPixel(i , j , 0 , 255 - red);
            image.setPixel(i , j , 1 , 255 - green);
            image.setPixel(i , j , 2 , 255 - blue);
        }

            }
    }


    