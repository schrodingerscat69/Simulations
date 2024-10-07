#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class GravitySource
{
    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;

public:
    GravitySource(float pos_x, float pos_y, float strength)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        s.setPosition(pos);
        s.setFillColor(sf::Color::Yellow);
        s.setRadius(10);
        s.setOrigin(10, 10);  // Set origin to center the circle
    }

    void render(sf::RenderWindow &wind)
    {
        wind.draw(s);
    }

    sf::Vector2f get_pos()
    {
        return pos;
    }

    float get_strength()
    {
        return strength;
    }
};

class Particle
{
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape s;
    std::vector<sf::Vertex> trail;
    sf::Color color;

public:
    Particle(float pos_x, float pos_y, float vel_x, float vel_y, sf::Color color)
    {
        pos.x = pos_x;
        pos.y = pos_y;

        vel.x = vel_x;
        vel.y = vel_y;

        s.setPosition(pos);
        s.setFillColor(color);
        s.setRadius(6);
        s.setOrigin(6, 6);  // Set origin to center the circle

        this->color = color;
    }

    void render(sf::RenderWindow &wind)
    {
        // Draw the particle
        s.setPosition(pos);
        wind.draw(s);

        // Draw the trail
        if (!trail.empty())
        {
            wind.draw(&trail[0], trail.size(), sf::LinesStrip);
        }
    }

    void update_physics(GravitySource &source)
    {
        // Calculate gravitational pull from the gravity source
        float distance_x = source.get_pos().x - pos.x;
        float distance_y = source.get_pos().y - pos.y;

        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
        if (distance < 10) return;  // Avoid too strong a pull near the source

        float inverse_distance = 1.f / distance;

        float normalized_x = inverse_distance * distance_x;
        float normalized_y = inverse_distance * distance_y;

        float inverse_square_dropoff = inverse_distance * inverse_distance;

        float acceleration_x = normalized_x * source.get_strength() * inverse_square_dropoff;
        float acceleration_y = normalized_y * source.get_strength() * inverse_square_dropoff;

        vel.x += acceleration_x;
        vel.y += acceleration_y;

        // Update position
        pos.x += vel.x;
        pos.y += vel.y;

        // Update trail
        trail.push_back(sf::Vertex(pos, color));

        // Keep trail length limited
        if (trail.size() > 200)
        {
            trail.erase(trail.begin());
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Elliptical Orbits with Corrected Initial Conditions");
    window.setFramerateLimit(60);

    // Adjust gravity source strength to be more moderate for stable orbits
    GravitySource source(window.getSize().x / 2, window.getSize().y / 2, 7500);  // Adjusted gravity strength

    // Refined initial conditions for stable elliptical orbits
    Particle particle1(600, 700, 2.0, 0.5, sf::Color::Cyan);  // Adjusted velocity and position
    Particle particle2(800, 500, -2.0, 1.8, sf::Color::Red);   // Adjusted velocity and position
    Particle particle3(350, 650, 1.5, 0.5, sf::Color::Green);  // Adjusted velocity and position
    Particle particle4(500, 700, 3.0, -1.5, sf::Color::Blue);  // Adjusted velocity and position

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Update physics and render particles
        particle1.update_physics(source);
        particle2.update_physics(source);
        particle3.update_physics(source);
        particle4.update_physics(source);

        // Render the gravity source and particles
        source.render(window);
        particle1.render(window);
        particle2.render(window);
        particle3.render(window);
        particle4.render(window);

        // Display everything
        window.display();
    }

    return 0;
}
