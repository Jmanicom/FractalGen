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