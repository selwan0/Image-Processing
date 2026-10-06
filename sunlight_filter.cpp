#include <iostream>
#include "Image_Class.h"
using namespace std;

void sunlight(Image& image){

    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image(i , j , 0);
            int green = image(i , j , 1);
            int blue = image(i , j , 2);


            red = min(255, (int)(red * 1.25 + 20));
            green = min(255, (int)(green * 1.20 + 15));
            blue = max(0, (int)(blue * 0.8));


            image(i,j,0) = red;
            image(i,j,1) = green;
            image(i,j,2) = blue;
        }
    
    }
}