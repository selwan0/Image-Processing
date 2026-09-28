#include <iostream>
#include "Image_Class.h"

using namespace std;

void rotate_image(Image& image , int angle){
    int w = image.width;
    int h = image.height;


    if (angle ==90){
        Image rotated_image(h, w);
        for (int i = 0; i < w; i++) 
            for (int j=0 ; j < h ; j++)
                for (int k=0 ; k < 3 ; k++){
                    rotated_image(h-1-j , i , k)= image(i , j , k); }
        image = rotated_image;
    }
    else if (angle == 180){
        Image rotated_image(w , h);
        for (int i = 0; i < w; i++) 
            for (int j=0 ;j<h ;j++)
                for (int k=0 ; k<3 ; k++){
                    rotated_image(w-1-i , h-1-j , k )= image(i , j , k); }
        image = rotated_image;
     }
    else if (angle ==270){
        Image rotated_image(h,w);
        for (int i=0 ; i<w; i++)
            for (int j=0 ; j < h ; j++)
                for (int k=0 ; k<3 ; k++){
                    rotated_image(j , w-1-i ,k)= image(i , j , k); }
        image = rotated_image;
    }
}


