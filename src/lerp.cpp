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
    int image_height = 1024;
    int image_width = 1024;
	int channels = 3;
    int image_size = image_height * image_width * channels;

    unsigned char* output_image = (unsigned char*)malloc(image_size);

    // initialize the image to a plain dark gray
    for (unsigned char* pix = output_image; pix != output_image + image_size ; pix+=channels)
    {
        *pix = 50;
        *(pix+1) = 50;
        *(pix+2) = 50;
    }

    Vec3D v1 = {0.5f , 0.25f , 0};
    Vec3D v2 = {0.9f , 0.75f , 0};
    Vec3D v3 = {0.1f , 0.75f , 0};

	std::cout << "Width: " << image_width << '\n';
	std::cout << "Height: " << image_height << '\n';
	std::cout << "Channels: " << channels << '\n';

    DrawTriangleLerped(v1 , v2 , v3 , output_image , image_width , image_height , channels);

    stbi_write_jpg("lerp_output.jpg" , image_width , image_height , channels , output_image , 100);
}
