//Header:
//Student Name:Selwan Ayman Mustafa     Student ID: 20250292    Filters: greyscale, flip
//Student Name:Sama Ahmed Ibrahim       Student ID: 20250294    Filters: black and white, rotate
//Student Name:Kenzi Ali Nosier         Student ID: 20250499    Filters: invert, darken and lighten
//Student Name:Nada Mohamed Refaat      Student ID: 20250704    Filters: frame, resize
//Section: S40


#include<iostream>
#include"Image_Class.h"
#include<string>
#include<algorithm>
using namespace std;


void applyframefilter(Image& image , int colorchoice , int type )
{
    int thickness = min (image.width , image.height)/30;
    if(thickness < 5) thickness=5;
    
    int Red=255 , Green=255 , Blue=255;
    if(colorchoice == 2) {Red=0 ; Green=0 ; Blue=0;}
    if(colorchoice==3) {Red=255 ; Green=0 ; Blue=0;}
    if(colorchoice==4) {Red=0 ; Green=255 ; Blue=0;}
    if(colorchoice==5) {Red=0 ; Green=0 ; Blue=255;}
   
     for(int i=0 ; i<image.height ; ++i)
     {
        for(int j=0 ; j<image.width ; ++j)
        {
            bool simpleframe = (j < thickness || j >= image.width - thickness || i< thickness || i >= image.height- thickness);
            int space = thickness + 20;
            int innerthickness = 10;
            bool outerline = (j<thickness || j>= image.width - thickness ||i< thickness || i>= image.height - thickness);

            bool innerline = ((j>= space && j<space + innerthickness && i>= space && i< image.height - space)
            ||(j>= image.width - space - innerthickness && j<image.width - space && i>= space && i<image.height - space)
            ||(i>= space && i<space + innerthickness && j>= space && j<image.width - space)
            ||(i>=image.height - space - innerthickness && i<image.height - space && j>= space && j< image.width - space));
            
            bool fancyframe = outerline || innerline;

            if(type==1 && simpleframe) 
            {
                image(j,i,0) = Red;
                image(j,i,1) = Green;
                image(j,i,2) = Blue;
            }
            else if(type==2 && fancyframe) 
            {
                image(j,i,0) = Red;
                image(j,i,1) = Green;
                image(j,i,2) = Blue;
            }
                
        }
     }
}

void grayscale(Image&image) {
    
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            unsigned int average = 0;

            for (int k = 0; k < 3; k++) {

                average += image(i, j, k);
            }

            average = average / 3;
            for (int k = 0; k < 3; k++) {

                image(i, j, k) = average;
                
            }
        }
    }
}

void black_and_white(Image& image , int threshold = 128) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            unsigned int average = 0;

            for (int k = 0; k < 3; k++) {

                average += image(i, j, k);
            }

            average = average / 3;
            if (average > threshold) {
                for (int k = 0; k < 3; k++) {
                    image(i, j, k) = 255;
                }
            } else {
                for (int k = 0; k < 3; k++) {
                    image(i, j, k) = 0;
                }
            }
        }
    }
}

void Horizontal_Flip(Image& image) {
    for (int i = 0; i < image.width / 2; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                unsigned char temp = image(i, j, k);
                image(i, j, k) = image(image.width - 1 - i, j, k);
                image(image.width - 1 - i, j, k) = temp;
            }
        }
    }
}

void Vertical_Flip(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height / 2; j++) {
            for (int k = 0; k < 3; k++) {
                unsigned char temp = image(i, j, k);
                image(i, j, k) = image(i, image.height - 1 - j, k);
                image(i, image.height - 1 - j, k) = temp;
            }
        }
    }
}

void rotate_image(Image& image , int angle){
    int w = image.width;
    int h = image.height;


    if (angle ==90){
        Image rotated_image(h, w);
        for (int i = 0; i < w; i++) 
            for (int j=0 ; j < h ; j++)
                for (int k=0 ; k < 3 ; k++){
                    rotated_image(h-1-j , i , k)= image(i , j , k); }
        image = rotated_image;
    }
    else if (angle == 180){
        Image rotated_image(w , h);
        for (int i = 0; i < w; i++) 
            for (int j=0 ;j<h ;j++)
                for (int k=0 ; k<3 ; k++){
                    rotated_image(w-1-i , h-1-j , k )= image(i , j , k); }
        image = rotated_image;
     }
    else if (angle ==270){
        Image rotated_image(h,w);
        for (int i=0 ; i<w; i++)
            for (int j=0 ; j < h ; j++)
                for (int k=0 ; k<3 ; k++){
                    rotated_image(j , w-1-i ,k)= image(i , j , k); }
        image = rotated_image;
    }
}


void applyinvertfilter(Image& image)
{
    for(int i=0 ; i<image.width ; ++i){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image.getPixel(i , j , 0);
            int green = image.getPixel(i , j , 1);
            int blue = image.getPixel(i , j , 2);
            image.setPixel(i , j , 0 , 255 - red);
            image.setPixel(i , j , 1 , 255 - green);
            image.setPixel(i , j , 2 , 255 - blue);
        }

            }
    }


void applyDarkenFilter(Image& image)
{
    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image.getPixel(i , j , 0);
            int green = image.getPixel(i , j , 1);
            int blue = image.getPixel(i , j , 2);
            image.setPixel(i , j , 0 , red*0.5);
            image.setPixel(i , j , 1 , green*0.5);
            image.setPixel(i , j , 2 , blue*0.5);
        }
    
    }
}

void applyLightenFilter(Image& image)
{
    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image.getPixel(i , j , 0);
            int green = image.getPixel(i , j , 1);
            int blue = image.getPixel(i , j , 2);
            image.setPixel(i , j , 0 , min(((red*0.5) + red ), 255.0));
            image.setPixel(i , j , 1 , min(((green*0.5) + green ), 255.0));
            image.setPixel(i , j , 2 , min(((blue*0.5) + blue ), 255.0));
        }
    
    }
}

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



void detect_image_edges(Image& image, int threshold = 100) {
    grayscale(image); 
    int w = image.width;  int h = image.height;
    Image edge_image(w, h);
    
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i=0 ; i < w ; i++)
        for (int j=0 ; j < h ; j++)
            for (int k=0 ; k<3 ; k++)
                edge_image(i,j,k) = 255;

    for (int i=1 ; i < h-1 ; i++){
        for (int j=1 ; j < w-1 ; j++)
            {
                int sumx =0 , sumy =0;
                for (int a = -1 ; a <=1 ; a++){
                    for (int b=-1 ; b <=1 ; b ++){
                        int px = image(j+b , i+a , 0);
                        sumx += px * gx[a+1][b+1];
                        sumy += px * gy[a+1][b+1];
                    }
                }
                int value = (abs (sumx) + abs(sumy)> threshold) ? 0 : 255;
                for (int k=0 ; k<3 ; k++)
                    edge_image(j,i,k) = value;  
            }
    }
    image = edge_image;
}
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

void old_tv_filter (Image& image) {
    Image old_tv_image(image.width, image.height);
    auto clampPixel = [] (int v ){
        return (v < 0) ? 0 : (v > 255) ? 255 : v;
    };
    int shift = 5 , noiseAmount = 20 , lineGap = 3 ;
    float lineDarkness = 0.4;

    for (int j =0 ; j < image.height ; j++){
        int glitch =0;
        if ( rand() % 20 ==0 ) glitch = (rand() % 20 )- 10;
        float lineFactor = (j % lineGap == 0) ? lineDarkness : 1.0;

        for (int i =0 ; i < image.width ; i++){
            int noise = (rand() % (2 * noiseAmount + 1)) - noiseAmount;

            for (int k = 0 ; k < 3 ; k++){
                int shifted_i = i + glitch;
                if (k == 0) shifted_i += shift;
                else if (k == 2) shifted_i -= shift;
                shifted_i = max (min (shifted_i , image.width-1), 0);


                int oldPixel = image(shifted_i, j, k) * lineFactor + noise;
                old_tv_image(i,j,k) = clampPixel(oldPixel);
            }
        }
    }
    image = old_tv_image;
}
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


void sunlight(Image& image){

    for(int i=0 ; i<image.width ; i++){
        for(int j=0 ; j<image.height ; ++j)
        {
            int red = image(i , j , 0);
            int green = image(i , j , 1);
            int blue = image(i , j , 2);


            red = min(255, (int)(red * 1.25 + 20));
            green = min(255, (int)(green * 1.20 + 15));
            blue = max(0, (int)(blue * 0.8));


            image(i,j,0) = red;
            image(i,j,1) = green;
            image(i,j,2) = blue;
        }
    
    }
}

void infraredImage(Image& image) 
{
    for(int i = 0 ; i< image.width ; ++i)
    {
        for(int j = 0 ; j< image.height ; ++j)
        {
            int Red = image(i , j , 0);
            int Green = image(i , j , 1);
            int Blue = image(i , j , 2);

            int gray = (Red + Green + Blue) / 3;

            int newRed = 255;
            int newGreen = gray;
            int newBlue = gray;

            image.setPixel(i , j ,0 , newRed);
            image.setPixel(i , j , 1 , newGreen);
            image.setPixel(i , j , 2 , newBlue);
        }
    }   
}
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


void applyOilPaintingFilter(Image& image, int brushSize) {
    Image result(image.width, image.height);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int rSum = 0, gSum = 0, bSum = 0;
            int count = 0;

            for (int dy = -brushSize; dy <= brushSize; ++dy) {
                for (int dx = -brushSize; dx <= brushSize; ++dx) {
                    int newX = x + dx;
                    int newY = y + dy;

                    if (newX >= 0 && newX < image.width && newY >= 0 && newY < image.height) {
                        rSum += image.getPixel(newX, newY, 0);
                        gSum += image.getPixel(newX, newY, 1);
                        bSum += image.getPixel(newX, newY, 2);
                        count++;
                    }
                }
            }

            result.setPixel(x, y, 0, rSum / count);
            result.setPixel(x, y, 1, gSum / count);
            result.setPixel(x, y, 2, bSum / count);
        }
    }

    image = result;
}

void menu() 
{
    cout<<"Image Processing Menu"<<endl;
    cout<<" 1: Load New Image"<<endl;
    cout<<" 2: Apply Grayscale Filter"<<endl;
    cout<<" 3: Apply Black and White Filter"<<endl;
    cout<<" 4: Apply Invert Filter"<<endl;
    cout<<" 5: Apply Frame Filter"<<endl;
    cout<<" 6: Apply Flip Filter"<<endl;
    cout<<" 7: Apply Rotate Filter"<<endl;
    cout<<" 8: Apply Darken and Lighten Filter"<<endl;
    cout<<" 9: Apply Resize Filter"<<endl;
    cout<<" 10: Apply Merge Filter"<<endl;
    cout<<" 11: Apply Detect Image Edges Filter"<<endl;
    cout<<" 12: Apply Crop Image Filter"<<endl;
    cout<<" 13: Apply Blur Filter"<<endl;
    cout<<" 14: Apply sunlight Filter"<<endl;
    cout<<" 15: Apply Old Tv Filter"<<endl;
    cout<<" 16: apply Purple Filter"<<endl;
    cout<<" 17: Apply Infrared Filter"<<endl;
    cout<<" 18: Apply Skew Filter"<<endl;
    cout<<" 19: Apply Oil Painting Filter"<<endl;
    cout<<" 20: Save The image "<<endl;
    cout<<" 0: Exit "<<endl;
    cout<<" choose an option from this:";
}

void load_image(Image& image , string& file_name){
    while (true){
        cout << "Enter file name :";
        cin >> file_name;
        
        int dot = file_name.find_last_of('.');
        string ext = (dot == -1) ? " " : file_name.substr(dot);
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
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
        transform(newFilename.begin(), newFilename.end(), newFilename.begin(), ::tolower);
        string newFileExt = newFilename.substr(newFilename.find_last_of('.'));
        transform(newFileExt.begin(), newFileExt.end(), newFileExt.begin(), ::tolower);
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
    bool saved = true;
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
            grayscale(image);
            saved = false;
            cout<<"Grayscale Filter applied"<<endl;
        }
        else if (choice == 3)
        {
            black_and_white(image,128);
            saved = false;
            cout<<"Black and White Filter applied"<<endl;
        }
        else if (choice == 4)
        {
            applyinvertfilter(image);
            saved = false;
            cout<<"Invert Filter applied"<<endl;
        }
        else if (choice == 5)
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


         else if (choice == 6)
        {
            int flipChoice;
            cout<<"Choose flip option:"<<endl;
            cout<<"1: Horizontal Flip"<<endl;
            cout<<"2: Vertical Flip"<<endl;
            cin>>flipChoice;
            if (flipChoice == 1) {
                Horizontal_Flip(image);
                saved = false;
                cout << "Horizontal Flip applied" << endl;
            } else if (flipChoice == 2) {
                Vertical_Flip(image);
                saved = false;
                cout << "Vertical Flip applied" << endl;
            } else {
                cout << "Invalid flip option" << endl;
            }
        }
        else if (choice == 7){
            int angle;
            cout << "Enter rotation angle (90, 180, 270): ";
            cin >> angle;
            rotate_image(image, angle);
            saved = false;
            cout << "Rotation applied" << endl;
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
                saved = false;
                cout << "Darken Filter applied" << endl;
            } else if (darkenLightenChoice == 2) {
                applyLightenFilter(image);
                saved = false;
                cout << "Lighten Filter applied" << endl;
            } else {
                cout << "Invalid option" << endl;
            }
        }

        else if(choice == 9)
        {
            resize_image(image);
            saved = false;
            cout<<"Resize Filter Applied"<<endl;
        
        }

        else if(choice == 10)
        {
            Image image2;
            string file2;
            cout << "Enter the filename of the second image to merge: ";
            load_image(image2, file2);

            int mergeType = 1;

            if (image.width != image2.width || image.height != image2.height) {
                cout << "The images have different dimensions, Please choose a merge type:" << endl;
                cout << "1: Resize to the biggest dimensions" << endl;
                cout << "2: Crop to the smallest dimensions (Common Area)" << endl;
                cin >> mergeType;
            }
            else{
                cout << "Invalid merge type" << endl;
            }

            merge(image, image2, mergeType);
            saved = false;
            cout << "Images merged successfully." << endl;
        }


        else if(choice == 11)
        {
            detect_image_edges(image, 100);
            saved = false;
            cout << "Edge Detection Filter applied" << endl;
        }
        else if(choice == 12)
        {
            int x, y, width, height;
            cout << "Enter start x and y coordinates for the crop area: ";
            cin >> x >> y;
            cout << "Enter the width and height of the crop area: ";
            cin >> width >> height;
            applyCropFilter(image, x, y, width, height);
            saved = false;
            cout << "Crop Filter applied" << endl;
        }


        else if(choice == 13)
        {
            int radius;
            cout<<"Enter blur radius according to the level of blurrness you want:";
            cin>> radius;
            blurImage(image , radius);
            saved = false;
            cout<<"Blur Filter Applied"<< endl;
        }
        else if(choice == 14)
        {
            sunlight(image);
            saved = false;
            cout << "Sunlight Filter applied" << endl;
        }
        else if(choice == 15)
        {
            old_tv_filter(image);
            saved = false;
            cout << "Old TV Filter applied" << endl;
        }
        else if(choice == 16)
        {
            applyPurpleFilter(image);
            saved = false;
            cout<< " Purple Filter Applied "<< endl;
        }
        else if(choice == 17)
        {
            infraredImage(image);
            saved = false;
            cout<< " Infrared Filter Applied "<< endl;
        }
        else if(choice == 18)
        {
            int angle;
            cout << "Enter skew angle in degrees (1 to 89): ";
            cin >> angle;
            applySkewFilter(image, angle);
            saved = false;
            cout << "Skew Filter applied" << endl;
        }


        else if(choice == 19)
        {
            int brushSize;
            cout << "Enter brush size for Oil Painting Filter(1-10): ";
            cin >> brushSize;
            if (brushSize < 1 || brushSize > 10) {
                cout << "Invalid brush size. Please enter a value between 1 and 10." << endl;
                continue;
            }
            else{
                applyOilPaintingFilter(image, brushSize);
                saved = false;
                cout << "Oil Painting Filter applied" << endl;
            }
            
        }


        else if(choice == 20)
        {
            save_image(image, filename);
            saved = true;
        }

         
        else if(choice == 0)
        {
            if (!saved) {
                cout << "You have unsaved changes. Do you want to save before exiting? (y/n): ";
                char exitChoice;
                cin >> exitChoice;
                if (exitChoice == 'y' || exitChoice == 'Y') {
                    save_image(image, filename);
                }
            }
            cout << "Exiting the program." << endl;
            break;
        }
        
    }

}