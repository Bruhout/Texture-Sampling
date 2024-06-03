# Texture-Sampling
This is an explanation of how an image texture can be applied upon a triangle in the rasterization rendering algorithm.

If you have ever played a video game, you have seen the use of textures. Its like wrapping and image on top of you geometry, to make it look likes it has more detail that it actually does. Instead of realistically simulating how objects are shaded and how objects interact with them and the tiny bumps and ridges that are otherwise required to make a convincing illusion of a "surface". Take this for example.

![wooden](https://github.com/Bruhout/Texture-Sampling/assets/147948392/cfabe6f6-dd46-4696-9555-cd9aa858fa8c)

The sphere in this image is really just an infinitely smooth spherical object with an image "wood" wrapped over the sphere. This repository contains some code for you to understand this technique in the case of a triangle.

The only dependancy is stb_image lib, which you can get from [here](https://github.com/nothings/stb/tree/master). Simply go and download the `stb_image.h` and `stb_image_write.h`. Or you could get it from the `include` directory in this repo, but do pay the original pay a vist, because this makes our job a lot easier. Than trying to write `.bmp` or `.ppm` images ourselves, let alone all the compressed formats like `.jpg / .png`.

We will use this library to read the texture image and write out out output image, to see what we got.


This is the image we will be using as our texture. Its is a `.jpg` image of a crate with a `512 x 512` resolution. You can find this image in this repo with the name `container.jpg`.


![container](https://github.com/Bruhout/Texture-Sampling/assets/147948392/80101905-f1ec-4eb0-aeb8-5d95ab295699)

This is what we will be creating by the end of this, and triangle with the crate image on it, looking really out of place.

![output](https://github.com/Bruhout/Texture-Sampling/assets/147948392/d0ec080c-7480-4e51-be18-b4b22a20942e)

