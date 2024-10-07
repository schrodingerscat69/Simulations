#include "Particle.hpp"

Particle::Particle(float x, float y, float radius, float mass, sf::Vector2f velocity)
    : position(x, y), velocity(velocity), radius(radius), mass(mass), shape(radius) {
    shape.setPosition(position);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::Green);
}

void Particle::update(float deltaTime) {
    position += velocity * deltaTime;
    shape.setPosition(position);
}

void Particle::render(sf::RenderWindow &window) {
    window.draw(shape);
}

void Particle::applyForce(const sf::Vector2f &force) {
    velocity += force / mass;
}

sf::Vector2f Particle::getPosition() const {
    return position;
}

float Particle::getRadius() const {
    return radius;
}

sf::Vector2f Particle::getVelocity() const {
    return velocity;
}

float Particle::getMass() const {
    return mass;
}

void Particle::setPosition(const sf::Vector2f &newPosition) {
    position = newPosition;
    shape.setPosition(position);
}
