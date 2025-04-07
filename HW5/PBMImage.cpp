#include <iostream>
#include<fstream>
#include<vector>
#include <cmath>
#include "PGMImage.h"
#include "PBMImage.h"
#include "AbstractImage.h"


PBMImage::PBMImage(){}

PBMImage::PBMImage(std::vector<std::vector<int>> im){
    this->num_cols = im.at(0).size();
    this->num_rows = im.size();
    this->max_pixel_val = 1;
    this->image = im;
}

int PBMImage::ReadImage(char* file_name){
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        return -1;
    }
    char p;
    char num;

    image_filestream >> p;
    image_filestream >> num;
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
            std::cout << val << " [" << col_count << "] ";
            if (image_filestream.fail()){
                std::cerr << "Could not read value in " << std::endl;
                return -1;
            }
            if (!(val == 0)&&!(val == 1)){
                std::cerr << "Incorrect pixel value" << std::endl;
                return -1;
            }
            row.push_back(val);
            col_count++;
        }

        image.push_back(row);
        row_count++;
    }

    // if(!image_filestream.eof()){
    //     std::string extra;
    //     getline(image_filestream, extra);
    //     if(!extra.empty()){
    //         std::cerr <<"bad row count "<<file_name<<std::endl;
    //         return -1;
    //     }
    // }

    image_filestream.close();
    return 0;
}

int PBMImage::OutputImage(char* out_file_name){
    std::ofstream imageFS;
    imageFS.open(out_file_name);

    if(!imageFS.is_open()){
        std::cerr <<"Unable to open file "<< out_file_name <<std::endl;
        return -1;
    }

    //First bit
    imageFS << "p1" << std::endl;
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

int PBMImage::NormalizeImage(){
    return 0;
}

std::vector<std::vector<int>> PBMImage::ConvertToPPM(){
    //B to C  RGB all = 255*bit
    std::vector<std::vector<int>> temp_image;
    int temp;
    
    for(int i = 0; i <num_rows; i++){
        std::vector<int> row;
        for (int j = 0; j < num_cols; j++){
            temp = image[i][j] * 255;
            row.push_back(temp);
            row.push_back(temp);
            row.push_back(temp);
        }
        temp_image.push_back(row);
    }

    return temp_image;
}

std::vector<std::vector<int>> PBMImage::ConvertToPGM(){
    //B to G  I = 255*bit
    std::vector<std::vector<int>> temp_image;
    int temp;
    
    for(int i = 0; i <num_rows; i++){
        std::vector<int> row;
        for (int j = 0; j < num_cols; j++){
            temp = image[i][j] * 255;
            row.push_back(temp);
        }
        temp_image.push_back(row);
    }

    return temp_image;
}

std::vector<std::vector<int>> PBMImage::ConvertToPBM(){
    return this->image;
}