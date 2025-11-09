#pragma once

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <iostream>
#include <string>

struct FractalState {

    sf::Vector2f center = cf::center_init;
    float zoom = cf::zoom_init;
    float colorOffset = 0.0f;
    std::string shader_init = "shaders/julia.frag";

    // Mouse state
    bool isDragging = false;
    bool cursorVisible = cf::cursor_visible;
    sf::Vector2i lastMousePos;

    
    void reset() {
        center = cf::center_init;
        zoom = cf::zoom_init;
    }

};

namespace ev                                                                                                                    // Create namespace for event handling
{                                                                                       
    void processEvents(sf::Window& window, FractalState& state, sf::Shader& fractalShader, float window_w, float window_h);     // Take in reference to window object from main.cpp

    //void setShader(std::string& shader)

}