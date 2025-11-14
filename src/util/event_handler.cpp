#include "event_handler.hpp"
#include "config.hpp"
#include <iostream>
#include <math.h>

namespace ev
{

<<<<<<< HEAD
void processEvents(sf::Window& window, FractalState& state, sf::Shader& fractalShader, float window_w, float window_h)      // Take in reference to window object from main.cpp
    {
        while (const std::optional event = window.pollEvent()) {

            float panAmount = cf::pan_speed * state.zoom;
=======
void processEvents(sf::RenderWindow& window, Fractal& fractal, sf::Shader& shader, float window_w, float window_h)      // Take in reference to window object from main.cpp
    {
        while (const std::optional event = window.pollEvent()) {
            float panAmount = cf::pan_speed * fractal.zoom;
>>>>>>> test
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    break;
                // Mouse Wheel Scroll to Zoom
                }   else if (const auto* mouseIn = event->getIf<sf::Event::MouseWheelScrolled>()) {
                    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);

                    sf::Vector2f mouseNorm;
                    mouseNorm.x = (mousePixel.x / window_w) * 2.0f - 1.0f;
                    mouseNorm.y = -((mousePixel.y / window_h) * 2.0f - 1.0f);
                    mouseNorm.x *= window_w / window_h;

<<<<<<< HEAD
                    sf::Vector2f mouseBeforeZoom = state.center + mouseNorm * state.zoom;
                    
                    float zoomFactor = std::pow(cf::zoom_speed, (mouseIn->delta > 0 ? -1.0f : 1.0f));
                    state.zoom *= zoomFactor;

                    sf::Vector2f mouseAfterZoom = state.center + mouseNorm * state.zoom;
                    state.center += mouseBeforeZoom - mouseAfterZoom;
=======
                    sf::Vector2f mouseBeforeZoom = fractal.center + mouseNorm * fractal.zoom;
                    
                    float zoomFactor = std::pow(cf::zoom_speed, (mouseIn->delta > 0 ? -1.0f : 1.0f));
                    fractal.zoom *= zoomFactor;

                    sf::Vector2f mouseAfterZoom = fractal.center + mouseNorm * fractal.zoom;
                    fractal.center += mouseBeforeZoom - mouseAfterZoom;
>>>>>>> test
                
                // Left Click to pan
                }   else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseClick->button == sf::Mouse::Button::Left) {
<<<<<<< HEAD
                        state.isDragging = true;
                        state.lastMousePos = sf::Mouse::getPosition(window);
                // Middle click to change mouse visibility
                }   if (mouseClick->button == sf::Mouse::Button::Middle) {
                        state.cursorVisible = !state.cursorVisible;
                        window.setMouseCursorVisible(state.cursorVisible);
=======
                        fractal.isDragging = true;
                        fractal.lastMousePos = sf::Mouse::getPosition(window);
                // Middle click to change mouse visibility
                }   if (mouseClick->button == sf::Mouse::Button::Middle) {
                        fractal.isVisible = !fractal.isVisible;
                        window.setMouseCursorVisible(fractal.isVisible);
>>>>>>> test
                }
                
                // To tell when no longer panning
                }   else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonReleased>()) {
                    if (mouseClick->button == sf::Mouse::Button::Left) {
<<<<<<< HEAD
                        state.isDragging = false;
=======
                        fractal.isDragging = false;
>>>>>>> test
                    }
                
                    // To handle mouse panning
                }   else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
<<<<<<< HEAD
                    if (state.isDragging) {
                        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                        sf::Vector2i delta = state.lastMousePos - currentMousePos;

                        float aspect = window_w / window_h;
                        state.center.x += (delta.x / window_w) * 2.0f * state.zoom *aspect;
                        state.center.y -= (delta.y / window_h) * 2.0f * state.zoom;

                        state.lastMousePos = currentMousePos;
=======
                    if (fractal.isDragging) {
                        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                        sf::Vector2i delta = fractal.lastMousePos - currentMousePos;

                        float aspect = window_w / window_h;
                        fractal.center.x += (delta.x / window_w) * 2.0f * fractal.zoom *aspect;
                        fractal.center.y -= (delta.y / window_h) * 2.0f * fractal.zoom;

                        fractal.lastMousePos = currentMousePos;
>>>>>>> test
                    }
                
                // To handle keyboard input 
                }   else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Escape to close window
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                        break;
                // Reset view to default
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
<<<<<<< HEAD
                        state.isPaused = !state.isPaused;
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        state.reset(state.juliaconst);
                // Keyboard Panning
                }   if (keyPressed->scancode >= sf::Keyboard::Scancode::Num1 && keyPressed->scancode <= sf::Keyboard::Scancode::Num2) {
                        int idx = static_cast<int>(keyPressed->scancode) - static_cast<int>(sf::Keyboard::Scancode::Num1);
                        state.active_shader = state.all_fractals[idx];
                        if (!fractalShader.loadFromFile(state.active_shader, sf::Shader::Type::Fragment)) {
=======
                        fractal.isPaused = !fractal.isPaused;
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        fractal.reset(fractal.julia_c);
                // Keyboard Panning
                }   if (keyPressed->scancode >= sf::Keyboard::Scancode::Num1 && keyPressed->scancode <= sf::Keyboard::Scancode::Num2) {
                        int idx = static_cast<int>(keyPressed->scancode) - static_cast<int>(sf::Keyboard::Scancode::Num1);
                        fractal.active_shader = fractal.all_fractals[idx];
                        if (!shader.loadFromFile(fractal.active_shader, sf::Shader::Type::Fragment)) {
>>>>>>> test
                            std::cerr << "Failed to load shader!" << std::endl;
                        }                
                }
            }
        }
    }
}