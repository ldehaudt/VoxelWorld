# Voxel Landscape Engine

Minecraft style voxel terrain engine made from scratch using OpenGL in C++.

This project is done in collaboration with Conan Wu (conanwu777) during our visit at [Unit Factory](https://unit.ua/en/) in Kiev, Ukraine.

## Showcase Video
[![Voxel Video](textures/5.png)](https://www.youtube.com/watch?v=1Bxgr2ItPq4 "Voxel Landscape Engine")

## Features

* Snow, rock, grass and sand block type
* Transparent water
* Trees
* Caves and overhangs
* Different player modes
* Day-Night shift
* Runs at >~ 50 FPS in full screen mode on iMac
* Virtually infinite map (larger than what one can possible visit in days, then it might start to repeat after that)
* Rendering over 160 blocks at any direction at any given time, which make 26214400 (320 * 320 * 256) possiblly visiable blocks in view

## Screenshots

![alt text](textures/1.jpg)

![alt text](textures/2.jpg)

![alt text](textures/3.jpg)

![alt text](textures/4.jpg)

## Comiling and Running

Run `make` to compile. Needed libraries will be downloaded and an executable will be created.

Run with:
```
./Vox [-r | seed(integer)]
```
Where the terrain will be generated deterministically based on the seed given.
`-r` option will use random seed (based on current time)

## Runtime Controls

`Mouse movement` Controls the angle/direction of the camera

`-WASD` Move camera (exact movement based on the mode below)

`-1` Glider mode (fly directions according to mouse angle)

`-2` Run mode (run on the ground with 'WASD' keys and mouse)

`-3` Classic minecraft flying mode (in addition to WASD, we have `Space` for up and `Shift` for down)

`-4` Snail mode (moves one grid per second on the ground, able to enter caves)

