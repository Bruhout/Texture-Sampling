#include <iostream>
#include <stdlib.h>
#include "../include/vec3d.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include "../include/geometry.h"

int main(void)
{
    int textureWidth , textureHeight , channels;
    unsigned char* textureImage = stbi_load("container.jpg" , &textureWidth , &textureHeight , &channels , 0);
    int textureSize = textureWidth * textureHeight * channels;
    
    if (textureImage == NULL) {
        std::cout << "Texture not loaded\n";
    } else {
        std::cout << "T Width:" << textureWidth << "\nT Height:" << textureHeight << "\nT Channels:" << channels << '\n';  
    }
    
    int imageHeight = 512;
    int imageWidth = 512;
    int imageSize = imageHeight * imageWidth * channels;

    unsigned char* outputImage = (unsigned char*)malloc(imageSize);

    // initialize the image to a plain dark gray
    for (unsigned char* pix = outputImage; pix != outputImage + imageSize ; pix+=channels)
    {
        *pix = 50;
        *(pix+1) = 50;
        *(pix+2) = 50;
    }

    Vec3D v1 = {0.5f , 0.25f , 0};
    Vec3D v2 = {0.9f , 0.75f , 0};
    Vec3D v3 = {0.1f , 0.75f , 0};

    Vec3D tex_coord1 = {0.5 , 0.0 , 0};
    Vec3D tex_coord2 = {1.0 , 1.0 , 0};
    Vec3D tex_coord3 = {0.0 , 1.0 , 0};

    DrawTriangle(v1 , v2 , v3 , tex_coord1 , tex_coord2 , tex_coord3 ,
        outputImage , imageWidth , imageWidth , channels ,
        textureImage , textureWidth , textureHeight
    );

    stbi_write_jpg("output.jpg" , imageWidth , imageHeight , channels , outputImage , 100);
}
