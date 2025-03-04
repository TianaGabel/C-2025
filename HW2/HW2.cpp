#include<iostream>
#include "Image.h"

int main(int argc,char* argv[]){

    //Check for arg errors
    if (argc != 3){
        std::cerr<<"Only image file name and checksum file should be provided"<< std::endl;
        return -1;
    }

    Image image;
    int return_code = image.ReadImage(argv[1],argv[2]);
    return return_code;
}