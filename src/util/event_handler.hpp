#pragma once

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <iostream>
#include <math.h>

struct Fractal 
{
    // Window-related Settings
    sf::Vector2<cf::FloatType> center = cf::center_init;
    cf::FloatType zoom = cf::zoom_init;
    sf::Vector2i lastMousePos;

    // Fractal Settings
    sf::Vector2f julia_c = {-0.7f, 0.27015f};
    sf::Vector2f mouseJuliaC = {0.0f, 0.0f};

    // Shader Settings
    bool isPaused = true;
    bool isDragging = false;
    bool isVisible = cf::cursor_visible;
    bool isFullscreen = cf::is_fullscreen;
    bool drawMan = true;
    bool drawJul = false;
    bool previewMode = false;
    int colType = 0;

    int fType = 0;

    void reset() {
        center = cf::center_init;
        zoom = cf::zoom_init;
    }
};

namespace ev                                                                                                                    // Create namespace for event handling
{                                                                                       
    inline void processEvents(sf::RenderWindow& window, Fractal& fractal, sf::Shader& shader, float window_w, float window_h)      // Take in reference to window object from main.cpp
    {
        while (const std::optional event = window.pollEvent()) {
            float panAmount = cf::pan_speed * fractal.zoom;
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

                    sf::Vector2f mouseBeforeZoom = fractal.center + mouseNorm * fractal.zoom;
                    
                    float zoomFactor = std::pow(cf::zoom_speed, (mouseIn->delta > 0 ? -1.0f : 1.0f));
                    fractal.zoom *= zoomFactor;

                    sf::Vector2f mouseAfterZoom = fractal.center + mouseNorm * fractal.zoom;
                    fractal.center += mouseBeforeZoom - mouseAfterZoom;
                
                // Left Click to pan
                }   else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseClick->button == sf::Mouse::Button::Left) {
                        if (fractal.previewMode) {
                            fractal.drawMan = false;
                            fractal.drawJul = true;
                            fractal.previewMode = false;
                            fractal.julia_c = fractal.mouseJuliaC;
                            fractal.center = sf::Vector2f(0.0f, 0.0f);
                            fractal.zoom = 1.5f;
                        } else {
                        fractal.isDragging = true;
                        fractal.lastMousePos = sf::Mouse::getPosition(window);
                        }
                // Middle click to change mouse visibility
                }   if (mouseClick->button == sf::Mouse::Button::Middle) {
                        fractal.isVisible = !fractal.isVisible;
                        window.setMouseCursorVisible(fractal.isVisible);
                }
                
                // To tell when no longer panning
                }   else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonReleased>()) {
                    if (mouseClick->button == sf::Mouse::Button::Left) {
                        fractal.isDragging = false;
                    }
                
                // To handle mouse panning
                }   else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
                        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
                        sf::Vector2f mouseNorm;
                        mouseNorm.x = (mousePixel.x / window_w) * 2.0f - 1.0f;
                        mouseNorm.y = -((mousePixel.y / window_h) * 2.0f - 1.0f);
                        mouseNorm.x *= window_w / window_h;

                        fractal.mouseJuliaC = fractal.center + mouseNorm * fractal.zoom;

                        if (fractal.isDragging) {
                            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                            sf::Vector2i delta = fractal.lastMousePos - currentMousePos;

                            float aspect = window_w / window_h;
                            fractal.center.x += (delta.x / window_w) * 2.0f * fractal.zoom *aspect;
                            fractal.center.y -= (delta.y / window_h) * 2.0f * fractal.zoom;

                            fractal.lastMousePos = currentMousePos;
                        }
                
                // To handle keyboard input 
                }   else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Escape to close window
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                        break;
                // Pause fractal Animation (Julia for now)
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                        fractal.isPaused = !fractal.isPaused;
                // Reset view to default
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        fractal.reset();
                // Enter Julia Select Mode
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::J) {
                        if (!fractal.drawJul) {
                            fractal.drawJul = true;
                            fractal.previewMode = true;
                        } else if (fractal.previewMode) {
                            fractal.drawMan = false;
                            fractal.previewMode = false;
                            fractal.julia_c = fractal.mouseJuliaC;
                            fractal.center = sf::Vector2f(0.0f, 0.0f);
                            fractal.zoom = 1.5f;
                        } else {
                            fractal.drawJul = false;
                            fractal.drawMan = true;
                            fractal.reset();
                        }
                // Change Color Palette
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::C) {
                        if (fractal.colType >= 1)
                            fractal.colType = 0;
                        else {
                            fractal.colType += 1;
                        }
                // Select Fractal to Render using Num Keys
                }   if (keyPressed->scancode >= sf::Keyboard::Scancode::Num1 && keyPressed->scancode <= sf::Keyboard::Scancode::Num4) {
                        int idx = static_cast<int>(keyPressed->scancode) - static_cast<int>(sf::Keyboard::Scancode::Num1);
                        fractal.fType = idx;             
                }
            }
        }
    }
}