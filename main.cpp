//Header:
//Student Name:Selwan Ayman Mustafa     Student ID: 20250292    Filters: greyscale, flip
//Student Name:Sama Ahmed Ibrahim       Student ID: 20250294    Filters: black and white, rotate
//Student Name:Kenzi Ali Nosier         Student ID: 20250499    Filters: invert, darken and lighten
//Student Name:Nada Mohamed Refaat      Student ID: 20250704    Filters: frame, resize


#include<iostream>
#include"Image_Class.h"
#include"frame_filter.cpp"
#include "greyscale_filter.cpp"
#include "black_and_white.cpp"
#include "flip_filter.cpp"
#include "rotate_image.cpp"
#include "invert_filter.cpp"
#include "darken_and_lighten_filter.cpp"
#include "resize_filter.cpp"
using namespace std;

void menu() 
{
    cout<<"Image Processing Menu"<<endl;
    cout<<" 1: Load New Image"<<endl;
    cout<<" 2: Apply Frame Filter"<<endl;
    cout<<" 3: Apply Greyscale Filter"<<endl;
    cout <<" 4: Apply Black and White Filter"<<endl;
    cout<<" 5: Apply Flip Filter"<<endl;
    cout <<" 6: Apply Rotate Filter"<<endl;
    cout <<" 7: Apply Invert Filter"<<endl;
    cout<<" 8: Apply Darken and Lighten Filter"<<endl;
    cout<<" 9: Apply Resize Filter"<<endl;
    cout<<" 10: Save The image "<<endl;
    cout<<" 0: Exit "<<endl;
    cout<<" choose an option from this:";
}

void load_image(Image& image , string& file_name){
    while (true){
        cout << "Enter file name :";
        cin >> file_name;
        
        int dot = file_name.find_last_of('.');
        string ext = (dot == -1) ? " " : file_name.substr(dot);
        if (ext!= ".jpg" && ext != ".jpeg" && ext != ".png" && ext != ".bmp" ){
            cout << "Invalid file extension. "<<endl<< "Please enter a valid image file name (.jpg, .jpeg, .png, .bmp)." << endl;
            continue;
        }
        image.loadNewImage(file_name);
        if (!image.imageData) {
            cout << "Failed to load image." << endl;
            continue;
        }
        break;
    }
}
void save_image(Image& image , string& file_name){
    char saveChoice;
    cout<<"Do you want to save the image on the same filename or a new filename? (s/n): ";
    cin>>saveChoice;
    if(saveChoice == 's' || saveChoice == 'S')
    {
        image.saveImage(file_name);
        cout<<"Image saved on the same filename"<<endl;
    }
    else if(saveChoice == 'n' || saveChoice == 'N')
    {
        string newFilename;
        cout<<"Enter the new filename: ";
        cin>>newFilename;
        string newFileExt = newFilename.substr(newFilename.find_last_of('.'));
        if (newFileExt != ".jpg" && newFileExt != ".jpeg" && newFileExt != ".png" && newFileExt != ".bmp") {
            cout << "Invalid file extension. Please enter a valid extension (.jpg, .jpeg, .png, .bmp)." << endl;
            return;
        }
        image.saveImage(newFilename);
        cout<<"Image saved on a new filename"<<endl;
    }
    else
    {
        cout<<"Invalid choice. Image not saved."<<endl;
    }
}

int main()
{
    string filename;
    int choice ;
    int threshold = 128;
    Image image;
    load_image(image, filename);


    while(true) 
    
    {

        menu();
        cin>>choice;
       if(choice == 1)
        {

            cout<<"Do you want to save the current image before loading a new one? (y/n): ";
            char saveChoice;
            cin>>saveChoice;
            if(saveChoice == 'y' || saveChoice == 'Y')
            {
                save_image(image, filename);
            }
            else if(saveChoice == 'n' || saveChoice == 'N')
            {
                cout<<"Proceeding to load a new image without saving."<<endl;
            }
            else
            {
                cout<<"Invalid choice. Proceeding to load a new image without saving."<<endl;
            }
            cout<<" Enter image filename: " ;
            cin>>filename;
            
            image.loadNewImage(filename);
            cout<<"Image loaded"<<endl;
        }
        else if (choice == 2)
        {
            int colorchoice, type;
            cout<< " 1:white " <<endl;
            cout<< " 2:Black " <<endl;
            cout<< " 3:Red " <<endl;
            cout<< " 4:Green " <<endl;
            cout<< " 5:Blue " <<endl;
            cout<<"choose color: ";
            cin>> colorchoice;

            cout<<" choose frame type: "<<endl;
            cout<< " 1:simple frame "<<endl;
            cout<< " 2:fancy frame "<<endl;
            cin>>type;

            applyframefilter(image , colorchoice , type);
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
            resize_image(image);
            cout<<"Resize Filter Applied"<<endl;
        
        }

        else if(choice == 10)
        {
            save_image(image, filename);
        }
         
        else if(choice == 0)
        {
            cout<<"Do you want to save the image before exiting? (y/n): ";
            char saveChoice;
            cin>>saveChoice;
            if(saveChoice == 'y' || saveChoice == 'Y')
            {
                save_image(image, filename);
                cout<<"Image saved"<<endl;
            }
            else if(saveChoice == 'n' || saveChoice == 'N')
            {
                cout<<"Exiting without saving."<<endl;
            }
            else
            {
                cout<<"Invalid choice. Exiting without saving."<<endl;
            }
            break;
        }
        
    }

}