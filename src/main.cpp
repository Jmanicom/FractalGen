#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <complex>
#include <math.h>

// Define Constants
static const int target_fps = 60;
static const int window_w_init = 1920;
static const int window_h_init = 1080;

// Define Settings
static int window_w = window_w_init;
static int window_h = window_h_init;


int main()
{
    sf::RenderWindow window(sf::VideoMode({window_w_init, window_h_init}), "Fractal", sf::Style::Default);
    window.setFramerateLimit(target_fps);
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);



    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                break;
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                    break;
                if (keyPressed->scancode == sf::Keyboard::Scancode::R)
                    window.close(); // test for event handling
            }
        }
        
        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}