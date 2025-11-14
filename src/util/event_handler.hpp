#pragma once

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <iostream>
#include <string>

struct Fractal 
{
    // Window-related Settings
    sf::Vector2<cf::FloatType> center = cf::center_init;
    cf::FloatType zoom = cf::zoom_init;
    sf::Vector2i lastMousePos;

    // Fractal Settings
    sf::Vector2f julia_init = {-0.835f, -0.2321f};
    sf::Vector2f julia_c = julia_init;

    // Shader Settings
    std::string shader_init = "shaders/mandelbrot.frag";
    std::string active_shader = shader_init;
    bool isPaused = true;
    bool isDragging = false;
    bool isVisible = cf::cursor_visible;
    bool isFullscreen = cf::is_fullscreen;

    // List of all fractals
    std::array<std::string, 2> all_fractals = {
        "shaders/mandelbrot.frag",
        "shaders/julia.frag"
    };

    void reset(sf::Vector2f& C) {
        center = cf::center_init;
        zoom = cf::zoom_init;
        if (active_shader == "shaders/julia.frag") {
            C = julia_init;
        }
    }
};

namespace ev                                                                                                                    // Create namespace for event handling
{                                                                                       
    void processEvents(sf::RenderWindow& window, Fractal& fractal, sf::Shader& shader, float window_w, float window_h);     // Take in reference to window object from main.cpp

    //void setShader(std::string& shader)

}