#include "config.hpp"


void createWindow(sf::RenderWindow& window, sf::ContextSettings& settings, bool is_fullscreen)
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

    settings.depthBits = 32;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 0;
}