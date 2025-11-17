#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"

struct Fractal {
    sf::Vector2f center{-0.5f, 0.0f};
    float zoom = 1.5f;
    sf::Vector2f julia_c{-0.7f, 0.27015f};
    
    bool isDragging = false;
    sf::Vector2i lastMousePos;
    bool isPaused = false;
    bool isVisible = true;  // Mouse cursor visibility
    
    bool drawMandelbrot = true;
    bool drawJulia = false;
    bool previewMode = false;
    sf::Vector2f mouseJuliaC{0.0f, 0.0f};
    
    int fractalType = 0;  // 0=Mandelbrot, 1=BurningShip, 2=Feather, 3=Tricorn
    
    std::string shader_init = "shaders/fractal.frag";
    std::string active_shader = "shaders/fractal.frag";
    
    void reset() {
        center = sf::Vector2f(-0.5f, 0.0f);
        zoom = 1.5f;
    }
    
    const char* getFractalName() {
        switch(fractalType) {
            case 0: return "Mandelbrot";
            case 1: return "Burning Ship";
            case 2: return "Feather";
            case 3: return "Tricorn";
            default: return "Unknown";
        }
    }
};

namespace ev {
    void processEvents(sf::RenderWindow& window, Fractal& fractal, sf::Shader& shader,
                      float window_w, float window_h);
}