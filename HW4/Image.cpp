#include <iostream>
#include<fstream>
#include<vector>
#include <cmath>
#include "Image.h"

int Image::OutputImage(char* out_file_name){
    std::ofstream imageFS;
    imageFS.open(out_file_name);

    if(!imageFS.is_open()){
        std::cerr <<"Unable to open file "<< out_file_name <<std::endl;
        return -1;
    }

    // char p;
    // char three;
    // int num_rows;
    // int num_cols;
    // int max_pixel_val;
    //First bit
    imageFS << "P3" << std::endl;
    imageFS << num_cols << " " << num_rows << " " << max_pixel_val;
    imageFS << std::endl;

    // migth as well do rows for ease of verifying
    // double check this
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols*3; j++){
            imageFS << image[i][j] << " ";
        }
        imageFS <<std::endl;
    }

    imageFS.close();
    return 0;
}

int Image::NormalizeImage(){

    int max = image[0][0];
    int min = image[0][0];
    //Find least and maximum
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols*3; j++){
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
        for (int j = 0; j < num_cols*3; j++){
            temp =  std::round((image[i][j]- min) * (255.0/(max-min)));
            std::cout << temp << " ";
            image[i][j] = temp;
        }
        std::cout << std::endl;
    }
    
    return 0;
}

int Image::OutputCheckSums(char* file_name, char* row_wise, char* column_wise){

    //std::vector<std::vector<int>> image = ReadImage(file_name);

    if (image.empty()){
        return -1;
    }

    num_rows = image.size();
    num_cols = image.at(0).size() / 3;
    // std::cout << "rows" << num_rows <<std::endl;
    // std::cout << "cols" << num_cols <<std::endl;

    //write to row-wise
    std::ofstream rowFS;
    rowFS.open(row_wise);

    if(!rowFS.is_open()){
        std::cerr <<"Unable to open file "<< row_wise <<std::endl;
        return -1;
    }

    for(int i = 0; i <num_rows; i++){
        int row_total = 0;
        for (int j = 0; j < num_cols*3; j++){
            row_total += image[i][j];
            std::cout << image[i][j] << num_rows <<std::endl;
        }
        rowFS << row_total << std::endl;
    }

    rowFS.close();

    //write to col-wise
    std::ofstream colFS;
    colFS.open(column_wise);

    if(!colFS.is_open()){
        std::cerr <<"Unable to open file "<< column_wise <<std::endl;
        return -1;
    }

    for (int col = 0; col < num_cols; col++){
        int col_total = 0;
        for(int i = 0; i <num_rows; i++){
            for (int j = 0; j < 3; j++){
                col_total += image[i][(col * 3)+j];
            }
        }
        colFS << col_total << std::endl;
    }   
    colFS.close();

    std::cout << "Success"<< std::endl;
    return 0;
}

int Image::ReadImage(char* file_name){
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        return -1;
    }
    char p;
    char three;

    image_filestream >> p;
    image_filestream >> three;
    image_filestream >> num_cols;
    image_filestream >> num_rows;
    image_filestream >> max_pixel_val;

    if (image_filestream.fail()){
        std::cerr << "Incorrect header formatting in "<< file_name << std::endl;
        return -1;
    }
    if ((p != 'p') ||(three != '3')){
        //May throw an error assignment was ambiguous
    }

    int row_count = 0;
    while(!image_filestream.eof() && (row_count < num_rows)){
        int col_count = 0;
        int row_total = 0;
        std::vector<int> row;
        while(col_count < num_cols*3){
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