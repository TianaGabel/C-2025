#ifndef ABSTRACTIMAGE_H
#define ABSTRACTIMAGE_H
#include<vector>
#include "PGMImage.h"
#include "PPMImage.h"
#include "PBMImage.h"

class AbstractImage{
    private:
        std::vector<std::vector<int>> image;
        int num_rows;
        int num_cols;
        int max_pixel_val;
    
    public:
        virtual int ReadImage(char* file_name);
        virtual int NormalizeImage();
        virtual int OutputImage(char* out_file_name);
        virtual PPMImage ConvertToPPM();
        virtual PGMImage ConvertToPGM();
        virtual PBMImage ConvertToPBM();
};

#endif