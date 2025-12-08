#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace cf
{
// Default Settings to be used in Sim

// Define float type for rendering
using FloatType = float;

// Window Config
const std::string window_name = "FractalGen";
inline sf::Vector2u window_size = {1920, 1080};
const sf::Vector2u minWindow_size = {800, 600};
inline sf::Vector2<FloatType> window_size_f = static_cast<sf::Vector2<FloatType>>(window_size);
const sf::Vector2<FloatType> center_init = {0.0, 0.0};

const uint32_t max_framerate = 144;
const int max_iter = 1200;
const unsigned int supersample = 2;
const bool key_reapeat = false;
const bool cursor_visible = false;
const bool is_fullscreen = false;

// Control Settings
const FloatType zoom_init = static_cast<FloatType>(1.5);
const FloatType zoom_speed = static_cast<FloatType>(1.1);
const FloatType pan_speed = static_cast<FloatType>(0.1);
}

struct Fractal 
{
    // Window-related Settings
    sf::Vector2<cf::FloatType> center = cf::center_init;
    cf::FloatType zoom = cf::zoom_init;
    sf::Vector2i lastMousePos;

    // Fractal Settings
    sf::Vector2f julia_c = {-0.7f, 0.27015f};
    sf::Vector2f mouseJuliaC = {0.0f, 0.0f};
    sf::Vector2f julisStartC;

    // Shader Settings
    bool isPaused = true;
    bool isDragging = false;
    bool isVisible = cf::cursor_visible;
    bool isFullscreen = cf::is_fullscreen;
    bool toggleFullscreen = false;
    bool takeScreenshot = false;
    bool drawMan = true;
    bool drawJul = false;
    bool previewMode = false;

    int fType = 0;

    void reset() {
        center = cf::center_init;
        zoom = cf::zoom_init;
    }
};

inline void resizeWindow(sf::RenderWindow& window, sf::RenderTexture& renderTexture, sf::ContextSettings& settings, unsigned int w, unsigned int h)
{
    cf::window_size.x = w;
    cf::window_size.y = h;
    if (!renderTexture.resize({w * cf::supersample, h * cf::supersample})) {
        std::cerr << "Failed to create render texture!" << std::endl;
    }
    window.setView(sf::View(sf::FloatRect({0.0f, 0.0f}, {(float)w, (float)h})));
}

inline void createTextures(sf::RenderTexture& renderTexture, sf::RectangleShape& rect, unsigned int w, unsigned int h)
{
    // Configure the render texture first
    if (!renderTexture.resize({w * cf::supersample, h * cf::supersample})) {
        std::cerr << "Failed to create render texture!" << std::endl;
    }
    renderTexture.setSmooth(true);

    // Configure the rect shape to draw to
    rect.setPosition({0.0f, 0.0f});
    rect.setSize(sf::Vector2f(w * cf::supersample, h * cf::supersample));
}

inline void takeScreenshot(sf::RenderWindow& window, sf::RenderTexture& renderTexture, Fractal& fractal)
{
    window.display();
    const time_t t = std::time(0);
    const tm* now = std::localtime(&t);
    char buffer[128];
    sf::Image image = renderTexture.getTexture().copyToImage();;

    std::strftime(buffer, sizeof(buffer), "pic_%m-%d-%y_%H-%M-%S.png", now);
    const sf::Vector2u windowSize = window.getSize();
    if(!image.saveToFile(buffer)) {
        std::cerr << "Failed to take screenshot" << std::endl;
    }
    fractal.takeScreenshot = false;
}

inline void createWindow(sf::RenderWindow& window, sf::RenderTexture& renderTexture, sf::RectangleShape& rect, sf::ContextSettings& settings, bool is_fullscreen) 
{
    // Create window and set its various settings
    window.close();
    sf::VideoMode winSize;
    if (is_fullscreen) {
        winSize = sf::VideoMode::getDesktopMode();
        window.create(winSize, cf::window_name, sf::State::Fullscreen, settings);
    } else {
        winSize = sf::VideoMode({cf::window_size.x, cf::window_size.y}, 32);
        window.create(winSize, cf::window_name, sf::Style::Default, sf::State::Windowed, settings);
    }
    resizeWindow(window, renderTexture, settings, winSize.size.x, winSize.size.y);
    createTextures(renderTexture, rect, winSize.size.x, winSize.size.y);
    window.setFramerateLimit(cf::max_framerate);
    window.setKeyRepeatEnabled(cf::key_reapeat);
    window.requestFocus();

    // Set program icon
    sf::Image icon;
    if(icon.loadFromFile("../Media/Icon.png"))
        window.setIcon(icon.getSize(), icon.getPixelsPtr());
    else
        std::cerr << "Failed to load icon" << std::endl;
    

    // Define OpenGL Context Settings
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 0;
}