#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include<vector>
#include "PGMImage.h"
#include "PPMImage.h"
#include "PBMImage.h"
#include "AbstractImage.h"

class ImageManager {
    private:
        AbstractImage image;
    public:
        int ReadImage(char* file_name);
        int OutputImage(char* out_file_name);
        int NormalizeImage();
};

#endif