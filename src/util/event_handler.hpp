#pragma once

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <iostream>
#include <string>

struct FractalState {

    // Window-related settings
    sf::Vector2f center = cf::center_init;
    float zoom = cf::zoom_init;
    float colorOffset = 0.0f;

    // Shader settings
    bool isPaused = true;
    sf::Vector2f juliaconst = cf::julia_c;
    std::string shader_init = "shaders/mandelbrot.frag";
    std::string active_shader = shader_init;

    // Mouse state
    bool isDragging = false;
    bool cursorVisible = cf::cursor_visible;
    sf::Vector2i lastMousePos;

    // List of all fractals
    std::array<std::string, 2> all_fractals = {
        "shaders/mandelbrot.frag",
        "shaders/julia.frag"
    };

    void reset(sf::Vector2f& C) {
        center = cf::center_init;
        zoom = cf::zoom_init;
        if (active_shader == "shaders/julia.frag") {
            C = cf::julia_c;
        }
    }

};

namespace ev                                                                                                                    // Create namespace for event handling
{                                                                                       
    void processEvents(sf::Window& window, FractalState& state, sf::Shader& fractalShader, float window_w, float window_h);     // Take in reference to window object from main.cpp

    //void setShader(std::string& shader)

}