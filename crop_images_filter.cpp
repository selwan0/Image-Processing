#include <iostream>
#include "Image_Class.h"
using namespace std;

void applyCropFilter(Image& image, int x, int y, int width, int height)
{
    if (x + width <= image.width && y + height <= image.height)
    {
        Image cropped(width, height);

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                int red = image.getPixel(x + i, y + j, 0);
                int green = image.getPixel(x + i, y + j, 1);
                int blue = image.getPixel(x + i, y + j, 2);

                cropped.setPixel(i, j, 0, red);
                cropped.setPixel(i, j, 1, green);
                cropped.setPixel(i, j, 2, blue);
            }
        }

        image = cropped;
    }
    else
    {
        cout << "Invalid crop dimensions!" << endl;
    }
}