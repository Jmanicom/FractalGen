# Fractal Generator

Explore various fractals through a real-time rendered and interactive environment. 
This project was started as a learning exercise in C++ and [SFML](https://www.sfml-dev.org/documentation/3.0.2/)/[OpenGL](https://www.opengl.org/Documentation/Specs.html), and thus has
some optimization/precision errors due to the naive approach of rendering the fractals. However, I am currently working on a better implementation. 

<p align="center">
  <img src="Media/Julia.gif" alt="Julia Set Render" width="1000" height="600"/>
</p>

# What are Fractals? - Synopsis

Fractals are a kind of shape containing detail at very small scales, derived from recusion. Two of the most popular fractals are known as the [MandelBrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set) and its counterpart the [Julia Set](https://en.wikipedia.org/wiki/Julia_set). These two fractals are very famous for their self similarity and cross similarity between one another.

### MandelBrot Set
In order to render the MandelBrot set, we use it's equation and a set of simple rules. The equation is quite simple: 

$$ z_{n+1} = z^2_n + c, z_0 = 0$$

Where the values of z and c lie in the complex number plane.

The rules are as followed:
- Start with z = 0 and select a value for c.
- Iteratre through the equation above multiple times.
  - If the value of z remains bounded for all n > 0, c is a member of the set and color its position black.
  - If the value of z diverges, color the position of c a different color based on how fast it diverges. 

Complete this series of calculations and coloring for every value c in the complex plane and you have the MandelBrot set fractal!

### Julia Set
The Julia Set is derived from the same equation as the Mandelbrot Set. However, its rules are slightly different, and thus we get a different shape.

$$ z_{n+1} = z^2_n + c$$

The rules are as followed:
- Select a fixed value for c, and select a value for z
- Iterate through the equation multiple times.
  - If the iterations remain bounded, color the initial z value black
  - If the iterations diverge, color the initial z value a different color based on how fast it diverges.

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

In order to
run the program, the SFML library must be downloaded to be able to link it at compile time. Please consult the SFML documentation link above