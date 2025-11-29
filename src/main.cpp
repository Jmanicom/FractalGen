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
    createWindow(window, renderTexture, rect, settings, cf::is_fullscreen);

     // Check if shaders are supported - Throw error if they aren't
    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders aren't unsupported on this system!" << std::endl;
        return -1;
    }

    // Load default fragment shader - Throw error if can't fetch file
    if (!shader.loadFromFile("shaders/frag.glsl", sf::Shader::Type::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }

    // Run Render Object Config Commands + Create display sprite
    createTextures(renderTexture, rect, cf::window_size.x, cf::window_size.y);
    sf::Sprite displaySprite(renderTexture.getTexture());
    displaySprite.setScale(sf::Vector2f(1.0f / cf::supersample, 1.0f / cf::supersample));

    float theta = 0;
    while(window.isOpen()) {

        // Calls processEvents in event_handler.cpp to handle input
        ev::processEvents(window, renderTexture, settings, fractal, shader, cf::window_size_f.x, cf::window_size_f.y);

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
            theta += 0.001;
            if (theta > 6.28318f) theta -= 6.28318f; // Return to 0 after 2pi
            float scale = 0.15f;

            fractal.julia_c.x = fractal.julisStartC.x + scale * sin(3.0f * theta);
            fractal.julia_c.y = fractal.julisStartC.y + scale * sin(2.0f * theta);

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

        if (fractal.toggleFullscreen) {
            fractal.toggleFullscreen = false;
            fractal.isFullscreen = !fractal.isFullscreen;
            createWindow(window, renderTexture, rect, settings, fractal.isFullscreen);

        }
    }

    return 0;
}