#include<iostream>
#include"Image_Class.h"
#include"frame_filter.cpp"
using namespace std;

void menu() 
{
    cout<< "Image Processing Menu"<<endl;
    cout<<" 1: Download a new image "<<endl;
    cout<<" 2: Apply filter according to team member's filter"<<endl;
    cout<<" 3: Save The image "<<endl;
    cout<<" 0: Exit "<<endl;
    cout<< "choose an option from this:";
}


int main()
{
    string filename;
    int choice;
    Image image;
    
    while(true) 
    {
        menu();
        cin>>choice;
        if(choice == 1)
        {
            cout<<" Enter image filename: " ;
            cin>>filename;
            image.loadNewImage(filename);
            cout<<"Image loaded"<<endl;
        }
        else if (choice == 2)
        {
            applyframefilter(image);
            cout<<"Filter applied"<<endl;
        }
        else if (choice == 3)
        {
            cout<<" Enter output filename"<<endl;
            cin>>filename;
            image.saveImage(filename);
            cout<<"Image saved"<<endl;
        }
        else if(choice == 0)
        {
            cout<<"Exit the program"<<endl;
            break;
        }
    }
    
    return 0;


}