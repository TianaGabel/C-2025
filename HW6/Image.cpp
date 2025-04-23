#include <iostream>
#include<fstream>
#include<vector>
#include <math.h>
#include <cctype>
#include "Image.h"

double Image::Correlation(char* file_name_A, char* file_name_B){
    std::vector<std::vector<int>> imageA = ReadImage(file_name_A);
    std::vector<std::vector<int>> imageB = ReadImage(file_name_B);
    if (imageA.empty() || imageB.empty()){
        std::cerr << "Failed to Read image";
        return -1;
    }

    int num_rowsA = imageA.size();
    int num_colsA = imageA.at(0).size();

    int num_rowsB = imageB.size();
    int num_colsB = imageB.at(0).size();

    if ((num_rowsA != num_rowsB)||(num_colsA != num_colsB)){
        std::cerr << "Incorrect row or column count";
        return -1;
    }

    double averageA = CalcAverage(imageA, num_rowsA, num_colsA);
    double averageB = CalcAverage(imageB, num_rowsA, num_colsA);
    // std::cout << averageA << std::endl;
    // std::cout << averageB << std::endl;

    double sumAB = CalcSummation(imageA, imageB, num_rowsA, num_colsA, averageA, averageB);
    double sumSquaredA = CalcSummationSquared(imageA, num_rowsA, num_colsA, averageA);
    double sumSquaredB = CalcSummationSquared(imageB, num_rowsB, num_colsB, averageB);
    // std::cout << sumAB << std::endl;
    // std::cout << sumSquaredA << std::endl;
    // std::cout << sumSquaredB << std::endl;
    if((sumSquaredA == 0)||(sumSquaredB == 0)){
        std::cerr << "Image must not be constant";
        return -1;
    }

    double correlation = (sumAB) / (sqrt(sumSquaredA) * sqrt(sumSquaredB));

    std::cout << correlation << std::endl;
    return 0;
}

double Image::CalcSummationSquared(std::vector<std::vector<int>>& image, int num_rows, int num_cols, double average){
    double total = 0 ;
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            total += pow((image[i][j]- average),2);
            // std::cout << total << " ";
        }
    }
    // std::cout << std::endl;
    return total;
}

double Image::CalcSummation(std::vector<std::vector<int>>& imageA,std::vector<std::vector<int>>& imageB, int num_rows, int num_cols, double avgA, double avgB){
    double total = 0 ;
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            total += (imageA[i][j]- avgA) * (imageB[i][j] - avgB);
        }
    }
    return total;
}

double Image::CalcAverage(std::vector<std::vector<int>>& image, int num_rows, int num_cols){
    double total = 0 ;
    for(int i = 0; i <num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            total += image[i][j];
        }
    }
    return ((total*1.0)/(double(num_cols*num_rows)));
}

std::vector<std::vector<int>> Image::ReadImage(char* file_name){
    // From hw3 but updated to work for pgm images
    std::ifstream image_filestream = std::ifstream(file_name);
    if(!image_filestream.is_open()){
        std::cerr <<"Unable to open file "<<file_name<<std::endl;
        std::vector<std::vector<int>> empty;
        return empty;
    }
    char p;
    char two;
    int num_rows;
    int num_cols;
    int max_pixel_val;

    image_filestream >> p;
    image_filestream >> two;
    image_filestream >> num_cols;
    image_filestream >> num_rows;
    image_filestream >> max_pixel_val;

    if (image_filestream.fail()){
        std::cerr << "Incorrect header formatting in "<< file_name << std::endl;
        std::vector<std::vector<int>> empty;
        return empty;
    }
    if ((two != '2')){
        //May throw an error assignment TODO
    }

    int row_count = 0;
    std::vector<std::vector<int>> image;
    while(!image_filestream.eof() && (row_count < num_rows)){
        int col_count = 0;
        int row_total = 0;
        std::vector<int> row;
        while(col_count < num_cols){
            int val;
            image_filestream >> val;
            // std::cout << val << " [" << col_count << "] ";
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
        // std::cout << std::endl;

        image.push_back(row);
        row_count++;
    }

    if(!image_filestream.eof()){
        std::string extra;
        getline(image_filestream, extra);
        // reference to documentation on strtol()
        if(!isspace(extra.c_str()[0]) && !extra.empty()){
            std::cerr <<"bad row count \"" << extra << "\""<<file_name<<std::endl;
            std::vector<std::vector<int>> empty;
            return empty;
        }
    }

    image_filestream.close();
    return image;
}