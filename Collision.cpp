#include <SFML/Graphics.hpp>
#include <cmath>

class Cube {
public:
    float mass;
    sf::Vector2f velocity;
    sf::RectangleShape shape;

    Cube(float m, sf::Vector2f v, sf::Vector2f pos, sf::Vector2f size, sf::Color color) : mass(m), velocity(v) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(color);
    }

    void collide(Cube& other) {
        float v1 = velocity.x;
        float v2 = other.velocity.x;
        float m1 = mass;
        float m2 = other.mass;

        velocity.x = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
        other.velocity.x = v2 * (m2 - m1) / (m1 + m2) + v1 * 2 * m1 / (m1 + m2);

        // Apply damping to simulate energy loss
        velocity *= 0.9f;
        other.velocity *= 0.9f;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision");

    sf::RectangleShape ground(sf::Vector2f(800.0f, 100.0f));
    ground.setPosition(0.0f, 500.0f);
    ground.setFillColor(sf::Color(128, 128, 128));

    Cube cube1(1.0f, sf::Vector2f(2000.0f, 0.0f), sf::Vector2f(100.0f, 450.0f), sf::Vector2f(50.0f, 50.0f), sf::Color::Magenta);
    Cube cube2(1000.0f, sf::Vector2f(-2.0f, 0.0f), sf::Vector2f(600.0f, 400.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cube1.shape.move(cube1.velocity);
        cube2.shape.move(cube2.velocity);

        if (cube1.shape.getPosition().x < 0 || cube1.shape.getPosition().x + cube1.shape.getSize().x > window.getSize().x) {
            cube1.velocity.x *= -0.9f; // 10% energy loss
        }
        if (cube2.shape.getPosition().x < 0 || cube2.shape.getPosition().x + cube2.shape.getSize().x > window.getSize().x) {
            cube2.velocity.x *= -0.9f; // 10% energy loss
        }

        sf::FloatRect bounds1 = cube1.shape.getGlobalBounds();
        sf::FloatRect bounds2 = cube2.shape.getGlobalBounds();
        if (bounds1.intersects(bounds2)) {
            cube1.collide(cube2);
        }

        window.clear(sf::Color::White);
        window.draw(ground);
        window.draw(cube1.shape);
        window.draw(cube2.shape);
        window.display();

        sf::sleep(sf::milliseconds(20)); // limit the frame rate to 50 fps
    }

    return 0;
}
