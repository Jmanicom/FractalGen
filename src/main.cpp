#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "util/event_handler.hpp"
#include "util/config.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

int main() {

    // Initialize Window Objetct/Settings
    sf::RenderWindow window;
    sf::ContextSettings settings;

    // Initialize Render Objects
    sf::Shader shader;
    sf::RenderTexture renderTexture;
    sf::RectangleShape rect;

    // Initialize Fractal Object
    Fractal fractal;

    // Run Window Config Commands (Refer to config.hpp)
    createWindow(window, settings, cf::is_fullscreen);

     // Check if shaders are supported
    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders aren't unsupported on this system!" << std::endl;
        return -1;
    }

    // Load default fragment shader
    if (!shader.loadFromFile("shaders/frag.glsl", sf::Shader::Type::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }

    // Run Render Object Config Commands + Create display sprite
    createTextures(renderTexture, rect, cf::supersample);
    sf::Sprite displaySprite(renderTexture.getTexture());
    displaySprite.setScale(sf::Vector2f(1.0f / cf::supersample, 1.0f / cf::supersample));

    float theta = 0;
    while(window.isOpen()) {

        // Calls processEvents in event_handler.cpp to handle input
        ev::processEvents(window, fractal, shader, cf::window_size_f.x, cf::window_size_f.y);

        // Set Shader Uniforms
        shader.setUniform("u_resolution", sf::Vector2f(cf::window_size_f.x * cf::supersample, cf::window_size_f.y * cf::supersample));
        shader.setUniform("u_center", fractal.center);
        shader.setUniform("u_zoom", fractal.zoom);
        shader.setUniform("u_maxIter", cf::max_iter);
        shader.setUniform("u_fType", fractal.fType);
        shader.setUniform("u_drawMandelbrot", fractal.drawMan);
        shader.setUniform("u_drawJulia", fractal.drawJul);
        shader.setUniform("u_colType", fractal.colType);

        if (fractal.previewMode) {
            shader.setUniform("u_mousePos", fractal.mouseJuliaC);
        } else {
            shader.setUniform("u_mousePos", fractal.julia_c);
        }

        // Animation for Julia Spirals
        if (fractal.drawJul && !fractal.drawMan && !fractal.isPaused) {
            theta += 0.01f;
            float speed = 0.0002f;

            fractal.julia_c.x += speed * cos(theta * 0.9f);
            fractal.julia_c.y += speed * sin(theta * 0.1f);

            fractal.julia_c.x = std::clamp(fractal.julia_c.x, -2.0f, 2.0f);
            fractal.julia_c.y = std::clamp(fractal.julia_c.y, -2.0f, 2.0f);
        }
        
        // Display the rendering
        renderTexture.clear(sf::Color::Black);
        renderTexture.draw(rect, &shader);
        renderTexture.display();

        displaySprite.setTexture(renderTexture.getTexture(), true);

        window.clear(sf::Color::Black);
        window.draw(displaySprite);
        window.display();
    }

    return 0;
}