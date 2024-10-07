#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>
#include "Particle.hpp"

class Physics
{
public:
	static void update(std::vector<Particle> &particles, float deltaTime);
	static void handleCollisions(std::vector<Particle> &particles);
	static void handleWallCollisions(std::vector<Particle> &particles, const sf::RenderWindow &window);
};

#endif
