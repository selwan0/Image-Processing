#include<iostream>
#include"Image_Class.h"
#include <algorithm>
using namespace std;

void applyDarkenFilter(Image& image)
{
    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image.getPixel(i , j , 0);
            int green = image.getPixel(i , j , 1);
            int blue = image.getPixel(i , j , 2);
            image.setPixel(i , j , 0 , red*0.5);
            image.setPixel(i , j , 1 , green*0.5);
            image.setPixel(i , j , 2 , blue*0.5);
        }
    
    }
}
void applyLightenFilter(Image& image)
{
    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image.getPixel(i , j , 0);
            int green = image.getPixel(i , j , 1);
            int blue = image.getPixel(i , j , 2);
            image.setPixel(i , j , 0 , min(((red*0.5) + red ), 255));
            image.setPixel(i , j , 1 , min(((green*0.5) + green ), 255));
            image.setPixel(i , j , 2 , min(((blue*0.5) + blue ), 255));
        }
    
    }
}