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
bool crop_shrink_skew = 0 ; // Used and explained in Black White Filter
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
void Black_and_white_filter(){ // to select weather to save or not (not saving if its used in another function)


    if(!crop_shrink_skew){
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
    }

  /*  else{
        average=128;  // if cropped/shrinked/skewed the white background will ruin the average so we used 128
    }

*/




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
void Black_and_white_filter_for_detect(){ // to select weather to save or not (not saving if its used in another function)

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

void detect() {

    Black_and_white_filter(); // to work on two degree only instead of working on range of degrees
    Black_and_white_filter_for_detect();
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

int main ()
{
//loadImage();
//Black_and_white_filter();
//Black_and_white_filter_for_detect();
//Invert_filter();
//flipping_filter_horz();
//flipping_filter_vertical();
//merge();
//mirror_lowerhalf();
//mirror_upperhalf();
//mirror_righthalf();
//mirror_LeftHalf();
//rotate_270_degree();
//rotate_180_degree();
//rotate_90_degree();
//detect();
//lighten();
//darken();
//saveImage();

}