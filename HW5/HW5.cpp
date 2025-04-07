#include<iostream>
#include "ImageManager.h"

int main(int argc,char* argv[]){

    //Check for arg errors
    if (argc != 3){
        std::cerr<<"Image file name and output image name are required arguments"<< std::endl;
        return -1;
    }

    ImageManager image;

    int return_code = image.ReadImage(argv[1]);
    if (return_code != 0) return return_code;
    return_code = image.NormalizeImage();
    if (return_code != 0) return return_code;
    image.OutputImage(argv[2]);
    return return_code;

    //ppm P3 width height max_val rgb_pixels
    //pgm P2 width height max_val int_pixel
    //pbm P1 width height max_val 1 or 0

    //read in image, determine it's type by the 'P...'
    //normalize grayscale and color
    //determine output image type based on the file extension of outfile
    //convert image to output image type

    //C to G I = round((R+G+B)/3)
    //C to B 1 if (R+G+B) > 382.5

    //G to C R,G,B all = I
    //G to B 1 if I > 127.5

    //B to C  RGB all = 255*bit
    //B to G  I = 255*bit

    //Test for illegal file extension
    // illegal values
    // illegal formatting
    
}