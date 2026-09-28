#include<iostream>
#include"Image_Class.h"
using namespace std;
void resize_image(Image& image)
{
    cout<< "current image width: " << image.width << "current image height: " << image.height <<endl;
    int new_width , new_height;
    cout<<"Enter new width:";
    cin>>new_width;
    cout<<"Enter new height:";
    cin>>new_height;

    Image resized_image(new_width , new_height);
    for(int i=0 ; i<new_height ; ++i)
    {
        for(int j=0 ; j<new_width ; ++j)
        {
            int orig_i = i*image.height / new_height;
            int orig_j = j*image.width / new_width;

            for(int k=0; k<image.channels; ++k)
            {
                resized_image(j,i,k) = image(orig_j , orig_i , k);
            }
        }
    }
    image = resized_image;
}

