#pragma once

#include <SFML/Graphics.hpp>
#include "util/config.hpp"
#include <iostream>

struct FractalState {

    sf::Vector2f center = cf::center_init;
    float zoom = cf::zoom_init;
    float colorOffset = 0.0f;

    void reset() {
        center = cf::center_init;
        zoom = cf::zoom_init;
    }

};

namespace ev {                                                       // Create namespace for event handling

    void processEvents(sf::Window& window, FractalState& state)      // Take in reference to window object from main.cpp
    {
        while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    break;
                } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                        break;
                }   if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        window.close(); // test for event handling
                        break;
                }
            }
        }
    }
}