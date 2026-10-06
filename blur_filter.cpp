#include<iostream>
#include"Image_Class.h"
using namespace std;

void blurImage(Image& image , int radius)
{
    Image result = image;

    for(int i=0 ; i<image.width ;i++)
    {
        for(int j=0 ; j<image.height ;j++)
        {
            for(int c=0 ; c<3 ; c++)
            {
                int sum =0;
                int count =0;
                
                for(int di= -radius ; di<= radius ; di++){
                    for(int dj = -radius ; dj<= radius ; dj++){
                        int neig_i = i+di;
                        int neig_j = j+dj;
                        if(neig_i >= 0 && neig_i < image.width && neig_j >= 0 && neig_j < image.height)
                        {
                            sum += image(neig_i , neig_j , c);
                            count++ ;
                        }
                    }
                }
                result( i, j, c) = sum / count ;
            }
        }
    }
    image = result;
}
