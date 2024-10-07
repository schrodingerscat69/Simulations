#include "Physics.hpp"
#include <cmath>

void Physics::update(std::vector<Particle> &particles, float deltaTime)
{
	for (auto &particle : particles)
	{
		particle.update(deltaTime);
	}
}

void Physics::handleCollisions(std::vector<Particle> &particles)
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		for (size_t j = i +1; j < particles.size(); j++)
		{
			Particle &p1 = particles[i];
			Particle &p2 = particles[j];

			sf::Vector2f diff = p1.getPosition() - p2.getPosition();
			float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			float minDist = p1.getRadius() + p2.getRadius();

			if (distance < minDist)
			{
				// Implement collision response (simple elastic collisions)
				sf::Vector2f collisionNormal = diff / distance;
				sf::Vector2f relativeVelocity = p1.getVelocity() - p2.getVelocity();
				float velocityAlongNormal = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;

				if (velocityAlongNormal > 0) continue; //Separation, no collision

				float restitution = 1.0f; //Perfectly elastic collision
				float impulseMagnitude = -(1 + restitution) * velocityAlongNormal / (1 / p1.getMass() + 1 / p2.getMass());

				sf::Vector2f impulse = impulseMagnitude * collisionNormal;
				p1.applyForce(impulse / p1.getMass());
				p2.applyForce(-impulse / p2.getMass());
			}
		}
	}
}

void Physics::handleWallCollisions(std::vector<Particle> &particles, const sf::RenderWindow &window)
{
	for (auto &particle : particles)
	{
		sf::Vector2f pos = particle.getPosition();
		float radius = particle.getRadius();

		// Check for collisions with left and right walls
		if (pos.x - radius < 0)
		{
			particle.applyForce(sf::Vector2f(-3 * particle.getVelocity().x, 0));
			pos.x = radius; // Prevent sticking to wall
		}

		else if (pos.x + radius > window.getSize().x)
		{
			particle.applyForce(sf::Vector2f(-3 * particle.getVelocity().x, 0));
			pos.x = window.getSize().x - radius;
		}

		// CHack for collisions with the top and bottom walls
		if (pos.y - radius < 0)
		{
			particle.applyForce(sf::Vector2f(0, -3 *particle.getVelocity().y)); 
			pos.y = radius;
		}

		else if (pos.y + radius > window.getSize().y)
		{
			particle.applyForce(sf::Vector2f(0, -3 * particle.getVelocity().y));
			pos.y = window.getSize().y - radius;
		}

		// Set the corrected position after wall collision
		particle.setPosition(pos);
	}
}









