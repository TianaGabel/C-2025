#ifndef IMAGE_H
#define IMAGE_H
#include<vector>

class Image {
    public:
        int OutputCheckSums(char* file_name, char* row_wise, char* column_wise);
        int OutputImage(char* out_file_name);
        int ReadImage(char* file_name);
        int NormalizeImage();
        std::vector<std::vector<int>> GetImage();
        void SetImage(std::vector<std::vector<int>> image);
        
    private:
        std::vector<std::vector<int>> image;
        int num_rows;
        int num_cols;
        int max_pixel_val;
        //image attributes
};

#endif