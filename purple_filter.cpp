#include <iostream>
#include <algorithm>
#include "Image_Class.h"
using namespace std;

void applyPurpleFilter(Image& image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int red = image.getPixel(i, j, 0);
            int green = image.getPixel(i, j, 1);
            int blue = image.getPixel(i, j, 2);

            image.setPixel(i, j, 0, min((red * 30) / 100 + red, 255));
            image.setPixel(i, j, 1, max(green - (green * 30) / 100, 0));
            image.setPixel(i, j, 2, min((blue * 30) / 100 + blue, 255));
        }
    }
}