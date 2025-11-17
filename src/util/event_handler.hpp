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

    int fType = 0;

    void reset() {
        center = cf::center_init;
        zoom = cf::zoom_init;
    }
};

namespace ev                                                                                                                    // Create namespace for event handling
{                                                                                       
    void processEvents(sf::RenderWindow& window, Fractal& fractal, sf::Shader& shader, float window_w, float window_h);     // Take in reference to window object from main.cpp

    //void setShader(std::string& shader)

}