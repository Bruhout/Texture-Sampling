#ifndef VEC3D_HPP
#define VEC3D_HPP
#include <iostream>
#include <math.h>

class Vec3D
{
public:
    float x , y , z;

    Vec3D();

    Vec3D(float X , float Y , float Z); 

    Vec3D operator-(Vec3D vec2);

    Vec3D operator+(Vec3D vec2);

    Vec3D operator*(float scalar);

    Vec3D operator/(float scalar);

    float MagnitudeSq();

    float Magnitude();

    float DistanceFrom(Vec3D refPoint);

    Vec3D CrossProduct(Vec3D vec2);

    float DotProduct(Vec3D vec2);

    Vec3D GetUnitVec();

    Vec3D ProjectOnto(Vec3D ontoVec);

    void PrintVec();

    Vec3D Normalize(int width , int height);
};
#endif // VEC3D_HPP