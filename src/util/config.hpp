#pragma once

#include <SFML/Graphics.hpp>

namespace cf
{
// Default Settings to be used in Sim
<<<<<<< HEAD
=======

// Define float type for rendering
using FloatType = float;
>>>>>>> test

// Window Config
const std::string window_name = "FractalGen";
sf::Vector2u const window_size = {1920, 1080};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
sf::Vector2<FloatType> const center_init = {0.0, 0.0};

uint32_t const max_framerate = 144;
<<<<<<< HEAD
int const max_iter = 2500;
bool const cursor_visible = false;
bool const key_reapeat = false;

// Initial fractal settings (defaults)
const sf::Vector2f center_init = {0.0f, 0.0f};
const float zoom_init = 1.0f;


// Control Settings (to be implemented)
const float zoom_speed = 1.1f;
const float pan_speed = 0.1f;

// Initial Julia C value: Use values between [-2, 2]
const sf::Vector2f julia_c = {-0.835f, -0.2321f};
}
=======
int const max_iter = 1000;
bool const key_reapeat = false;
bool const cursor_visible = false;
bool const is_fullscreen = false;

// Control Settings
FloatType const zoom_init = static_cast<FloatType>(1.0);
FloatType const zoom_speed = static_cast<FloatType>(1.1);
FloatType const pan_speed = static_cast<FloatType>(0.1);
}

void createWindow(sf::RenderWindow& window, sf::ContextSettings& settings, bool is_fullscreen);
>>>>>>> test
