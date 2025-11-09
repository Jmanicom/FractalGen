#include "event_handler.hpp"
#include "config.hpp"
#include <iostream>

namespace ev
{

void processEvents(sf::Window& window, FractalState& state, sf::Shader& fractalShader, float window_w, float window_h)      // Take in reference to window object from main.cpp
    {
        while (const std::optional event = window.pollEvent()) {

            float panAmount = cf::pan_speed * state.zoom;
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

                    sf::Vector2f mouseBeforeZoom = state.center + mouseNorm * state.zoom;
                    
                    if (mouseIn->delta > 0) {
                        state.zoom /= cf::zoom_speed;
                    } else {
                        state.zoom *= cf::zoom_speed;
                    }

                    sf::Vector2f mouseAfterZoom = state.center + mouseNorm * state.zoom;
                    state.center += mouseBeforeZoom - mouseAfterZoom;
                
                // Left Click to pan
                }   else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseClick->button == sf::Mouse::Button::Left) {
                        state.isDragging = true;
                        state.lastMousePos = sf::Mouse::getPosition(window);
                // Middle click to change mouse visibility
                }   if (mouseClick->button == sf::Mouse::Button::Middle) {
                        state.cursorVisible = !state.cursorVisible;
                        window.setMouseCursorVisible(state.cursorVisible);
                }
                
                // To tell when no longer panning
                }   else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonReleased>()) {
                    if (mouseClick->button == sf::Mouse::Button::Left) {
                        state.isDragging = false;
                    }
                
                    // To handle mouse panning
                }   else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
                    if (state.isDragging) {
                        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                        sf::Vector2i delta = state.lastMousePos - currentMousePos;

                        float aspect = window_w / window_h;
                        state.center.x += (delta.x / window_w) * 2.0f * state.zoom *aspect;
                        state.center.y -= (delta.y / window_h) * 2.0f * state.zoom;

                        state.lastMousePos = currentMousePos;
                    }
                
                // To handle keyboard input 
                }   else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Escape to close window
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                        break;
                // Reset view to default
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        state.reset(state.juliaconst);
                // Keyboard Panning
                }   if (keyPressed->scancode >= sf::Keyboard::Scancode::Num1 && keyPressed->scancode <= sf::Keyboard::Scancode::Num2) {
                        int idx = static_cast<int>(keyPressed->scancode) - static_cast<int>(sf::Keyboard::Scancode::Num1);
                        state.active_shader = state.all_fractals[idx];
                        if (!fractalShader.loadFromFile(state.active_shader, sf::Shader::Type::Fragment)) {
                            std::cerr << "Failed to load shader!" << std::endl;
                        }                
                }
            }
        }
    }
}