#include <SFML/Graphics.hpp>
#include <cmath>

// Constants
const double mass = 1.0;            // Mass of the cube (kg)
const double springConstant = 0.95; // Spring constant (N/m)
const double dampingConstant = 0.005; // Damping constant (N·s/m)
const double dt = 0.02;             // Time step (s)

// Function to compute acceleration
double acceleration(double x, double v) {
    return -(springConstant / mass) * x - (dampingConstant / mass) * v;
}

int main() {
    // Initial conditions
    double x = 1.0;   // Initial displacement (m)
    double v = 0.0;   // Initial velocity (m/s)

    // SFML setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mass-Spring Simulation");
    window.setFramerateLimit(60);

    // Create objects
    sf::RectangleShape cube(sf::Vector2f(50, 50)); // Cube
    cube.setFillColor(sf::Color::Blue);
    cube.setOrigin(25, 25);

    sf::RectangleShape wall(sf::Vector2f(10, 300)); // Wall
    wall.setFillColor(sf::Color::Black);
    wall.setPosition(100, 150);

    sf::VertexArray spring(sf::LineStrip, 10); // Spring
    for (int i = 0; i < 10; ++i) {
        spring[i].color = sf::Color::Red;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Numerical integration (Euler method)
        double a = acceleration(x, v);
        v += a * dt;
        x += v * dt;

        // Update positions
        double position = 200 + x * 95; // Scale displacement for visualization
        cube.setPosition(position, 300);

        // Update spring shape
        double springLength = position - 110;
        for (int i = 0; i < 10; ++i) {
            double yOffset = std::sin(i * 3.14 / 5) * 10;
            spring[i].position = sf::Vector2f(110 + springLength * i / 9, 300 + yOffset);
        }

        // Rendering
        window.clear(sf::Color::White);
        window.draw(wall);
        window.draw(spring);
        window.draw(cube);
        window.display();
    }

    return 0;
}
