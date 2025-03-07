#include <iostream>
#include<fstream>
#include<vector>
#include "Image.h"

int Image::GenerateCheckSums(char* file_name, char* row_wise, char* column_wise){

    std::vector<std::vector<int>> image = ReadImage(file_name);

    if (image.empty()){
        return -1;
    }

    int num_rows = image.size();
    int num_cols = image.at(0).size() / 3;
    std::cout << "rows" << num_rows <<std::endl;
    std::cout << "cols" << num_cols <<std::endl;

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

std::vector<std::vector<int>> Image::ReadImage(char* file_name){
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        std::vector<std::vector<int>> empty;
        return empty;
    }
    char p;
    char three;
    int num_rows;
    int num_cols;
    int max_pixel_val;

    image_filestream >> p;
    image_filestream >> three;
    image_filestream >> num_cols;
    image_filestream >> num_rows;
    image_filestream >> max_pixel_val;

    if (image_filestream.fail()){
        std::cerr << "Incorrect header formatting in "<< file_name << std::endl;
        std::vector<std::vector<int>> empty;
        return empty;
    }
    if ((p != 'p') ||(three != '3')){
        //May throw an error assignment was ambiguous
    }

    int row_count = 0;
    std::vector<std::vector<int>> image;
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
                std::vector<std::vector<int>> empty;
                return empty;
            }
            if ((val > max_pixel_val) || (val < 0)){
                std::cerr << "Incorrect pixel value" << std::endl;
                std::vector<std::vector<int>> empty;
                return empty;
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
            std::vector<std::vector<int>> empty;
            return empty;
        }
    }

    image_filestream.close();
    return image;
}