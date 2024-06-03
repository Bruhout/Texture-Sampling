# Texture-Sampling
This is an explanation of how an image texture can be applied upon a triangle in the rasterization rendering algorithm.

If you have ever played a video game, you have seen the use of textures. Its like wrapping and image on top of you geometry, to make it look likes it has more detail that it actually does. Instead of realistically simulating how objects are shaded and how objects interact with them and the tiny bumps and ridges that are otherwise required to make a convincing illusion of a "surface". Take this for example.

![wooden](https://github.com/Bruhout/Texture-Sampling/assets/147948392/cfabe6f6-dd46-4696-9555-cd9aa858fa8c)

The sphere in this image is really just an infinitely smooth spherical object with an image "wood" wrapped over the sphere. This repository contains some code for you to understand this technique in the case of a triangle.

The only dependancy is stb_image lib, which you can get from [here](https://github.com/nothings/stb/tree/master). Simply go and download the `stb_image.h` and `stb_image_write.h`.
We will use this library to read the texture image and write out out output image, to see what we got.
