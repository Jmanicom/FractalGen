#pragma once

#include <SFML/Graphics.hpp>

namespace cf
{
// Default Settings to be used in Sim

// Window Config
sf::Vector2u const window_size = {1920, 1080};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);

uint32_t const max_framerate = 144;
int const max_iter = 2500;
bool const cursor_visible = false;
bool const key_reapeat = false;

// Initial fractal settings (defaults)
const sf::Vector2f center_init = {0.0f, 0.0f};
const float zoom_init = 1.0f;


// Control Settings (to be implemented)
const float zoom_speed = 1.1f;
const float pan_speed = 0.1f;

const sf::Vector2f julia_c = {-0.8f, 0.156f};
}