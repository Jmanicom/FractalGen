#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "util/event_handler.hpp"
#include "util/config.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

int main() {

    // Initialize Window Objetcs
    sf::RenderWindow window;
    sf::ContextSettings settings;
    sf::Shader shader;
    Fractal fractal;
    sf::RectangleShape rect;
    rect.setPosition({0.0, 0});
    rect.setSize(cf::window_size_f);

    // Run Window Config Commands (Refer to config.cpp)
    createWindow(window, settings, cf::is_fullscreen);

     // Check if shaders are supported
    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders are unsupported on this system!" << std::endl;
        return -1;
    }

    // Load default fragment shader
    if (!shader.loadFromFile(fractal.shader_init, sf::Shader::Type::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }
    
    float theta = 0;
    while(window.isOpen()) {

        // Calls processEvents in event_handler.cpp to handle input
        ev::processEvents(window, fractal, shader, cf::window_size_f.x, cf::window_size_f.y);

        // Set Shader Uniforms
        shader.setUniform("u_resolution", cf::window_size_f);
        shader.setUniform("u_center", fractal.center);
        shader.setUniform("u_zoom", fractal.zoom);
        shader.setUniform("u_maxIter", cf::max_iter);

        if (fractal.active_shader == "shaders/julia.frag") {
            shader.setUniform("u_juliaC", fractal.julia_c);
            if (!fractal.isPaused) {
                theta += 0.01f;
                float speed = 0.0002f;

                fractal.julia_c.x += speed *cos(theta*0.9f);
                fractal.julia_c.y += speed *sin(theta*0.1f);

                fractal.julia_c.x = std::clamp(fractal.julia_c.x, -2.0f, 2.0f);
                fractal.julia_c.y = std::clamp(fractal.julia_c.y, -2.0f, 2.0f);
            }
        }   

        if (fractal.active_shader == "shaders/julia.frag") {
            shader.setUniform("u_juliaC", fractal.julia_c);
            if (!fractal.isPaused) {
                theta += 0.01f;
                float speed = 0.0002f;

                fractal.julia_c.x += speed *cos(theta*0.9f);
                fractal.julia_c.y += speed *sin(theta*0.1f);

                fractal.julia_c.x = std::clamp(fractal.julia_c.x, -2.0f, 2.0f);
                fractal.julia_c.y = std::clamp(fractal.julia_c.y, -2.0f, 2.0f);
            }
        }   
        window.clear(sf::Color::Black);
        window.draw(rect, &shader);
        window.display();
    }

    return 0;
}