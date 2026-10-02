#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

void detect_image_edges(Image& image, int threshold = 100) {
    grayscale(image); 
    int w = image.width;  int h = image.height;
    Image edge_image(w, h);
    
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i=0 ; i < w ; i++)
        for (int j=0 ; j < h ; j++)
            for (int k=0 ; k<3 ; k++)
                edge_image(i,j,k) = 255;

    for (int i=1 ; i < h-1 ; i++){
        for (int j=1 ; j < w-1 ; j++)
            {
                int sumx =0 , sumy =0;
                for (int a = -1 ; a <=1 ; a++){
                    for (int b=-1 ; b <=1 ; b ++){
                        int px = image(j+b , i+a , 0);
                        sumx += px * gx[a+1][b+1];
                        sumy += px * gy[a+1][b+1];
                    }
                }
                int value = (abs (sumx) + abs(sumy)> threshold) ? 0 : 255;
                for (int k=0 ; k<3 ; k++)
                    edge_image(j,i,k) = value;  
            }
    }
    image = edge_image;
}
