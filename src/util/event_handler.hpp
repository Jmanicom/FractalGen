#pragma once

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <iostream>

struct FractalState {

    sf::Vector2f center = cf::center_init;
    float zoom = cf::zoom_init;
    float colorOffset = 0.0f;

    // Mouse state
    bool isDragging = false;
    bool cursorVisible = cf::cursor_visible;
    sf::Vector2i lastMousePos;

    
    void reset() {
        center = cf::center_init;
        zoom = cf::zoom_init;
    }

};

namespace ev {                                                                                       // Create namespace for event handling

    void processEvents(sf::Window& window, FractalState& state, float window_w, float window_h)      // Take in reference to window object from main.cpp
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
                        state.reset();
                // Keyboard Panning
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                        state.center.y += panAmount;
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                        state.center.x += panAmount;
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                        state.center.y -= panAmount;
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                        state.center.x -= panAmount;
                }
            }
        }
    }
}