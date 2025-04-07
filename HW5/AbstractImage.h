#ifndef ABSTRACTIMAGE_H
#define ABSTRACTIMAGE_H
#include<vector>
#include "PGMImage.h"
#include "PPMImage.h"
#include "PBMImage.h"

class PBMImage;
class PGMImage;
class PPMImage;

//Fixing the circular dependency error Whoops! "https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes"

//Style for Virtaul/Abstract class https://stackoverflow.com/questions/34557268/how-do-i-implement-virtual-methods-in-implementation-files
class AbstractImage{
    private:
        std::vector<std::vector<int>> image;
        int num_rows;
        int num_cols;
        int max_pixel_val;
    
    public:
        virtual int ReadImage(char* file_name) = 0;
        virtual int NormalizeImage() = 0;
        virtual int OutputImage(char* out_file_name) = 0;
        virtual std::vector<std::vector<int>> ConvertToPPM() = 0 ;
        virtual std::vector<std::vector<int>> ConvertToPGM() = 0;
        virtual std::vector<std::vector<int>> ConvertToPBM() = 0;
};

#endif