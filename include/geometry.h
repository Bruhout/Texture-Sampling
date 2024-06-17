#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "vec3d.hpp"

//Given the vertices of a trangle and a point within normal image space, this function will write out the barycentric coordinates of the point with respect to that triangle
double GetTriArea(Vec3D v1 , Vec3D v2 , Vec3D v3);

bool GetBarycentricCoords(Vec3D v1 , Vec3D v2 , Vec3D v3 , Vec3D point , Vec3D* write);

void DrawTriangleTextured(
    Vec3D p1 , Vec3D p2 , Vec3D p3,
    Vec3D tp1 , Vec3D tp2 , Vec3D tp3, 
    unsigned char* output_image , int image_width , int image_height , int channels,
    unsigned char* texture_image , int texture_width, int texture_height
);

void DrawTriangleLerped(
		Vec3D p1 , Vec3D p2 , Vec3D p3 ,
		unsigned char* output_image , int image_width , int image_height , int channnels
);

#endif
