#include "Physics.hpp"
#include <cmath>

void Physics::update(std::vector<Particle> &particles, float deltaTime) {
    for (auto &particle : particles) {
        particle.update(deltaTime);
    }
}

void Physics::handleCollisions(std::vector<Particle> &particles) {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Particle &p1 = particles[i];
            Particle &p2 = particles[j];
            
            sf::Vector2f diff = p1.getPosition() - p2.getPosition();
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            float minDist = p1.getRadius() + p2.getRadius();
            
            if (distance < minDist) {
                sf::Vector2f collisionNormal = diff / distance;
                sf::Vector2f relativeVelocity = p1.getVelocity() - p2.getVelocity();
                float velocityAlongNormal = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;

                if (velocityAlongNormal > 0) continue;

                float restitution = 1.0f;
                float impulseMagnitude = -(1 + restitution) * velocityAlongNormal / (1 / p1.getMass() + 1 / p2.getMass());
                
                sf::Vector2f impulse = impulseMagnitude * collisionNormal;
                p1.applyForce(impulse / p1.getMass());
                p2.applyForce(-impulse / p2.getMass());
            }
        }
    }
}

void Physics::handleWallCollisions(std::vector<Particle> &particles, const sf::RenderWindow &window) {
    for (auto &particle : particles) {
        sf::Vector2f pos = particle.getPosition();
		sf::Vector2f velocity = particle.getVelocity();
        float radius = particle.getRadius();

        if (pos.x - radius < 0) {
            pos.x = radius;
			velocity.x = -velocity.x;
        } 
        else if (pos.x + radius > window.getSize().x) {
            pos.x = window.getSize().x - radius;
			velocity.x = -velocity.x;
        }

        if (pos.y - radius < 0) {
            pos.y = radius;
			velocity.y = -velocity.y;
        } 
        else if (pos.y + radius > window.getSize().y) {
            pos.y = window.getSize().y - radius;
			velocity.y = -velocity.y;
        }

        particle.setPosition(pos);
		particle.applyForce(velocity - particle.getVelocity());
    }
}
