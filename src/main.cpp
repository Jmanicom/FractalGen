#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "util/event_handler.hpp"
#include "util/config.hpp"

#include <iostream>
#include <complex>
#include <math.h>


// Define Settings
static float window_w = cf::window_size_f.x;
static float window_h = cf::window_size_f.y;


int main()
{
    // Refer to config.hpp for changing window settings
    sf::RenderWindow window(sf::VideoMode({cf::window_size.x, cf::window_size.y}), "Fractal", sf::Style::Default, sf::State::Fullscreen);
    window.setFramerateLimit(cf::max_framerate);
    window.setMouseCursorVisible(cf::cursor_visible);
    window.setKeyRepeatEnabled(cf::key_reapeat);

    // after your existing initialization
    sf::VertexArray screen(sf::PrimitiveType::TriangleStrip, 4);
    screen[0].position = { 0.f, 0.f };
    screen[1].position = { window_w, 0.f };
    screen[2].position = { 0.f, window_h };
    screen[3].position = { window_w, window_h };

    sf::Shader fractalShader;

    if (!fractalShader.loadFromFile("shaders/mandelbrot.frag", sf::Shader::Type::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }

    FractalState state;

    while(window.isOpen()) {
        
        // Calls processEvents in event_handler.hpp under namespace ev
        ev::processEvents(window, state, window_w, window_h);

        // state.colorOffset += 0.00001f;  // Animate colors over time (Optional)


        // set uniforms before drawing
        fractalShader.setUniform("u_resolution", sf::Vector2f(window_w, window_h));
        fractalShader.setUniform("u_center", state.center);
        fractalShader.setUniform("u_zoom", state.zoom);
        fractalShader.setUniform("u_maxIter", cf::max_iter);
        fractalShader.setUniform("u_colorOffset", state.colorOffset);

        window.clear(sf::Color::Black);
        window.draw(screen, &fractalShader);
        window.display();

    }

    return 0;

}