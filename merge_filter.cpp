#include <iostream>
#include <Image_Class.h>
#include <algorithm>
#include <string>
using namespace std;

void merge(Image& image1, Image& image2, int mergeType) {
    int W, H, mode = 0;
    
    if (image1.width == image2.width && image1.height == image2.height) {
        W = image1.width;
        H = image1.height;
    }
    else if(mergeType == 1) {
        mode = 1;
        W = max(image1.width, image2.width);
        H = max(image1.height, image2.height);
    }
    else if(mergeType == 2) {
        mode = 2;
        W = min(image1.width, image2.width);
        H = min(image1.height, image2.height);
    }
    Image outputImage (W, H);
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            int i1, j1, i2, j2;
            if (mode == 2) {
                i1 = i + (image1.width - W) / 2;
                j1 = j + (image1.height - H) / 2;
                i2 = i + (image2.width - W) / 2;
                j2 = j + (image2.height - H) / 2;
            }
            else {
                i1 = i * image1.width / W;
                j1 = j * image1.height / H;
                i2 = i * image2.width / W;
                j2 = j * image2.height / H;
            }
            for (int k = 0; k < 3; k++) {
                outputImage(i, j, k) = (image1(i1, j1, k) + image2(i2, j2, k)) / 2;
            }
        }
    }
    image1 = outputImage;
}