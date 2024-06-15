#include "../include/geometry.h"
#include "../include/vec3d.hpp"
#include <iostream>

double GetTriArea(Vec3D v1 , Vec3D v2 , Vec3D v3)
{
    Vec3D edge12 = v2 - v1;
    Vec3D edge23 = v3 - v2;

    return ((edge12 * -1) - (edge12 * -1).ProjectOnto(edge23)).Magnitude() * edge23.Magnitude();
}

bool GetBarycentricCoords(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D point , Vec3D* output_vec)
{
    double total_area = GetTriArea(v1 , v2 , v3);
    double c1 = GetTriArea(v2 , point , v3) / total_area;
    double c2 = GetTriArea(v3 , point , v1) / total_area;
    double c3 = GetTriArea(v1 , point , v2) / total_area;

    output_vec->x = c1;
    output_vec->y = c2;
    output_vec->z = c3;

    if (c1 + c2 + c3 > 0.995f && c1 + c2 + c3 < 1.005f) {
        return true;
    } else {
        return false;
    }
}

void DrawTriangle(
    Vec3D p1 , Vec3D p2 , Vec3D p3,
    Vec3D tp1 , Vec3D tp2 , Vec3D tp3, 
    unsigned char* output_image , int image_width , int image_height , int channels,
    unsigned char* texture_image , int texture_width, int texture_height
)
{
    // vertices are given as integer coordinates (pixel coordinates)
    // texture coords are given as floats in normal texture space [0 , 1]
    double image_pixel_height = 1/(double)image_height;
    double image_pixel_width = 1/(double)image_width;

    Vec3D current_b_coords;
    Vec3D current_texture_coords;
    unsigned int texel_x;
    unsigned int texel_y;
    for(int i=0 ; i<image_height ; i++)
    {
        for(int j=0 ; j<image_width ; j++)
        {
            if (GetBarycentricCoords(p1 , p2 , p3 , Vec3D(j/(double)image_width + image_pixel_width/2 , i/(double)image_height + image_pixel_height/2 , 0) , &current_b_coords))
            {
                current_texture_coords = (tp1*current_b_coords.x + tp2*current_b_coords.y + tp3*current_b_coords.z);
                texel_x = round(current_texture_coords.x * texture_width);
                texel_y = round(current_texture_coords.y * texture_height);

                *(output_image + (i*image_width+j)*channels + 0) = *(texture_image + (texel_y*image_width+texel_x)*channels + 0);
                *(output_image + (i*image_width+j)*channels + 1) = *(texture_image + (texel_y*image_width+texel_x)*channels + 1);
                *(output_image + (i*image_width+j)*channels + 2) = *(texture_image + (texel_y*image_width+texel_x)*channels + 2);
            }
        }
    }
}