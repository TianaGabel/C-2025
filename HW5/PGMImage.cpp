#include <iostream>
#include<fstream>
#include<vector>
#include <cmath>
#include "PGMImage.h"
#include "PBMImage.h"
#include "AbstractImage.h"

PGMImage::PGMImage(){}

PGMImage::PGMImage(std::vector<std::vector<int>> im){
    this->image = im;
}

int PGMImage::ReadImage(char* file_name){
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        return -1;
    }
    char p;
    char two;

    image_filestream >> p;
    image_filestream >> two;
    image_filestream >> num_cols;
    image_filestream >> num_rows;
    image_filestream >> max_pixel_val;

    if (image_filestream.fail()){
        std::cerr << "Incorrect header formatting in "<< file_name << std::endl;
        return -1;
    }

    int row_count = 0;
    while(!image_filestream.eof() && (row_count < num_rows)){
        int col_count = 0;
        int row_total = 0;
        std::vector<int> row;
        while(col_count < num_cols){
            int val;
            image_filestream >> val;
            //std::cout << val << " [" << col_count << "] ";
            if (image_filestream.fail()){
                std::cerr << "Could not read value in " << std::endl;
                return -1;
            }
            if ((val > max_pixel_val) || (val < 0)){
                std::cerr << "Incorrect pixel value" << std::endl;
                return -1;
            }
            row.push_back(val);
            col_count++;
        }
        //std::cout << std::endl;

        image.push_back(row);
        row_count++;
    }

    if(!image_filestream.eof()){
        std::string extra;
        getline(image_filestream, extra);
        if(!extra.empty()){
            std::cerr <<"bad row count "<<file_name<<std::endl;
            return -1;
        }
    }

    image_filestream.close();
    return 0;
}

int PGMImage::OutputImage(char* out_file_name){
    std::ofstream imageFS;
    imageFS.open(out_file_name);

    if(!imageFS.is_open()){
        std::cerr <<"Unable to open file "<< out_file_name <<std::endl;
        return -1;
    }

    //First bit
    imageFS << "P2" << std::endl;
    imageFS << num_cols << " " << num_rows << " " << max_pixel_val;
    imageFS << std::endl;

    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            imageFS << image[i][j] << " ";
        }
        imageFS <<std::endl;
    }

    imageFS.close();
    return 0;
}

int PGMImage::NormalizeImage(){

    int max = image[0][0];
    int min = image[0][0];
    //Find least and maximum
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            if(image[i][j] > max) max = image[i][j];
            if(image[i][j] < min) min = image[i][j];
        }
    }
    //std::cout << "BOO" << max << "+" << min << std::endl;

    if (min == max){
        //no edits need to be made
        return 0;
    }
    //Update image values
    int temp;
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            temp =  std::round((image[i][j]- min) * (255.0/(max-min)));
            std::cout << temp << " ";
            image[i][j] = temp;
        }
        std::cout << std::endl;
    }
    
    return 0;
}

PPMImage PGMImage::ConvertToPPM(){
    //G to C R,G,B all = I
    std::vector<std::vector<int>> temp_image;
    int temp;
    
    for(int i = 0; i <num_rows; i++){
        std::vector<int> row;
        for (int j = 0; j < num_cols; j++){
            temp = image[i][j];
            row.push_back(temp);
            row.push_back(temp);
            row.push_back(temp);
        }
        temp_image.push_back(row);
    }

    return PPMImage(temp_image);
}

PGMImage PGMImage::ConvertToPGM(){
    return *this;
}

PBMImage PGMImage::ConvertToPBM(){
    //G to B 1 if I > 127.5
    std::vector<std::vector<int>> temp_image;
    int threshold = 127.5;
    int temp;
    
    for(int i = 0; i <num_rows; i++){
        std::vector<int> row;
        for (int j = 0; j < num_cols; j++){
            int num = image[i][j];
            temp = (num > threshold) ? 1 : 0;
            row.push_back(temp);
        }
        temp_image.push_back(row);
    }

    
}