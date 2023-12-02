#include <SFML/Graphics.hpp>
#include <cmath>

class Cube {
public:
    float mass;
    sf::Vector2f velocity;
    sf::RectangleShape shape;

    Cube(float m, sf::Vector2f v, sf::Vector2f pos, sf::Vector2f size) : mass(m), velocity(v) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(sf::Color::Green);
    }

    void collide(Cube& other) {
        float v1 = velocity.x;
        float v2 = other.velocity.x;
        float m1 = mass;
        float m2 = other.mass;

        velocity.x = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
        other.velocity.x = v2 * (m2 - m1) / (m1 + m2) + v1 * 2 * m1 / (m1 + m2);
    }
};
