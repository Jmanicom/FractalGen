#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "util/event_handler.hpp"
#include "util/config.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

// Define Settings
static float window_w = cf::window_size_f.x;
static float window_h = cf::window_size_f.y;


int main()
{
    // Enable 8x MSAA antialiasing
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Refer to config.hpp for changing window settings
    sf::RenderWindow window(sf::VideoMode({cf::window_size.x, cf::window_size.y}), "FractalGen", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(cf::max_framerate);
    window.setMouseCursorVisible(cf::cursor_visible);
    window.setKeyRepeatEnabled(cf::key_reapeat);

    // after your existing initialization
    sf::VertexArray screen(sf::PrimitiveType::TriangleStrip, 4);
    screen[0].position = { 0.f, 0.f };
    screen[1].position = { window_w, 0.f };
    screen[2].position = { 0.f, window_h };
    screen[3].position = { window_w, window_h };

    FractalState state;         // Init fractal state
    sf::Shader fractalShader;   // Init fractalShader

    // Check if shaders are supported
    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders are unsupported on this system!" << std::endl;
        return -1;
    }

    // Load default fragment shader
    if (!fractalShader.loadFromFile(state.shader_init, sf::Shader::Type::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }
    float theta = 0;

    while(window.isOpen()) {
        
        // Calls processEvents in event_handler.hpp under namespace ev
        ev::processEvents(window, state, fractalShader, window_w, window_h);

        // state.colorOffset += 0.00001f;  // Animate colors over time (Optional)


        // set uniforms before drawing
        fractalShader.setUniform("u_resolution", sf::Vector2f(window_w, window_h));
        fractalShader.setUniform("u_center", state.center);
        fractalShader.setUniform("u_zoom", state.zoom);
        fractalShader.setUniform("u_maxIter", cf::max_iter);

        if (state.active_shader == "shaders/julia.frag") {
            fractalShader.setUniform("u_juliaC", state.juliaconst);
            if (!state.isPaused) {
                theta += 0.01f;
                float speed = 0.0002f;

                state.juliaconst.x += speed *cos(theta*0.9f);
                state.juliaconst.y += speed *sin(theta*0.1f);

                state.juliaconst.x = std::clamp(state.juliaconst.x, -2.0f, 2.0f);
                state.juliaconst.y = std::clamp(state.juliaconst.y, -2.0f, 2.0f);
        }
    }   
        window.clear(sf::Color::Black);
        window.draw(screen, &fractalShader);
        window.display();

    }

    return 0;

}