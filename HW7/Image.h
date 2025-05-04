#ifndef IMAGE_H
#define IMAGE_H
#include<vector>

class Image {
    public:
        double CalcSummation(std::vector<std::vector<int>>& imageA,std::vector<std::vector<int>>& imageB, int num_rows, int num_cols, double avgA, double avgB);
        double CalcSummationSquared(std::vector<std::vector<int>>& image, int num_rows, int num_cols, double average);
        double CalcAverage(std::vector<std::vector<int>>& image, int num_rows, int num_cols);
        double Correlation(char* file_one_name, char* file_two_name);
        std::vector<std::vector<int>> ReadImage(char* file_name);
};

#endif