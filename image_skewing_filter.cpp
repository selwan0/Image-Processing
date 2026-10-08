#include <iostream>
#include <cmath>
#include "Image_Class.h"
using namespace std;

void applySkewFilter(Image& image, int angle)
{
    double pi = 3.141592653589793;

    double maxShift = (image.height - 1) * tan(angle * pi / 180);

    int newWidth = image.width + (int)abs(maxShift);

    Image skewed(newWidth, image.height);

    for (int y = 0; y < image.height; y++)
    {
        double shift = y * tan(angle * pi / 180);

        for (int x = 0; x < image.width; x++)
        {
            int newX = (int)(x + shift);

            int red = image.getPixel(x, y, 0);
            int green = image.getPixel(x, y, 1);
            int blue = image.getPixel(x, y, 2);

            skewed.setPixel(newX, y, 0, red);
            skewed.setPixel(newX, y, 1, green);
            skewed.setPixel(newX, y, 2, blue);
        }
    }

    image = skewed;
}