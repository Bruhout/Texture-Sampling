# Texture-Sampling
### This is an explanation of how an image texture can be applied upon a triangle in the rasterization rendering algorithm.

If you have ever played a video game, you have seen the use of textures. Its like wrapping and image on top of you geometry, to make it look likes it has more detail that it actually does. Instead of realistically simulating how objects are shaded and how objects interact with them and the tiny bumps and ridges that are otherwise required to make a convincing illusion of a "surface". Take this for example.

![wooden](https://github.com/Bruhout/Texture-Sampling/assets/147948392/cfabe6f6-dd46-4696-9555-cd9aa858fa8c)
Image 1: Texture examples

The sphere in this image is really just an infinitely smooth spherical object with an image "wood" wrapped over the sphere. This repository contains some code for you to understand this technique in the case of a triangle.

The only dependancy is stb_image lib, which you can get from [here](https://github.com/nothings/stb/tree/master). Simply go and download the `stb_image.h` and `stb_image_write.h`. Or you could get it from the `include` directory in this repo, but do pay the original pay a vist, because this makes our job a lot easier. Than trying to write `.bmp` or `.ppm` images ourselves, let alone all the compressed formats like `.jpg / .png`.

We will use this library to read the texture image and write out out output image, to see what we got.


This is the image we will be using as our texture. Its is a `.jpg` image of a crate with a `512 x 512` resolution. You can find this image in this repo with the name `container.jpg`.


![container](https://github.com/Bruhout/Texture-Sampling/assets/147948392/80101905-f1ec-4eb0-aeb8-5d95ab295699)
Image 2: Container texture

This is what we will be creating by the end of this, and triangle with the crate image on it, looking really out of place on the gray background.

![output](https://github.com/Bruhout/Texture-Sampling/assets/147948392/330eb043-2848-4afe-a42c-6d6fd8130bfe)
Image 3: A peek at the final result

## Texture coordinate mapping

![Ok_ManimCE_v0 18 1](https://github.com/Bruhout/Texture-Sampling/assets/147948392/269be59f-5e51-4fc4-8434-e772d8bdb4e2)
Image 4: The texture coordinates visualised

Let's start by deciding what part of the texture is going to be projected on top of our triangle. This process is called texture coordinate mapping.
1. Each vertex of the triangle is given in own texture coordinate.
2. `Texture coordinates` are used to refer to a point on the texture image.
3. They range from `(0 , 1)` for both the x and y axes. Texture coordinates are independant of the image size, which allows us to vary the resolution of the image arbitrarily.

In this case, the three texture coordinates for our three vertices are as follows
> (0 , 0.5)
> (0 , 1)
> (1 , 1)

You can see this visualised in `Image 4`. If you look back at the final result we will be getting, you will notice that the part of the texture that is covered by our triangle (the triangle formed from texture coordinates) will be projected on the triangle. Lets try changing the texture coordinates to see what happens.




