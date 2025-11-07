#pragma once

#include <SFML/Graphics.hpp>

namespace conf
{

// Window Config
sf::Vector2u const window_size = {1920, 1080};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);

uint32_t const max_framerate = 144;
int const max_iter = 200;
bool const cursor_visible = false;
bool const key_reapeat = false;
}