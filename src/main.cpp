#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "util/event_handler.hpp"
#include "util/config.hpp"

#include <iostream>
#include <complex>
#include <math.h>


// Define Settings
static int window_w = cf::window_size.x;
static int window_h = cf::window_size.y;


int main()
{
    // Refer to config.hpp for changing window settings
    sf::RenderWindow window(sf::VideoMode({cf::window_size.x, cf::window_size.y}), "Fractal", sf::Style::Default);
    window.setFramerateLimit(cf::max_framerate);
    window.setMouseCursorVisible(cf::cursor_visible);
    window.setKeyRepeatEnabled(cf::key_reapeat);

    // Test for rendering shapes
    sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);

    triangle[0].position = sf::Vector2f(10.f, 10.f);
    triangle[1].position = sf::Vector2f(100.f, 10.f);
    triangle[2].position = sf::Vector2f(100.f, 100.f);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;


    while(window.isOpen()) {
        
        // Calls processEvents in event_handler.hpp under namespace ev
        ev::processEvents(window);

        window.clear(sf::Color::Black);
        window.draw(triangle);
        window.display();

    }

    return 0;
}