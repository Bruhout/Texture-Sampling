#include <iostream>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

// This file will help you understand the scanline triangle drawing algorithm.
// This is only a half implementation.
// The remanining part of the algorithm is very simialar and is left as an exercise to the learner.

void FillTriangle(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , unsigned char* image , int image_width , int image_height);

int main(void)
{
    int image_width = 512;
    int image_height = 512;
    int channels = 3;
    int image_size = image_height * image_width * channels;

    unsigned char* outputImage = (unsigned char*)malloc(image_size);

    if (outputImage == NULL){
        std::cerr << "failed to allocate memory for the image";
    }

    // Initialize the image to a dark gray color
    for (int i=0 ; i<image_size ; i++)
    {
        *(outputImage + i) = 50;
    }

    int x1 = 256;
    int y1 = 150;

    int x2 = 150; 
    int y2 = 412;

    int x3 = 362;
    int y3 = 412;

    FillTriangle(x1 , y1 , x2 , y2 , x3 , y3 , outputImage , image_width , image_height);
    stbi_write_png("output_scanline.png" , image_width , image_height , channels , outputImage , image_width*channels);
}


void FillTriangle(int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , unsigned char* image , int image_width , int image_height)
{
    // vertices are given as integer coordinates

    // First, we sort the vertices based on y coordinate
    if (y1 > y2) {
        std::swap(y1 , y2);
        std::swap(x1 , x2);
    }

    if (y1 > y3) {
        std::swap(y1 , y3);
        std::swap(x1 , x3);
    }

    if (y2 > y3) {
        std::swap(y2 , y3);
        std::swap(x2 , x3);
    }

    // {x1 , y1} is on top , {x3 , y3} is on the bottom

    //y_diff is always positive
    int y_diff = y2 - y1;
    float slope_a = y_diff / (float)(x2 - x1);
    float slope_b = (y3 - y1) / (float)(x3 - x1);

    // The two slope values correspond to the slopes of the 2 sides of the triangle going down from {x1 , y1}

    for (int i=0 ; i<y_diff ; i++)
    {
        //these can be negative as well
        int x_offset_low = (int)(i / slope_a);
        int x_offset_high = (int)(i / slope_b);

        // make sure the low one is to the left of the high one
        if (x_offset_low > x_offset_high) {
            std::swap(x_offset_high , x_offset_low);
        }
        
        for (int j = x_offset_low + x1 ; j < x_offset_high + x1 ; j++)
        {
            // We color in the necessary pixel with a brighter gray color
            *(image + (((i + y1)*image_width) + j)*3) = 200;
            *(image + (((i + y1)*image_width) + j)*3 + 1) = 200;
            *(image + (((i + y1)*image_width) + j)*3 + 2) = 200;
        }
    }
}
