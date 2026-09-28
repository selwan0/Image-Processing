#include<iostream>
#include"Image_Class.h"
#include"frame_filter.cpp"
#include "greyscale_filter.cpp"
#include "black_and_white.cpp"
#include "flip_filter.cpp"
#include "rotate_image.cpp"
#include "invert_filter.cpp"
#include "darken_and_lighten_filter.cpp"
using namespace std;

void menu() 
{
    cout<<"Image Processing Menu"<<endl;
    cout<<" 1: Download a new image "<<endl;
    cout<<" 2: Apply Frame Filter"<<endl;
    cout<<" 3: Apply Greyscale Filter"<<endl;
    cout <<" 4: Apply Black and White Filter"<<endl;
    cout<<" 5: Apply Flip Filter"<<endl;
    cout <<" 6: Apply Rotate Filter"<<endl;
    cout <<" 7: Apply Invert Filter"<<endl;
    cout<<" 8: Apply Darken and Lighten Filter"<<endl;
    cout<<" 9: Save The image "<<endl;
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
         else if (choice == 5)
        {
            int flipChoice;
            cout<<"Choose flip option:"<<endl;
            cout<<"1: Horizontal Flip"<<endl;
            cout<<"2: Vertical Flip"<<endl;
            cin>>flipChoice;
            if (flipChoice == 1) {
                Horizontal_Flip(image);
                cout << "Horizontal Flip applied" << endl;
            } else if (flipChoice == 2) {
                Vertical_Flip(image);
                cout << "Vertical Flip applied" << endl;
            } else {
                cout << "Invalid flip option" << endl;
            }
        }
        else if (choice ==6){
            int angle;
            cout << "Enter rotation angle (90, 180, 270): ";
            cin >> angle;
            rotate_image(image, angle);
            cout << "Rotation applied" << endl;
        }

        else if (choice == 7)
        {
            applyinvertfilter(image);
            cout<<"Invert Filter applied"<<endl;
        }

        else if (choice == 8)
        {
            int darkenLightenChoice;
            cout<<"Choose option:"<<endl;
            cout<<"1: Darken"<<endl;
            cout<<"2: Lighten"<<endl;
            cin>>darkenLightenChoice;
            if (darkenLightenChoice == 1) {
                applyDarkenFilter(image);
                cout << "Darken Filter applied" << endl;
            } else if (darkenLightenChoice == 2) {
                applyLightenFilter(image);
                cout << "Lighten Filter applied" << endl;
            } else {
                cout << "Invalid option" << endl;
            }
        }

        else if(choice == 9)
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
        
        cout <<"Enter output filename to save the image: ";
        cin >> filename;
        image.saveImage(filename);
        cout << "Image saved" << endl;
    }

}