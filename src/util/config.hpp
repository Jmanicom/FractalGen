#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace cf
{
// Default Settings to be used in Sim

// Define float type for rendering
using FloatType = float;

// Window Config
const std::string window_name = "FractalGen";
const sf::Vector2u window_size = {1920, 1080};
const sf::Vector2<FloatType> window_size_f = static_cast<sf::Vector2<FloatType>>(window_size);
const sf::Vector2<FloatType> center_init = {0.0, 0.0};

const uint32_t  max_framerate = 144;
const int max_iter = 1000;
const int supersample = 2;
const bool key_reapeat = false;
const bool cursor_visible = false;
const bool is_fullscreen = false;

// Control Settings
const FloatType zoom_init = static_cast<FloatType>(1.5);
const FloatType zoom_speed = static_cast<FloatType>(1.1);
const FloatType pan_speed = static_cast<FloatType>(0.1);
}

inline void createWindow(sf::RenderWindow& window, sf::ContextSettings& settings, bool is_fullscreen) 
{
    window.close();
    sf::VideoMode winSize;
    if (is_fullscreen) {
        winSize = sf::VideoMode::getDesktopMode();
        window.create(winSize, cf::window_name, sf::State::Fullscreen, settings);
    } else {
        winSize = sf::VideoMode({cf::window_size.x, cf::window_size.y}, 32);
        window.create(winSize, cf::window_name, sf::Style::Default, sf::State::Windowed, settings);
    }
    window.setFramerateLimit(cf::max_framerate);
    window.setKeyRepeatEnabled(cf::key_reapeat);
    window.requestFocus();

    // Define OpenGL Context Settings
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 0;
}

inline void createTextures(sf::RenderTexture& renderTexture, sf::RectangleShape& rect, const int supersample)
{
    // Configure the render texture first
    if (!renderTexture.resize({cf::window_size.x * supersample, cf::window_size.y * supersample})) {
        std::cerr << "Failed to create render texture!" << std::endl;
    }
    renderTexture.setSmooth(true);

    // Configure the rect shape to draw to
    rect.setPosition({0.0f, 0.0f});
    rect.setSize(sf::Vector2f(cf::window_size_f.x * supersample, cf::window_size_f.y * supersample));
}