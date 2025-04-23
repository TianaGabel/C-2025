#include<iostream>
#include "Image.h"

int main(int argc,char* argv[]){

    //Check for arg errors
    if (argc != 3){
        std::cerr<<"First and Second image file names are required arguments"<< std::endl;
        return -1;
    }    

    Image image;
    int return_code = image.Correlation(argv[1],argv[2]);
    return return_code;

    //Read in 2 grayscale images
    //ensure header is correct for a pgm image (file extension doesn't matter)
    //Check if the widths and heights are the same else error -1
    //check that neither image is constant/"blank" (basically the denominator cannot be 0) else error

    //compute correlation between the two images
    //apparently called pearson's correlation
    //sum of each for A(pixel - average_pixel) * for B(pixel-average_pixel)
    //divided by sqrt((sum(pixel-average))^2) * //

    //print the value to std::cout

    
}