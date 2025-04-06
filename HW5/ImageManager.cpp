#include <iostream>
#include<fstream>
#include<vector>
#include <cmath>
#include "PGMImage.h"
#include "PPMImage.h"
#include "PBMImage.h"
#include "AbstractImage.h"
#include "ImageManager.h"

int ImageManager::OutputImage(char* out_file_name){

    //TODO does case matter
    std::string ext(out_file_name);

    ext = ext.substr(3);

    if (ext == "ppm")     image = image.ConvertToPPM();
    else if(ext == "pgm") image = image.ConvertToPGM();
    else if(ext == "pbm") image = image.ConvertToPBM();
    else {
        //TODO Error message about invalid file extension
        return -1;
    }

    return image.OutputImage(out_file_name);
}

int ImageManager::ReadImage(char* file_name){
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        return -1;
    }
    char p;
    char num;

    image_filestream >> p;
    image_filestream >> num;
    
    image_filestream.close();

    if (num == '3')     image = PPMImage();
    else if(num == '2') image = PGMImage();
    else if(num == '1') image = PBMImage();
    else {
        //TODO Error message about invalid file extension
        return -1;
    }

    return image.ReadImage(file_name);
}

int ImageManager::NormalizeImage(){
    return image.NormalizeImage();
}