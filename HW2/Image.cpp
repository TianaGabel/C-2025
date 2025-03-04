#include <iostream>
#include<fstream>
#include<vector>
#include "Image.h"

int Image::ReadImage(char* file_name, char* checksum_name){
    //Read from image file
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        return -1;
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
        return -1;
    }
    if ((p != 'p') ||(three != '3')){
        //May throw an error assignment was ambiguous
    }

    std::cout << p << three << " " << num_rows << num_cols << max_pixel_val << std::endl;

    int row_count = 0;
    std::vector<int> image_rows;
    while(!image_filestream.eof()){
        int col_count = 0;
        int row_total = 0;
        while(col_count < num_cols*3){
            int val;
            image_filestream >> val;
            std::cout << val << " [" << col_count << "] ";
            if (image_filestream.fail()){
                std::cerr << "Could not read value in "<< file_name << std::endl;
                return -1;
            }
            if ((val > max_pixel_val) || (val < 0)){
                std::cerr << "Incorrect pixel value" << std::endl;
                return -1;
            }
            row_total += val;
            col_count++;
        }
        std::cout << std::endl;
        row_count++;
        image_rows.push_back(row_total);
    }
    if (row_count != num_rows){
        std::cerr << "Incorrect number of rows found" << std::endl;
        return -1;
    }

    //Read from checksum file
    std::ifstream checksum_filestream = std::ifstream(checksum_name);
    if(!checksum_filestream.is_open()){
        std::cerr <<"Unable to open file "<<checksum_name<<std::endl;
        return -1;
    }

    int current_row = 0;
    while(!checksum_filestream.eof()){
        int checksum;
        checksum_filestream >> checksum;
        std::cout << checksum <<std::endl;
        if (checksum_filestream.fail()){
            std::cerr << "Could not read value in "<< checksum_name<< std::endl;
            return -1;
        }
        if (!(checksum == image_rows.at(current_row))){
            std::cerr << "Incorrect check sum at " << current_row << ". Computed ";
            std::cerr << image_rows.at(current_row) << " actual " << checksum << std::endl;
            return -(current_row + 2);
        }
        current_row++;
    }
    if(current_row != int(image_rows.size())){
        std::cerr << "Checksum and Image file rowcounts do not match" << std::endl;
        return -1;
    }

    image_filestream.close();
    checksum_filestream.close();

    std::cout << "Success"<< std::endl;
    return 0;
}