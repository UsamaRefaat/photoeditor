/*------------------------------------------------------------------------------------------------------
                            FCAI – OOP Programming – 2023 - Assignment 1
                            Program Name: photoeditor.cpp
                            Last Modification Date:	15/10/2023
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
unsigned char image[SIZE][SIZE][RGB];
unsigned char second_image[SIZE][SIZE][RGB];
unsigned char blank_image[SIZE][SIZE][RGB];
//-----------------------------------------------------------------------------------------------------
void loadImage () {
    char imageFileName[100];
 
    // Get gray scale image file name
    cout << "Enter the name of the image you want to edit: \n";
    cin >> imageFileName;
 
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
 
 
void loadImageTwice () { // load the same image twice
    char imageFileName[100];
 
    cout << "Enter the source image file name:\n ";
    cin >> imageFileName;
    
 
    strcat (imageFileName, ".bmp"); // imagefilename+=".bmp"
    readRGBBMP(imageFileName, image);
    readRGBBMP(imageFileName, second_image);
}
 
 
void load_SecondImage () {
    char imageFileName[100];
 
    cout << "Enter the second source image file name: \n";
    cin >> imageFileName;
 
    strcat (imageFileName, ".bmp"); // imagefilename+=".bmp"
    readRGBBMP(imageFileName, second_image);
}
 
void load_blankimage (){
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            for (int k = 0; k < RGB; ++k) {
                blank_image[i][j][k]=255;
            }
 
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
 
    writeRGBBMP(imageFileName, image);
 
 
}
//----------------------------------------------------------------------------------------------------- 

void Black_and_white_filter(){ // 
 
 

    for(int i=0 ; i<256 ; i++){
        for(int j=0 ; j<256 ; j++){
            long long average = 0;
            for (int k = 0; k < RGB; ++k) {
                average+=image[i][j][k]; // calculate the average gray level in the image
            }
            average/=3 ;
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=average;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                if (image[i][j][k]>=128)
                    image[i][j][k]=255;
                else
                    image[i][j][k]=0;
            }
        }
    }
    
 
}
//-----------------------------------------------------------------------------------------------------
 
void Invert_filter() {
 
    // get the difference of each value from 255 to invert it to its corresponding value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=255-(image[i][j][k]);
            }
        }
    }
 
}
 
void flipping_filter_horz()
{
    // getting the row value fixed , and adjusting the value of the columns to shift pixels to the right and get horizontally flipped photo
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k],image[i][SIZE-1-j][k]);
 
            }
        }
    }
 
 
}
 
void flipping_filter_vertical()
{
    // getting the columns value fixed , and adjusting the value of the rows to shift pixels down and get vertically flipped photo
 
    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k],image[SIZE-1-i][j][k]);
 
            }
        }
    }
 
}
//-----------------------------------------------------------------------------------------------------
 
void merge() {
 
    load_SecondImage();
    // getting the average of pixel value of the two photos to get merged one of both
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=(image[i][j][k]+second_image[i][j][k])/2;
 
            }
        }
    }
 
 
}
 
//-----------------------------------------------------------------------------------------------------
 
void mirror_lowerhalf ()
{
    // getting the columns value fixed , and adjusting the value of the rows to shift pixels down but the inner loop iterating to (SIZE/2) to get the mirroring effect not flipping
 
 
    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=image[SIZE-1-i][j][k];
            }
        }
    }
 
}
 
void mirror_upperhalf ()
{
    // getting the columns value fixed , and adjusting the value of the rows to shift pixels down but the outer loop iterating from (SIZE/2) to the end in order to get the mirroring effect not flipping
 
    for (int i = SIZE/2; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=image[SIZE-1-i][j][k];
 
            }
        }
    }
 
}
 
void mirror_LeftHalf()
{
    // getting the rows value fixed , and adjusting the value of the columns to work horizontally and shift pixels left but iterating from (SIZE/2) to the end in order to to get the mirroring effect not flipping
 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = SIZE / 2; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j] [k] = image[i][SIZE - 1 - j][k];
 
            }
        }
    }
 
}
 
void mirror_righthalf ()
{
    // getting the rows value fixed , and adjusting the value of the columns to work horizontally and shift pixels right but iterating to (SIZE/2) in order to to get the mirroring effect not flipping
 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=image[i][SIZE-1-j][k];
 
            }
        }
    }
 
}
//-----------------------------------------------------------------------------------------------------
void rotate_180_degree()
{
// swapping pixel values with its corresponding pixel value on the other side
 
    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k], image[SIZE - 1 - i][SIZE - 1 - j][k]);
            }
 
        }
    }
 
}
 
void rotate_270_degree()
{
    // swapping each pixel value of row with column
 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i+1; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k],image[j][i][k]);
 
            }
        }
    }
    //reversing the Matrix to get the 270 rotation by getting the rows fixed and adjusting the columns values and iterating to 1/2 size of the columns
    for (int i = 0; i < SIZE; ++i ) {
        for (int j = 0; j < SIZE/2; ++j ) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k], image[i][SIZE-1-j][k]);
 
            }
        }
    }
 
}
 
void rotate_90_degree()
{
 
    // swapping each pixel value of row with column
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i+1; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k],image[j][i][k]);
            }
        }
    }
    //reversing the Matrix to get the 270 rotation by getting the columns fixed and adjusting the rows values and iterating to 1/2 the size of the rows
    for (int i = 0; i < SIZE/2; ++i ) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k], image[SIZE-1-i][j][k]);
 
            }
        }
    }
 
}
 
//-----------------------------------------------------------------------------------------------------
void lighten ()
{
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]+=((255-image[i][j][k])/2);
            }
        }
    }
}
void darken()
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]-=((image[i][j][k])/2);
 
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------------

 
void detect() {
 
    Black_and_white_filter(); // to work on two degree only instead of working on range of degrees
    load_blankimage() ;
 
// checking if the pixel value is diffrent from its neighbour pixels to mark it as an edge or not
    for(int i=1 ; i<255 ; i++){
        for(int j=1 ; j<255 ; j++){
            for (int k = 0; k < RGB; ++k) {
                if(image[i][j][k]==0){
                    if(image[i+1][j][k] || image[i][j+1][k] || image[i+1][j+1][k] || image[i-1][j][k] || image[i][j-1][k] || image[i-1][j-1][k]){
                        blank_image[i][j][k]=0;
                    }
                    else{blank_image[i][j][k]=255;}
                }
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
            for(int k = 0; k < RGB; ++k){    
                blank_image[i][j][k]=image[i][y][k];
                 // skiping bits for compression
            }
            if(j%2){y+=skip;}// skiping bits for compression
            else{y+=skip+1;}
        }
        y=0;
        current_side--;
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
        for(int row=current_side * tanrad; row<SIZE-rightside+current_side * tanrad && y<SIZE; row++){ // our start is equal to the upper side * tan the angle
            for(int k = 0; k < RGB; ++k){    
                blank_image[row][col][k]=image[y][col][k];
                 
            }
            
            if(row%2){y+=skip;}// skiping bits for compression
            else{y+=skip+1;}
        }
        y=0;
        current_side--;
    }

    swap(blank_image,image);
}

//-----------------------------------------------------------------------------------------------------

void enlarge(){
    cout<<"Please Choose which quarter to Enlarge \n";
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
            for(int k=0 ; k<RGB ; k++){
                blank_image[i][j][k]=image[x][y][k];
                
            }
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
    cout<<"Enter '2' for (1/2) , 3 for (1/3), 4 for (1/4) \n";
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
            for(int k=0 ; k<RGB ; k++){
                blank_image[i][j][k]=image[x][y][k];
            }
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
            for(int k=0 ; k<RGB ; k++){
                blank_image[i][j][k]=image[x][y][k];
            }
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
    for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
        for (int k = 0; k < RGB; k++) {
            int sum = 0;
            int count = 0;
            for (int x = -4; x <= 4; x++) {
                for (int y = -4; y <= 4; y++) { // getting the surrounding pixels
                    int x1 = i + x;
                    int y1 = j + y;
                    if (x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE) { // avoiding out-of-bounds
                        sum += image[x1][y1][k];
                        count++;
                    }
                }
            }
            blank_image[i][j][k] = sum / count; // The average of the surrounding pixels for the current color channel
        }
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
            for(int k=0 ; k<RGB ; k++){
                blank_image[i][j][k]=image[i][j][k];
            }
        }
    }
    swap(image,blank_image);
}
//-----------------------------------------------------------------------------------------------------




int main ()
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
                            using switch case method to organize the code
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
                break;
                //---------------------------------------------------------------------------------------

            case 'e':
                skewHorizontally();
                break;
                //---------------------------------------------------------------------------------------

            case 'f':
                skewVertically();
                break;
                //---------------------------------------------------------------------------------------
            case 's':
                saveImage();
                cout << "Thanks for using our Photoeditor ^_^\n";
                return 0;
                //---------------------------------------------------------------------------------------

            case '0':
                cout << "Thanks for using our Photoeditor ^_^\n";
                return 0;
        } 
    }
           /*---------------------------------------------------------------------------------------
                                              THE END
            ----------------------------------------------------------------------------------------*/
 
}
