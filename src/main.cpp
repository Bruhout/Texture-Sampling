#include <iostream>
#include <stdlib.h>
#include "../include/vec3d.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"


bool GetBCoords(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D point , Vec3D* write);

void DrawTriangle(
    Vec3D p1 , Vec3D p2 , Vec3D p3,
    Vec3D tp1 , Vec3D tp2 , Vec3D tp3, 
    unsigned char* outputImage , int image_width , int image_height , int channels,
    unsigned char* textureImage , int texture_width, int texture_height
);

int main(void)
{
    int textureWidth , textureHeight , channels;
    unsigned char* textureImage = stbi_load("container.jpg" , &textureWidth , &textureHeight , &channels , 0);
    int textureSize = textureWidth * textureHeight * channels;
    
    // if (textureImage == NULL)
    // {
    //     std::cout << "Texture not loaded\n";
    // }
    // else
    // {
    //     std::cout << "T Width:" << textureWidth << "\nT Height:" << textureHeight << "\nT Channels:" << channels << '\n';  
    // }
    
    int imageHeight = 512;
    int imageWidth = 512;
    int imageSize = imageHeight * imageWidth * channels;

    unsigned char* outputImage = (unsigned char*)malloc(imageSize);

    for (unsigned char* pix = outputImage; pix != outputImage + imageSize ; pix+=channels)
    {
        *pix = 50;
        *(pix+1) = 50;
        *(pix+2) = 50;
    }

    Vec3D v1 = {(int)(0.5 * imageWidth) , (int)(0.25f * imageHeight) , 0};
    Vec3D v2 = {(int)(0.1f * imageWidth) , (int)(0.75f * imageHeight) , 0};
    Vec3D v3 = {(int)(0.9f * imageWidth) , (int)(0.75f * imageHeight) , 0};

    Vec3D tv1 = {0.5f , 0 , 0};
    Vec3D tv2 = {0 , 1.0f , 0};
    Vec3D tv3 = {1.0f , 1.0f , 0};

    DrawTriangle(v1 , v2 , v3 , tv1 , tv2 , tv3 , outputImage , imageWidth , imageWidth , channels , textureImage , textureWidth , textureHeight);

    stbi_write_png("output.png" , imageWidth , imageHeight , channels , outputImage , imageWidth*channels);
}

void DrawTriangle(
    Vec3D p1 , Vec3D p2 , Vec3D p3,
    Vec3D tp1 , Vec3D tp2 , Vec3D tp3, 
    unsigned char* outputImage , int image_width , int image_height , int channels,
    unsigned char* textureImage , int texture_width, int texture_height
)
{
    // vertices are given as floats in normal screen space [-1 , 1]
    // texture coords are given as floats in normal texture space [0 , 1]
    // First, we sort the vertices based on y coordinate
    if (p1.y > p2.y)
        std::swap(p1 , p2);

    if (p1.y > p3.y)
        std::swap(p1 , p3);

    if (p2.y > p3.y)
        std::swap(p2 , p3);

    p1.PrintVec();
    p2.PrintVec();
    p3.PrintVec();

    //y_diff is always positive
    //using the sign of slope value we can find the side of p1 the vertices are on
    int y_diff = p2.y - p1.y;
    float slope_2 = y_diff / (p2.x - p1.x);
    float slope_3 = y_diff / (p3.x - p1.x);

    for (int i=0 ; i<y_diff ; i++)
    {
        //these can be negative as well
        int x_offset_low = (int)(i / slope_2);
        int x_offset_high = (int)(i / slope_3);

        // make sure the low one is to the left of the high one
        if (x_offset_low > x_offset_high)
        {
            float temp = x_offset_high;
            x_offset_high = x_offset_low;
            x_offset_low = temp;
        }
        // for (int j=0 ; j < image_width ; j++)
        for (int j = x_offset_low + p1.x ; j < x_offset_high + p1.x ; j++)
        {
            //Current pixel coords in normal screen space
            Vec3D bCoords;
            GetBCoords(
                p1.Normalize(image_width , image_height),
                p2.Normalize(image_width , image_height),
                p3.Normalize(image_width , image_height),
                Vec3D(j / (float)image_width , (i+p1.y) / image_height , 0),
                &bCoords
            );

            int textelX = ((tp1.x * bCoords.x) + (tp2.x * bCoords.y) + (tp3.x * bCoords.z)) * texture_width;
            int textelY = ((tp1.y * bCoords.x) + (tp2.y * bCoords.y) + (tp3.y * bCoords.z)) * texture_height;

            *(outputImage + ((i + (int)p1.y)* image_width + j) * channels) = *(textureImage + (textelY*texture_width + textelX) * channels);
            *(outputImage + 1 + ((i + (int)p1.y) * image_width + j) * channels) = *(textureImage + 1 + (textelY*texture_width + textelX) * channels);
            *(outputImage + 2 + ((i + (int)p1.y) * image_width + j) * channels) = *(textureImage + 2 + (textelY*texture_width + textelX) * channels);
        }
    }
}

bool GetBCoords(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D point , Vec3D* write)
{
    Vec3D edge12 = v2 - v1;
    Vec3D edge23 = v3 - v2;
    Vec3D edge31 = v1 - v3;

    float triArea = 0.5f * (edge23 - edge23.ProjectOnto(edge12)).Magnitude() * edge12.Magnitude();


    Vec3D pointDisp = point - v1;
    float perp = (pointDisp - pointDisp.ProjectOnto(edge12)).Magnitude();
    float c3 = (0.5f * perp * edge12.Magnitude()) / triArea;

    pointDisp = point - v2;
    perp = (pointDisp - pointDisp.ProjectOnto(edge23)).Magnitude();
    float c1 = (0.5f * perp * edge23.Magnitude()) / triArea;

    pointDisp = point - v3;
    perp = (pointDisp - pointDisp.ProjectOnto(edge31)).Magnitude();
    float c2 = (0.5f * perp * edge31.Magnitude()) / triArea;

    write->x = c1;
    write->y = c2;
    write->z = c3;

    if (c1 + c2 + c3 == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}