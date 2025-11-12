# Fractal Generator

Explore various fractals through a real-time generated sandbox.

This project was started as a learning exercise in C++ and SFML/OpenGL. 
The main resource used in the production of this project comes from [SFML documentation](https://www.sfml-dev.org/documentation/3.0.2/)

<p align="center">
  <img src="Media/Julia.gif" alt="Julia Set Render" width="800" height="600"/>
</p>

# How to Use

This project was built using g++ and its ucrt64 compiler with SFML and openGL on its includepath. With that being said, the easiest way to compile it then would be to do the same and run this terminal command:

`g++ main.cpp util/event_handler.cpp -I util -I shaders -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -o main`

Controls
-------------
* Esc - Exit Window
* Left Mouse - Drag to pan view
* Middle Mouse - Toggle Cursor Visible
* Scroll Wheel - Zoom in and out
* R - Reset View
* 1 - Mandelbrot Set
* 2 - Julia Set
* C - Toggle Color (Not functional)
* F11 - Toggle Fullscreen (Not functional)
* S - Save Screenshot (Not functional)

(Not all features are functional, early working version)
