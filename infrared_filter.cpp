#include<iostream>
#include"Image_Class.h"
using namespace std;

void infraredImage(Image& image) 
{
    for(int i = 0 ; i< image.width ; ++i)
    {
        for(int j = 0 ; j< image.height ; ++j)
        {
            int Red = image(i , j , 0);
            int Green = image(i , j , 1);
            int Blue = image(i , j , 2);

            int gray = (Red + Green + Blue) / 3;

            int newRed = 255;
            int newGreen = gray;
            int newBlue = gray;

            image.setPixel(i , j ,0 , newRed);
            image.setPixel(i , j , 1 , newGreen);
            image.setPixel(i , j , 2 , newBlue);
        }
    }
     
        
    
}