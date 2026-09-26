#include<iostream>
#include"Image_Class.h"
#include"frame_filter.cpp"
#include "greyscale_filter.cpp"
#include "black_and_white.cpp"
using namespace std;

void menu() 
{
  //  cout<< "Image Processing Menu"<<endl;
   // cout<<" 1: Download a new image "<<endl;

    cout <<"    filter Menu"<<endl;
    cout<<" 2: Apply Frame Filter"<<endl;
    cout<<" 3: Apply Greyscale Filter"<<endl;
    cout<<" 4: Apply Black and White Filter"<<endl;
   // cout<<" 5: Save The image "<<endl;
    cout<<" 0: Exit "<<endl;
    cout<<" choose an option from this:";
}


int main()
{
    string filename;
    int choice;
    int threshold = 128;
    Image image;
    
    while(true) 
    {
        cout << "Download a new image" << endl;
        cout << "Enter image filename: ";
        cin >> filename;
        image.loadNewImage(filename);
        cout << "Image loaded" << endl;


        menu();
        cin>>choice;
       /* if(choice == 1)
        {
            cout<<" Enter image filename: " ;
            cin>>filename;
            image.loadNewImage(filename);
            cout<<"Image loaded"<<endl;
        }*/
        /*else*/ if (choice == 2)
        {
            applyframefilter(image);
            cout<<"Frame Filter applied"<<endl;
        }
        else if (choice == 3)
        {
            greyscale(image);
            cout<<"Greyscale Filter applied"<<endl;
        }
        else if (choice == 4)
        {
            black_and_white(image,128);
            cout<<"Black and White Filter applied"<<endl;
        }
       /* else if(choice == 5)
        {
            cout<<" Enter output filename"<<endl;
            cin>>filename;
            image.saveImage(filename);
            cout<<"Image saved"<<endl;
        }*/
        else if(choice == 0)
        {
            cout<<"Exit the program"<<endl;
            break;
        }
        
        cout <<"Enter output filename to save the image: ";
        cin >> filename;
        image.saveImage(filename);
        cout << "Image saved" << endl;
    }

}