#include <iostream>
#include <vector>
#include <Image_Class.h>
using namespace std;

void applyOilPaintingFilter(Image& image, int brushSize , int levels =20) {
    Image result(image.width, image.height);

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            vector<int> count(levels, 0), rSum(levels, 0), gSum(levels, 0), bSum(levels, 0);

            for (int dy = -brushSize; dy <= brushSize; ++dy) {
                for (int dx = -brushSize; dx <= brushSize; ++dx) {
                    int newX = x + dx;
                    int newY = y + dy;

                    if (newX >= 0 && newX < image.width && newY >= 0 && newY < image.height) {
                        int r = image.getPixel(newX, newY, 0);
                        int g = image.getPixel(newX, newY, 1);
                        int b = image.getPixel(newX, newY, 2);
                        int level = ((r+g+b)/3) * (levels - 1)/255;
                        count[level]++;
                        rSum[level] += r;    gSum[level]+=g;     bSum[level]+= b;
                    }
                }
            }
            int best =0;
            for (int i = 1 ; i< levels ; i++){
                if (count[i] > count[best]) best =i;
            }

            result.setPixel(x, y, 0, rSum[best] / count[best]);
            result.setPixel(x, y, 1, gSum[best] / count[best]);
            result.setPixel(x, y, 2, bSum[best] / count[best]);
        }
    }
    for (int y = 0 ; y < image.height; y++){
        for (int x =0 ; x < image.width ; x++){
            for (int k = 0; k < 3; k++){
                image.setPixel(x,y,k, result.getPixel(x,y,k));
            }
        }
    }
}