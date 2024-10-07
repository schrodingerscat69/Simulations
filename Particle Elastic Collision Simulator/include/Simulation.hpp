#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.hpp"
#include "Physics.hpp"

class Simulation {
public:
    Simulation();
    void run();
    void update(float deltaTime);
    void render();
    void handleInput();

private:
    sf::RenderWindow window;
    std::vector<Particle> particles;
};

#endif
