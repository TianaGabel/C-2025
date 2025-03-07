#include<iostream>
#include "Image.h"

int main(int argc,char* argv[]){

    //Check for arg errors
    if (argc != 4){
        std::cerr<<"Image file name, row-wise checksum output file name, column-wise out file name are required arguments"<< std::endl;
        return -1;
    }    

    Image image;
    int return_code = image.GenerateCheckSums(argv[1],argv[2],argv[3]);
    return return_code;


    //takes in 3 args: file_name of an image, row-wise file anem, column-wise file name
    //row is like the checksum we did last time
    //
    
}