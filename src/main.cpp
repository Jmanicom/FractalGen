#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "util/event_handler.hpp"
#include "util/config.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

int main() {

    // Initialize Window Objects
    sf::RenderWindow window;
    sf::ContextSettings settings;
    sf::Shader shader;
    Fractal fractal;
    
    // Run Window Config Commands
    createWindow(window, settings, cf::is_fullscreen);

    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders are unsupported on this system!" << std::endl;
        return -1;
    }

    // Load shader
    if (!shader.loadFromFile("shaders/frag.glsl", sf::Shader::Type::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }
    
    // Supersampling setup (2x for quality)
    const unsigned int supersample = 2;
    sf::RenderTexture renderTexture;
    
    // SFML 3.x uses constructor instead of create()
    if (!renderTexture.resize({cf::window_size.x * supersample, cf::window_size.y * supersample})) {
        std::cerr << "Failed to create render texture!" << std::endl;
        return -1;
    }
    renderTexture.setSmooth(true);
    
    sf::RectangleShape rect;
    rect.setPosition({0.0f, 0.0f});
    rect.setSize(sf::Vector2f(cf::window_size_f.x * supersample, cf::window_size_f.y * supersample));
    
    // SFML 3.x requires texture in constructor
    sf::Sprite displaySprite(renderTexture.getTexture());
    
    // SFML 3.x setScale takes Vector2f
    displaySprite.setScale(sf::Vector2f(1.0f / supersample, 1.0f / supersample));
    
    float theta = 0.0f;
    
    std::cout << "=== Fractal Explorer ===" << std::endl;
    std::cout << "1-4 - Switch fractal type" << std::endl;
    std::cout << "  1: Mandelbrot" << std::endl;
    std::cout << "  2: Burning Ship" << std::endl;
    std::cout << "  3: Feather" << std::endl;
    std::cout << "  4: Tricorn" << std::endl;
    std::cout << "J - Toggle Julia preview / Lock / Return" << std::endl;
    std::cout << "Space - Pause animation" << std::endl;
    std::cout << "R - Reset view" << std::endl;
    std::cout << "Mouse wheel - Zoom" << std::endl;
    std::cout << "Drag - Pan" << std::endl;
    std::cout << "WASD/Arrows - Pan" << std::endl;
    std::cout << "Middle Click - Toggle cursor visibility" << std::endl;
    std::cout << "ESC - Exit" << std::endl;
    
    while(window.isOpen()) {

        ev::processEvents(window, fractal, shader, cf::window_size_f.x, cf::window_size_f.y);

        // Set Shader Uniforms
        shader.setUniform("u_resolution", 
            sf::Vector2f(cf::window_size_f.x * supersample, cf::window_size_f.y * supersample));
        shader.setUniform("u_center", fractal.center);
        shader.setUniform("u_zoom", fractal.zoom);
        shader.setUniform("u_maxIter", cf::max_iter);
        shader.setUniform("u_fType", fractal.fractalType);
        shader.setUniform("u_drawMandelbrot", fractal.drawMandelbrot);
        shader.setUniform("u_drawJulia", fractal.drawJulia);
        
        if (fractal.previewMode) {
            shader.setUniform("u_mousePos", fractal.mouseJuliaC);
        } else {
            shader.setUniform("u_mousePos", fractal.julia_c);
        }

        // Julia animation when locked (not in preview mode)
        if (fractal.drawJulia && !fractal.drawMandelbrot && !fractal.isPaused) {
            theta += 0.01f;
            float speed = 0.0002f;

            fractal.julia_c.x += speed * std::cos(theta * 0.9f);
            fractal.julia_c.y += speed * std::sin(theta * 0.1f);

            fractal.julia_c.x = std::clamp(fractal.julia_c.x, -2.0f, 2.0f);
            fractal.julia_c.y = std::clamp(fractal.julia_c.y, -2.0f, 2.0f);
        }
        
        // Render to high-resolution texture
        renderTexture.clear(sf::Color::Black);
        renderTexture.draw(rect, &shader);
        renderTexture.display();
        
        // Update sprite texture (in case it changed)
        displaySprite.setTexture(renderTexture.getTexture(), true);
        
        // Draw downscaled sprite to window
        window.clear(sf::Color::Black);
        window.draw(displaySprite);
        window.display();
    }

    return 0;
}