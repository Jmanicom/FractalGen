#pragma once

#include <SFML/Graphics.hpp>

namespace cf
{
// Default Settings to be used in Sim

// Define float type for rendering
using FloatType = float;

// Window Config
const std::string window_name = "FractalGen";
sf::Vector2u const window_size = {1920, 1080};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
sf::Vector2<FloatType> const center_init = {-0.5, 0.0};

uint32_t const max_framerate = 144;
int const max_iter = 1000;
bool const key_reapeat = false;
bool const cursor_visible = false;
bool const is_fullscreen = false;

// Control Settings
FloatType const zoom_init = static_cast<FloatType>(1.5);
FloatType const zoom_speed = static_cast<FloatType>(1.1);
FloatType const pan_speed = static_cast<FloatType>(0.1);
}


inline void createWindow(sf::RenderWindow& window, sf::ContextSettings& settings, bool is_fullscreen) 
{
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

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 0;
}
