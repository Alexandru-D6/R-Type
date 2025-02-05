# R-Type

This is a small game developed for the subject [VJ](https://www.fib.upc.edu/en/studies/bachelors-degrees/bachelor-degree-informatics-engineering/curriculum/syllabus/VJ) using a custom 2D engine provided by the teachers. Initially, it included a demo that loaded somes textures and sprites to create a simple character capable of moving and perfoming some sprite animations with a basic AABB collision system.

The main goal of this project was to replicate the original arcade game [R-Type](https://en.wikipedia.org/wiki/R-Type). You can find all the implemented features and a more in-depth explanation in the [TXT](/info.txt) (written in catalan). Here's a quick summary:
	- 4 different types of enemies
	- Force device
	- Different attacks
	- A final boss fight

You can play it yourself using the [binary](/assets/Release/R-Type.exe)

> [!NOTE]
> For the UI and gameplay controls, use the arrow keys along with `X` or `Z`.

All the source code and the solution file is available in the [assets](/assets/) folder. You will need to have [VS community](https://visualstudio.microsoft.com/es/vs/) installed (any version should be compatible) along with the [Windows 10 sdk 10.0.19041.0](https://developer.microsoft.com/es-es/windows/downloads/sdk-archive/). 

Two features that we are particularly proud of:
 - Implementation of a spatial hashmap collision system with coarse and fine optimization for improved performance.
 - A Python script utilizing computing vision to automatically compute all the collision boxes and enemies position based on an image.

Developed by:
 - Álvaro Rodríguez Rubio
 - Alexandru Dumitru Maroz
