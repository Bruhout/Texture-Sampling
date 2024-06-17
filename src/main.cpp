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
	// LOAD IN THE TEXTURE
    int texture_width , texture_height , channels;
    unsigned char* texture_image = stbi_load("container.jpg" , &texture_width , &texture_height , &channels , 0);
    int texture_size = texture_width * texture_height * channels;
    
    if (texture_image == NULL) {
        std::cout << "Texture not loaded\n";
    } else {
        std::cout << "T Width:" << texture_width << "\nT Height:" << texture_height << "\nT Channels:" << channels << '\n';  
    }
    
	// ALLOCATE MEMORY FOR OUTPUT IMAGE
    int image_height = 512;
    int image_width = 512;
    int image_size = image_height * image_width * channels;

    unsigned char* output_image = (unsigned char*)malloc(image_size);

	if (output_image == NULL) {
		std::cout << "Error allocating memory for output image\n";
	} else {
        std::cout << "I Width:" << image_width << "\nI Height:" << image_height << "\nI Channels:" << channels << '\n';  
	}
)
    // INITIALIZE THE IMAGE TO A PLAIN DARK GRAY
    for (int i=0 ; i<image_size ; i++)
    {
        *(output_image + i) = 50;
    }

    Vec3D v1 = {0.5f , 0.25f , 0};
    Vec3D v2 = {0.9f , 0.75f , 0};
    Vec3D v3 = {0.1f , 0.75f , 0};

    Vec3D tex_coord1 = {0.5 , 0.0 , 0};
 	Vec3D tex_coord2 = {1.0 , 1.0 , 0};
    Vec3D tex_coord3 = {0.0 , 1.0 , 0};

    DrawTriangleTextured(v1 , v2 , v3 , tex_coord1 , tex_coord2 , tex_coord3 ,
        output_image , image_width , image_width , channels ,
        texture_image , texture_width , texture_height
    );

    stbi_write_jpg("output.jpg" , image_width , image_height , channels , output_image , 100);
	free(output_image);
	stbi_image_free(texture_image);
}
