#ifndef IMAGE_H
#define IMAGE_H
#include<vector>

class Image {
    public:
        int GenerateCheckSums(char* file_name, char* row_wise, char* column_wise);
        std::vector<std::vector<int>> ReadImage(char* file_name);
};

#endif