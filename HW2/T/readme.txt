Expected = 0
b is base test, very simple example file given

Expected = -83
error line 81, is an incorrect checksum on line 81 (82 with traditional indexing)

Expected = 0
success 40x50 is a 40x50 image file with a correct checksum file
success formatting is a 40x10 image with lots of variety in spacing, newlines, etc

For -1 tests, I deleted or swapped data from the image header, pixel values, or changed file extensions.

./HW2 T/bimage.ppm T/bchecksums.txt
./HW2 T/errorline81image.ppm T/errorline81checksums.txt
./HW2 T/success40x50image.ppm T/success40x50checksums.txt
./HW2 T/successformattingimage.ppm T/successformattingchecksums.txt