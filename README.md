# Dijkstra Shortest Path

An illustration of finding the shortest path between a pair of vertices.
Shortest path uses dijkstra algorithm.

---

## REQUIREMENT

- SDL2 library
- Currently project Makefile only supports GCC and Mingw

---

## BUILD

Configure `Makefile`
- Point _INCL\_PATHS_ to include dir in SDL2 lib
- Point _LIB\_PATHS_ to all static library paths for static loading

Make sure the following dynamic lib are present in `bin` dir at runtime:
- SDL2.dll
- SDL2\_image.dll
- SDL2\_ttf.dll
- dijkstra.exe
- libfreetype-6.dll
- libjpeg-9.dll
- libpng16-16.dll
- libtiff-5.dll
- libwebp-4.dll
- zlib1.dll

## DEMO

![demo1](./demo/demo1.gif)

with animation:
![demo2](./demo/demo2.gif)
