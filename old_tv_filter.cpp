#include <iostream>
#include <string>
#include <algorithm>
#include "Image_Class.h"
using namespace std;

void old_tv_filter (Image& image) {
    Image old_tv_image(image.width, image.height);
    auto clampPixel = [] (int v ){
        return (v < 0) ? 0 : (v > 255) ? 255 : v;
    };
    int shift = 5 , noiseAmount = 20 , lineGap = 3 ;
    float lineDarkness = 0.4;

    for (int j =0 ; j < image.height ; j++){
        int glitch =0;
        if ( rand() % 20 ==0 ) glitch = (rand() % 20 )- 10;
        float lineFactor = (j % lineGap == 0) ? lineDarkness : 1.0;

        for (int i =0 ; i < image.width ; i++){
            int noise = (rand() % (2 * noiseAmount + 1)) - noiseAmount;

            for (int k = 0 ; k < 3 ; k++){
                int shifted_i = i + glitch;
                if (k == 0) shifted_i += shift;
                else if (k == 2) shifted_i -= shift;
                shifted_i = max (min (shifted_i , image.width-1), 0);


                int oldPixel = image(shifted_i, j, k) * lineFactor + noise;
                old_tv_image(i,j,k) = clampPixel(oldPixel);
            }
        }
    }
    image = old_tv_image;
}
