#include "Simulation.hpp"

Simulation::Simulation() 
    : window(sf::VideoMode(800, 600), "Particle Collision Simulation") {
    particles.emplace_back(100.f, 100.f, 20.f, 1.f, sf::Vector2f(100.f, 50.f));
    particles.emplace_back(300.f, 300.f, 30.f, 1.5f, sf::Vector2f(-50.f, -100.f));
    particles.emplace_back(200.f, 150.f, 25.f, 1.2f, sf::Vector2f(30.f, 70.f));
    particles.emplace_back(600.f, 400.f, 20.f, 1.f, sf::Vector2f(-60.f, 20.f));
	particles.emplace_back(500.f, 300.f, 10.f, 1.1f, sf::Vector2f(60.f, -20.f));
	particles.emplace_back(345.f, 400.f, 20.f, 1.f, sf::Vector2f(-40.f, 60.f));
	particles.emplace_back(150.f, 250.f, 15.f, 0.9f, sf::Vector2f(50.f, 40.f));
	particles.emplace_back(400.f, 450.f, 22.f, 1.3f, sf::Vector2f(-35.f, 75.f));
	particles.emplace_back(550.f, 200.f, 18.f, 1.2f, sf::Vector2f(40.f, -60.f));
	particles.emplace_back(250.f, 350.f, 12.f, 1.0f, sf::Vector2f(-70.f, 30.f));
	particles.emplace_back(120.f, 320.f, 16.f, 1.0f, sf::Vector2f(45.f, 55.f));
	particles.emplace_back(480.f, 260.f, 25.f, 1.4f, sf::Vector2f(-30.f, 60.f));
	particles.emplace_back(350.f, 150.f, 20.f, 1.1f, sf::Vector2f(25.f, -50.f));
	particles.emplace_back(700.f, 180.f, 22.f, 1.2f, sf::Vector2f(-55.f, 35.f));
	particles.emplace_back(240.f, 500.f, 19.f, 1.3f, sf::Vector2f(60.f, -30.f));
	particles.emplace_back(520.f, 350.f, 18.f, 1.0f, sf::Vector2f(-40.f, 50.f));
	particles.emplace_back(650.f, 450.f, 17.f, 1.2f, sf::Vector2f(35.f, 65.f));
	particles.emplace_back(280.f, 120.f, 15.f, 0.8f, sf::Vector2f(-50.f, -40.f));
	particles.emplace_back(600.f, 250.f, 24.f, 1.5f, sf::Vector2f(40.f, -50.f));
	particles.emplace_back(320.f, 400.f, 20.f, 1.1f, sf::Vector2f(-45.f, 35.f));
   // particles.emplace_back(500.f, 200.f, 30.f, 2.f, sf::Vector2f(-20.f, 90.f));
}

void Simulation::run() {
    sf::Clock clock;
    const float timeStep = 1.0f / 60.0f;
    float accumulator = 0.0f;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        handleInput();

        while (accumulator >= timeStep) {
            update(timeStep);
            accumulator -= timeStep;
        }

        render();
    }
}

void Simulation::update(float deltaTime) {
    Physics::update(particles, deltaTime);
    Physics::handleCollisions(particles);
    Physics::handleWallCollisions(particles, window);
}

void Simulation::render() {
    window.clear();
    for (auto &particle : particles) {
        particle.render(window);
    }
    window.display();
}

void Simulation::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
