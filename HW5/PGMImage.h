#ifndef PGMIMAGE_H
#define PGMIMAGE_H
#include<vector>
#include "PPMImage.h"
#include "PBMImage.h"
#include "AbstractImage.h"

class PGMImage : public AbstractImage{
    private:
        std::vector<std::vector<int>> image;
        int num_rows;
        int num_cols;
        int max_pixel_val;
    
    public:
        PGMImage();
        PGMImage(std::vector<std::vector<int>> im);
        int ReadImage(char* file_name);
        int NormalizeImage();
        int OutputImage(char* out_file_name);
        PPMImage ConvertToPPM();
        PGMImage ConvertToPGM();
        PBMImage ConvertToPBM();
};

#endif