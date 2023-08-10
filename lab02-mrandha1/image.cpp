/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "image.h"

#include <iostream>
using namespace std;

// Note: see image.h for documentation on functions.

int pixelToIndex(int width, int x, int y) {
    int index=width*y*3+x*3;
    return index;
}
void noRed(int width, int height, int* ppm) {

// this loops makes us go through the pixels row wise and we are able to
// go through each of the pixels
    int index_current=0;
    for (int j=0;j<height;j++){

      for (int i=0;i<width;i++){
          index_current=(pixelToIndex(width,i,j));
          //we set the Red value of each pixel to 0 to remove red
          ppm[index_current]=0;
      }
    }

}

void noGreen(int width, int height, int* ppm) {

  // this loops makes us go through the pixels row wise and we are able to
  // go through each of the pixels
    int index_current=0;
    for (int j=0;j<height;j++){

      for (int i=0;i<width;i++){
          //we set the Green value of each pixel to 0 to remove Green
          index_current=(pixelToIndex(width,i,j))+1;
          ppm[index_current]=0;
      }
    }

}

void noBlue(int width, int height, int* ppm) {
  // this loops makes us go through the pixels row wise and we are able to
  // go through each of the pixels
    int index_current=0;
    for (int j=0;j<height;j++){
    //we set the Blue value of each pixel to 0 to remove Blue
      for (int i=0;i<width;i++){
          index_current=(pixelToIndex(width,i,j))+2;
          ppm[index_current]=0;
      }
    }

  }

void invert(int width, int height, int* ppm) {
  // this loops makes us go through the pixels row wise and we are able to
  // go through each of the pixels
    int index_current=0;

    for (int j=0;j<height;j++){

      for (int i=0;i<width;i++){
        //we invert the RGB values of each of the pixel by subtracing all of
        //RGB values from 255 and storing them. It inverts the colors.
          index_current=(pixelToIndex(width,i,j));
          ppm[index_current]=255-ppm[index_current];
          ppm[index_current+1]=255-ppm[index_current+1];
          ppm[index_current+2]=255-ppm[index_current+2];
      }
    }

}


void grayscale(int width, int height, int* ppm) {
    int index_current=0;
  // this loops makes us go through the pixels row wise and we are able to
  // go through each of the pixels

    for (int j=0;j<height;j++){

      for (int i=0;i<width;i++){
        //we take the average RGB value of each of the pixel and set that as for
        //the respective pixel's RGB values.
          index_current=(pixelToIndex(width,i,j));
          float average_color=((ppm[index_current]+ppm[index_current+1]+ppm[index_current+2]))/3;

          ppm[index_current]=average_color;
          ppm[index_current+1]=average_color;
          ppm[index_current+2]=average_color;
      }
    }

}


void flipHorizontally(int width, int height, int* ppm) {
    int n_pixels=width*height;

    int final_index_row=0;
    int index_current=0;
    int new_index=0;
    //we make a new dynamic array that helps us to not mess up our main data array.
    int* new_ppm= new int[3*n_pixels];

    // this loops makes us go through the pixels row wise and we are able to
    // go through each of the pixels


    for (int j=0;j<height;j++){
      //this is the index value for the red color of the last pixel in the row
      //of an image
      final_index_row=pixelToIndex(width,width-1,j);

      for (int i=0;i<width;i++){
          //we calculate the index of our pixel
          index_current=(pixelToIndex(width,i,j));
          //we find the new position of the pixel under consideration and
          //swap each of the RGB values into respective positions.
          new_index=final_index_row-index_current+j*width*3;
          new_ppm[new_index]=ppm[index_current];
          new_ppm[new_index+1]=ppm[index_current+1];
          new_ppm[new_index+2]=ppm[index_current+2];
      }
    }
    //we copy the new image into our ppm array
    for(int i=0; i<3*n_pixels; ++i){
        ppm[i] = new_ppm[i];
      }
    //we delete the array we created for record keeping
      delete[] new_ppm;
}





void flipVertically(int width, int height, int* ppm) {

    int n_pixels=width*height;
    int j=0;

    int final_index_col=0;
    int index_current=0;
    int new_index=0;
    //we make a new dynamic array that helps us to not mess up our main data array.
    int* new_ppm= new int[3*n_pixels];

    // this loops makes us go through the pixels column wise and we are able to
    // go through each of the pixels
    for (int i=0;i<width;i++){
        //this is the index value for the red color of the last pixel in the column
        //of an image
        final_index_col=pixelToIndex(width,i,height-1);
      for (int j=0;j<height;j++){
          //we calculate the index of our pixel
          index_current=(pixelToIndex(width,i,j));
          //we find the new position of the pixel under consideration and
          //swap each of the RGB values into respective positions.
          new_index=final_index_col-index_current+3*i;
          new_ppm[new_index]=ppm[index_current];
          new_ppm[new_index+1]=ppm[index_current+1];
          new_ppm[new_index+2]=ppm[index_current+2];
      }
    }
    //we copy the new image into our ppm array
    for(int i=0; i<3*n_pixels; ++i){
        ppm[i] = new_ppm[i];
      }
    //we delete the array we created for record keeping
      delete[] new_ppm;
}
