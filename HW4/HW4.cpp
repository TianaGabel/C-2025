#include<iostream>
#include "Image.h"

int main(int argc,char* argv[]){

    //Check for arg errors
    if (argc != 3){
        std::cerr<<"Image file name and normalized output image name are required arguments"<< std::endl;
        return -1;
    }    

    Image image;

    int return_code = image.ReadImage(argv[1]);
    if (return_code != 0) return return_code;
    return_code = image.NormalizeImage();
    if (return_code != 0) return return_code;
    image.OutputImage(argv[2]);
    return return_code;

    //Takes in filename of PPM, file name to write image to (include extensions)
    //0 if it run corrently and -1 if it encounters and error
    //find the maximum and minimum values
    //Apply intensity normalization
    // round((curr_val - min) * (255/(max-min)))
    //rounded is ciel .05 or higher and floor less than .05
    //write the new values to the new .ppm
    
    
}