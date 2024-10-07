#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(float x, float y, float radius, float mass, sf::Vector2f velocity);
    
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void applyForce(const sf::Vector2f &force);

    sf::Vector2f getPosition() const;
    float getRadius() const;
    sf::Vector2f getVelocity() const;
    float getMass() const;

    void setPosition(const sf::Vector2f &newPosition);

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    float mass;
    sf::CircleShape shape;
};

#endif
