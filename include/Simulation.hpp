#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.hpp"

class Simulation
{
public:
	Simulation();
	void run();

private:
	sf::RenderWindow window;
	std::vector<Particle> particles;
	void handleInput();
	void update(float deltaTime);
	void render();
};

#endif
