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

    //Loops are run way too many times
    //either openmpi to parallelize this or combine
    //decrease the amount of calls
    //vectors are heavier, potentially 1d or use arrays
    //is it possible to parallelize image reading?
    //don't recalculate size
    //throw some additional data into the initial reading loop?
    
}