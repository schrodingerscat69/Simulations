#include "Simulation.hpp"
#include "Physics.hpp"

Simulation::Simulation(): window(sf::VideoMode(800,600), "Particle Collision Simulation")
{
	// Initialize particles
	particles.emplace_back(100.f, 100.f, 20.f, 1.f, sf::Vector2f(100.f, 50.f));
	particles.emplace_back(300.f, 300.f, 30.f, 1.5f, sf::Vector2f(-50.f, -100.f));
	particles.emplace_back(200.f, 150.f, 25.f, 1.2f, sf::Vector2f(30.f, 70.f));
	particles.emplace_back(600.f, 400.f, 20.f, 1.f, sf::Vector2f(-60.f, 20.f));
	particles.emplace_back(500.f, 200.f, 25.f, 2.f, sf::Vector2f(-70.f, 90.f));
}

void Simulation::run()
{
	sf::Clock clock;
	const float timeStep = 1.0f / 120.0f; // Target 60 FPS physics updates
	float accumulator = 0.0f;

	// Cap the frame rate for smooth rendering
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		accumulator += deltaTime;

		handleInput();

		// Update at fixed intervals
		while (accumulator >= timeStep)
		{
			update(timeStep);
			accumulator -= timeStep;
		}
		
		render();
	}
}

void Simulation::handleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Simulation::update(float deltaTime)
{
	Physics::update(particles, deltaTime);
	Physics::handleCollisions(particles);
	Physics::handleWallCollisions(particles, window);
}

void Simulation::render()
{
	window.clear();

	for (auto &particle : particles)
	{
		particle.render(window);
	}

	window.display();
}
