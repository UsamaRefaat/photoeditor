/*------------------------------------------------------------------------------------------------------
                            FCAI – OOP Programming – 2023 - Assignment 1
                            Program Name: photoeditor.cpp
                            Last Modification Date:	10/10/2023
 	                        Omar  Ahmed  Mohamed Saleh    20220220      omaarsaaleh1@gmail.com
 	                        Osama Refaat Sayed   Ali      20221015      osamarefaatsubm@gmail.com
            Purpose: Practice C++ Structured programming and gaining more experience in implementing large clean codes.
-------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <algorithm>
#include <map>
using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char second_image[SIZE][SIZE];
unsigned char blank_image[SIZE][SIZE];
bool crop_shrink_skew = 0 ; // Used and explained in Black White Filter
//-----------------------------------------------------------------------------------------------------
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the name of the image you want to edit: \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}


void loadImageTwice () { // load the same image twice
    char imageFileName[100];

    cout << "Enter the source image file name:\n ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp"); // imagefilename+=".bmp"
    readGSBMP(imageFileName, image);
    readGSBMP(imageFileName, second_image);
}


void load_SecondImage () {
    char imageFileName[100];

    cout << "Enter the second source image file name: \n";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp"); // imagefilename+=".bmp"
    readGSBMP(imageFileName, second_image);
}

void load_blankimage (){
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            blank_image[i][j]=255;
        }
    }
}


//-----------------------------------------------------------------------------------------------------
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName, image);


}

//-----------------------------------------------------------------------------------------------------
void Black_and_white_filter(){ // to select weather to save or not (not saving if its used in another function)

    long long average = 0;

    if(!crop_shrink_skew){
        for(int i=0 ; i<256 ; i++){
            for(int j=0 ; j<256 ; j++){
                average+=image[i][j]; // calculate the average gray level in the image
            }
        }
        average/=65536 ;
    }

    else{
        average=128;  // if cropped/shrinked/skewed the white background will ruin the average so we used 128
    }

    for(int i=0 ; i<256 ; i++){
        for(int j=0 ; j<256 ; j++){
            if(image[i][j]>=average){ // if the pixel value is greater or equal to the average set it to white
                image[i][j]=255;
            }
            else{
                image[i][j]=0; // if the pixel value is greater or equal to the average set it to black
            }
        }
    }


}
//-----------------------------------------------------------------------------------------------------

void Invert_filter() {

    // get the difference of each value from 255 to invert it to its corresponding value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=255-(image[i][j]);
        }
    }

}
//-----------------------------------------------------------------------------------------------------

void flipping_filter_horz()
{
    // getting the row value fixed , and adjusting the value of the columns to shift pixels to the right and get horizontally flipped photo
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            swap(image[i][j],image[i][SIZE-1-j]);
        }
    }


}

void flipping_filter_vertical()
{
    // getting the columns value fixed , and adjusting the value of the rows to shift pixels down and get vertically flipped photo

    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            swap(image[i][j],image[SIZE-1-i][j]);
        }
    }

}
//-----------------------------------------------------------------------------------------------------

void merge() {

    load_SecondImage();
    // getting the average of pixel value of the two photos to get merged one of both
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=(image[i][j]+second_image[i][j])/2;
        }
    }


}

//-----------------------------------------------------------------------------------------------------

void mirror_lowerhalf ()
{
    // getting the columns value fixed , and adjusting the value of the rows to shift pixels down but the inner loop iterating to (SIZE/2) to get the mirroring effect not flipping


    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=image[SIZE-1-i][j];
        }
    }

}

void mirror_upperhalf ()
{
    // getting the columns value fixed , and adjusting the value of the rows to shift pixels down but the outer loop iterating from (SIZE/2) to the end in order to get the mirroring effect not flipping

    for (int i = SIZE/2; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=image[SIZE-1-i][j];
        }
    }

}

void mirror_LeftHalf()
{
    // getting the rows value fixed , and adjusting the value of the columns to work horizontally and shift pixels left but iterating from (SIZE/2) to the end in order to to get the mirroring effect not flipping

    for (int i = 0; i < SIZE; ++i) {
        for (int j = SIZE / 2; j < SIZE; ++j) {
            image[i][j] = image[i][SIZE - 1 - j];
        }
    }

}

void mirror_righthalf ()
{
    // getting the rows value fixed , and adjusting the value of the columns to work horizontally and shift pixels right but iterating to (SIZE/2) in order to to get the mirroring effect not flipping

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            image[i][j]=image[i][SIZE-1-j];
        }
    }

}
//-----------------------------------------------------------------------------------------------------

void rotate_180_degree()
{
// swapping pixel values with its corresponding pixel value on the other side

    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            swap(image[i][j], image[SIZE - 1 - i][SIZE - 1 - j]);        }
    }

}

void rotate_270_degree()
{
    // swapping each pixel value of row with column

    for (int i = 0; i < SIZE; ++i) {
        for (int j = i+1; j < SIZE; ++j) {
            swap(image[i][j],image[j][i]);
        }
    }
    //reversing the Matrix to get the 270 rotation by getting the rows fixed and adjusting the columns values and iterating to 1/2 size of the columns
    for (int i = 0; i < SIZE; ++i ) {
        for (int j = 0; j < SIZE/2; ++j ) {
            swap(image[i][j], image[i][SIZE-1-j]);
        }
    }

}

void rotate_90_degree()
{

    // swapping each pixel value of row with column
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i+1; j < SIZE; ++j) {
            swap(image[i][j],image[j][i]);
        }
    }
    //reversing the Matrix to get the 270 rotation by getting the columns fixed and adjusting the rows values and iterating to 1/2 the size of the rows
    for (int i = 0; i < SIZE/2; ++i ) {
        for (int j = 0; j < SIZE; ++j) {
            swap(image[i][j], image[SIZE-1-i][j]);
        }
    }

}

//-----------------------------------------------------------------------------------------------------

void lighten ()
{
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            image[i][j]+=((255-image[i][j])/2);
        }
    }
}
void darken()
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]-=((image[i][j])/2);
        }
    }
}
//-----------------------------------------------------------------------------------------------------

void detect() {

    Black_and_white_filter() ; // to work on two degree only instead of working on range of degrees
    load_blankimage() ;

// checking if the pixel value is diffrent from its neighbour pixels to mark it as an edge or not
    for(int i=1 ; i<255 ; i++){
        for(int j=1 ; j<255 ; j++){
            if(image[i][j]==0){
                if(image[i+1][j] || image[i][j+1] || image[i+1][j+1] || image[i-1][j] || image[i][j-1] || image[i-1][j-1]){blank_image[i][j]=0;}
                else{blank_image[i][j]=255;}
            }
        }

    }
    swap(image,blank_image);
}
//-----------------------------------------------------------------------------------------------------

void skewHorizontally(){

    load_blankimage();
    cout << "Please enter an angle in degrees between 0 and 45\n";
    double angle ; cin >> angle ;
    if(angle<0 || angle>45){
        cout << "\nInvalid Input!\n\n";
        return ;
    }

    double tanrad = tan((angle)*M_PI/180.0) ;
    int current_side = SIZE ;
    int paralloSide =SIZE - SIZE * tanrad ; // the size of the horizontal side that the photo is compressed in
    int skip = (angle==45.0)? 1 : (1/(1-tanrad)) ; // compressing factor

    int y = 0;
    for(int i=0; i<SIZE ; i++){
        for(int j=current_side * tanrad; j<current_side * tanrad + paralloSide ; j++){ // our start is equal to the left side * tan the angle
            blank_image[i][j]=image[i][y];
            y+=skip; // skiping bits for compression
        }
        y=0;
        current_side--;
    }

    swap(image,blank_image);


}
//-----------------------------------------------------------------------------------------------------

void enlarge(){
    cout<<"Please Choose which quarter to Enlarge '1','2','3','4' \n";
    int n ; cin>>n;

    load_blankimage();
    int x,y,py ;

    if(n==1){x=0; y=0; py=0;}
    else if(n==2){x=0; y=128; py=128;} // Setting the start of the selected quarter
    else if(n==3){x=128; y=0; py=0;}
    else if(n==4){x=128; y=128; py=128;}
    else{
        cout << "\nInvalid Input!\n\n";
        return ;
    }

    for(int i=0 ; i<256 ; i++){
        for(int j=0 ; j<256 ; j++){
            blank_image[i][j]=image[x][y];
            if(!(j%2)){y++;} // expanding the image
        }
        if(!(i%2)){x++;}
        y=py; // resetting the y
    }

    swap(blank_image,image);

}
//-----------------------------------------------------------------------------------------------------

void shrink(){ //2 -> half, 4 -> quarter
    cout<<"Shrink to (1/2), (1/3) or (1/4)?\n";
    cout<<"Enter '2' for (1/2) , '3' for (1/3), '4' for (1/4) \n";
    int n; cin>>n;
    if(n!=4 && n!=2 && n!=3){
        cout << "\nInvalid Input!\n\n";
        return ;
    }


    load_blankimage();

    int size = 256/n ; // the size of the new image
    int x=0,y=0;
    for(int i=0 ; i<size ; i++){
        for(int j=0 ; j<size ; j++){
            blank_image[i][j]=image[x][y];
            y+=n;
        }
        y=0;
        x+=n;
    }

    swap(blank_image,image);

}
//-----------------------------------------------------------------------------------------------------

void fillq(int s,int e,int q){ // a function to fill a quarter with another quarter from another photo // not for the user
    int sizei = s+128 ;
    int sizej= e+128 ;

    int x,y, yp ;
    if(q==1){x=0;y=0;yp=0;}
    else if(q==2){x=0;y=128;yp=128;}
    else if(q==3){x=128;y=0;yp=0;}
    else if(q==4){x=128;y=128;yp=128;}

    for(int i=s ; i<sizei ; i++){
        for(int j=e ; j<sizej ; j++){
            blank_image[i][j]=image[x][y];
            y++;
        }
        x++; y=yp;
    }
}
//-----------------------------------------------------------------------------------------------------

void shuffle() {
    int a, b ,c, d;
    cout<<"Enter the order of quarters you would like in your new image"<<endl;
    cin>>a>>b>>c>>d;
    map<int,int> mp;
    mp[a]++ ; mp[b]++ ; mp[c]++ ; mp[d]++ ;
    for (int i=1 ; i<5 ; i++) {
        if(mp[i]!=1){
            cout << "\nInvalid Input!\n\n";
            return;
        }
    }

    load_blankimage();

    fillq(0,0,a); // fill each quarter with the required one
    fillq(0,128,b);
    fillq(128,0,c);
    fillq(128,128,d);

    swap(blank_image,image);

}
//-----------------------------------------------------------------------------------------------------

void blur(){

    load_blankimage();
    for(int i=0; i <SIZE; i++){
        for(int j=0; j <SIZE; j++){
            int sum = 0;
            int count = 0;
            for(int x = -2; x <= 2; x++){
                for(int y = -2; y <= 2; y++){ // getting the surrounding pixels
                    int x1 = i + x; int y1 = j + y;
                    if(x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE){ // avoiding out of bounds
                        sum += image[x1][y1];
                        count++;
                    }
                }
            }
            blank_image[i][j] = sum / count; // The average of the surrounding pixels
        }
    }
    swap(blank_image,image);
}
//-----------------------------------------------------------------------------------------------------

void crop(){
    int x ,  y , l, w;
    cout<<"Please enter x,y,l,w : \n";
    cin>>x>>y>>l>>w;

    if(w<=1 || w+y>256 || l<=1 || l+x>256 ){
        cout << "\nInvalid Input!\n\n";
        return ;
    }
    load_blankimage();

    int length_end = x+l ;
    int width_end = y+w ;

    for(int i=x; i<length_end ; i++){
        for(int j=y; j<width_end; j++){
            blank_image[i][j]=image[i][j];
        }
    }
    swap(image,blank_image);
}
//-----------------------------------------------------------------------------------------------------

void skewVertically(){

    load_blankimage();

    cout << "Please enter an angle in degrees between 0 and 45\n";
    double angle ; cin >> angle ;
    if(angle<0 || angle>45){
        cout << "\nInvalid Input!\n\n";
        return ;
    }

    double tanrad = tan((angle)*M_PI/180.0) ;
    int current_side = SIZE ;
    int y = 0;
    int rightside=SIZE * tanrad ;
    int skip= (angle==45.0)? 1 : (1/(1-tanrad)) ; // compressing factor

    for(int col=0; col<SIZE ; col++){
        for(int row=current_side * tanrad; row<SIZE-rightside+current_side * tanrad; row++){ // our start is equal to the upper side * tan the angle
            blank_image[row][col]=image[y][col];
            y+=skip;
        }
        y=0;
        current_side--;
    }

    swap(blank_image,image);
}

//-----------------------------------------------------------------------------------------------------


int main()
{
    cout<<"Welcome to bitmap photo editor\n";
    cout<<"We offer you a list of filters to choose from:\n";
    loadImage();
    while(true){

        cout<<"Choose a filter to apply or 's' to save or '0' to exit\n"
              "1-Black & White Filter\n"
              "2-Invert Filter\n"
              "3-Merge Filter \n"
              "4-Flip Image\n"
              "5-Darken and Lighten Image \n"
              "6-Rotate Image\n"
              "7-Detect Image Edges \n"
              "8-Enlarge Image\n"
              "9-Shrink Image\n"
              "a-Mirror 1/2 Image\n"
              "b-Shuffle Image\n"
              "c-Blur Image\n"
              "d-Crop Image\n"
              "e-Skew Image Horizontally  \n"
              "f-Skew Image Vertically  \n"
              "s-Save the image to a file\n"
              "0-Exit\n";
        //-----------------------------------------------------------------------------------------------------
        char choice ;
        cout<<"Please enter your choice :   \n";
        cin>>choice;
        /*-----------------------------------------------------------------------------------------------------
                                    using switch case control mechanism
        //----------------------------------------------------------------------------------------------------*/
        switch (choice) {
            case '1' :
                Black_and_white_filter();
                break;
                //---------------------------------------------------------------------------------------

            case '2' :
                Invert_filter();
                break;
                //---------------------------------------------------------------------------------------

            case '3' :
                merge();
                break;
                //---------------------------------------------------------------------------------------

            case '4' :
                cout<<"Flip (h)orizontally or (v)ertically?\n";
                cout<<"Enter 'h' for horizontal flip and 'v' for vertical flip\n";
                char flipping;
                cin>>flipping;
                if (flipping=='h')
                    flipping_filter_horz();
                else
                    flipping_filter_vertical();
                break;
                //---------------------------------------------------------------------------------------

            case '5' :
                cout<<"Do you want to (d)arken or (l)ighten?\n";
                cout<<"Enter 'd' for darkening and 'l' for lighting\n";
                char brightness;
                cin>>brightness;
                if (brightness=='d')
                    darken();
                else
                    lighten();
                break;
                //---------------------------------------------------------------------------------------

            case '6' :
                cout<<"Enter degree of Rotation you want (90), (180) or (270) degrees?\n";
                int degree;
                cin>>degree;
                if (degree==90)
                    rotate_90_degree();
                else if (degree==180)
                    rotate_180_degree();
                else
                    rotate_270_degree();
                break;
                //---------------------------------------------------------------------------------------

            case '7' :
                detect();
                break;
                //---------------------------------------------------------------------------------------

            case '8' :
                enlarge();
                break;
                //---------------------------------------------------------------------------------------

            case '9' :
                shrink();
                crop_shrink_skew=1;
                break;
                //---------------------------------------------------------------------------------------

            case 'a' :
                cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
                cout<<"Enter 'l' for left mirror , 'r' for right , 'u' for upper , 'd' for down\n";
                char mirror;
                cin>>mirror;
                if (mirror=='l')
                    mirror_LeftHalf();
                else if (mirror=='r')
                    mirror_righthalf();
                else if (mirror=='u')
                    mirror_upperhalf();
                else
                    mirror_lowerhalf();
                break;
                //---------------------------------------------------------------------------------------

            case 'b':
                shuffle();
                break;
                //---------------------------------------------------------------------------------------

            case 'c':
                blur();
                break ;
                //---------------------------------------------------------------------------------------

            case 'd':
                crop();
                crop_shrink_skew=1;
                break;
                //---------------------------------------------------------------------------------------

            case 'e':
                skewHorizontally();
                crop_shrink_skew=1;
                break;
                //---------------------------------------------------------------------------------------

            case 'f':
                skewVertically();
                crop_shrink_skew=1;
                break;
                //---------------------------------------------------------------------------------------
            case 's':
                saveImage();
                cout << "Thanks for using our Photo editor ^_^\n";
                return 0;
                //---------------------------------------------------------------------------------------

            case '0':
                cout << "Thanks for using our Photo editor ^_^\n";
                return 0;
        }
    }
    /*---------------------------------------------------------------------------------------
                                       THE END
     ----------------------------------------------------------------------------------------*/
}
