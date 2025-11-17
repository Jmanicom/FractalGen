#include "event_handler.hpp"
#include "config.hpp"
#include <iostream>
#include <cmath>

namespace ev {

void processEvents(sf::RenderWindow& window, Fractal& fractal, sf::Shader& shader,
                  float window_w, float window_h) {
    while (const std::optional event = window.pollEvent()) {
        float panAmount = cf::pan_speed * fractal.zoom;
        
        if (event->is<sf::Event::Closed>()) {
            window.close();
            break;
            
        // Mouse Wheel Scroll to Zoom
        } else if (const auto* mouseIn = event->getIf<sf::Event::MouseWheelScrolled>()) {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);

            sf::Vector2f mouseNorm;
            mouseNorm.x = (mousePixel.x / window_w) * 2.0f - 1.0f;
            mouseNorm.y = -((mousePixel.y / window_h) * 2.0f - 1.0f);
            mouseNorm.x *= window_w / window_h;

            sf::Vector2f mouseBeforeZoom = fractal.center + mouseNorm * fractal.zoom;
            
            float zoomFactor = std::pow(cf::zoom_speed, (mouseIn->delta > 0 ? -1.0f : 1.0f));
            fractal.zoom *= zoomFactor;

            sf::Vector2f mouseAfterZoom = fractal.center + mouseNorm * fractal.zoom;
            fractal.center += mouseBeforeZoom - mouseAfterZoom;
        
        // Mouse Click
        } else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
            // Left Click - dragging or lock Julia
            if (mouseClick->button == sf::Mouse::Button::Left) {
                if (fractal.previewMode) {
                    fractal.drawMandelbrot = false;
                    fractal.drawJulia = true;
                    fractal.previewMode = false;
                    fractal.julia_c = fractal.mouseJuliaC;
                    fractal.center = sf::Vector2f(0.0f, 0.0f);
                    fractal.zoom = 1.5f;
                    std::cout << "Locked Julia set at c = (" 
                             << fractal.julia_c.x << ", " << fractal.julia_c.y << ")" << std::endl;
                } else {
                    fractal.isDragging = true;
                    fractal.lastMousePos = sf::Mouse::getPosition(window);
                }
            }
            // Middle click to toggle mouse visibility
            if (mouseClick->button == sf::Mouse::Button::Middle) {
                fractal.isVisible = !fractal.isVisible;
                window.setMouseCursorVisible(fractal.isVisible);
            }
        
        // Mouse Released
        } else if (const auto* mouseRelease = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseRelease->button == sf::Mouse::Button::Left) {
                fractal.isDragging = false;
            }
        
        // Mouse Movement
        } else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
            // Update mouse position for Julia preview
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mouseNorm;
            mouseNorm.x = (mousePixel.x / window_w) * 2.0f - 1.0f;
            mouseNorm.y = -((mousePixel.y / window_h) * 2.0f - 1.0f);
            mouseNorm.x *= window_w / window_h;
            
            fractal.mouseJuliaC = fractal.center + mouseNorm * fractal.zoom;
            
            // Handle dragging
            if (fractal.isDragging) {
                sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                sf::Vector2i delta = fractal.lastMousePos - currentMousePos;

                float aspect = window_w / window_h;
                fractal.center.x += (delta.x / window_w) * 2.0f * fractal.zoom * aspect;
                fractal.center.y -= (delta.y / window_h) * 2.0f * fractal.zoom;

                fractal.lastMousePos = currentMousePos;
            }
        
        // Keyboard Input
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            // Escape to close window
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
                break;
            }
            
            // Number keys 1-4 to switch fractal types
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num1) {
                fractal.fractalType = 0;
                fractal.reset();
                std::cout << "Switched to Mandelbrot" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num2) {
                fractal.fractalType = 1;
                fractal.reset();
                std::cout << "Switched to Burning Ship" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num3) {
                fractal.fractalType = 2;
                fractal.reset();
                std::cout << "Switched to Feather" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num4) {
                fractal.fractalType = 3;
                fractal.reset();
                std::cout << "Switched to Tricorn" << std::endl;
            }
            
            // J key - Toggle Julia preview
            if (keyPressed->scancode == sf::Keyboard::Scancode::J) {
                if (!fractal.drawJulia) {
                    fractal.drawJulia = true;
                    fractal.previewMode = true;
                    std::cout << "Julia Preview ON for " << fractal.getFractalName() << std::endl;
                } else if (fractal.previewMode) {
                    fractal.drawMandelbrot = false;
                    fractal.previewMode = false;
                    fractal.julia_c = fractal.mouseJuliaC;
                    fractal.center = sf::Vector2f(0.0f, 0.0f);
                    fractal.zoom = 1.5f;
                    std::cout << "Locked Julia set of " << fractal.getFractalName() << std::endl;
                } else {
                    fractal.drawJulia = false;
                    fractal.drawMandelbrot = true;
                    fractal.reset();
                    std::cout << "Returned to " << fractal.getFractalName() << std::endl;
                }
            }
            
            // Space - Pause animation
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                fractal.isPaused = !fractal.isPaused;
                std::cout << (fractal.isPaused ? "Paused" : "Unpaused") << std::endl;
            }
            
            // R - Reset view
            if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                fractal.reset();
                std::cout << "View reset" << std::endl;
            }
            
            // WASD / Arrow key panning
            if (keyPressed->scancode == sf::Keyboard::Scancode::A || 
                keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                fractal.center.x -= panAmount;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::D || 
                keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                fractal.center.x += panAmount;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::W || 
                keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                fractal.center.y += panAmount;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::S || 
                keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                fractal.center.y -= panAmount;
            }
        }
    }
}

} // namespace ev