#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

int collisionCounter = 0; // Global counter for cube collisions

class Cube {
public:
    float mass;
    sf::Vector2f velocity;
    sf::RectangleShape shape;
    bool isColliding; // Flag to track the collision state

    Cube(float m, sf::Vector2f v, sf::Vector2f pos, sf::Vector2f size, sf::Color color) : mass(m), velocity(v), isColliding(false) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(color);
    }

    void collide(Cube& other) {
        if (!isColliding && !other.isColliding) {
            collisionCounter++;
        }

        isColliding = true;
        other.isColliding = true;

        sf::Vector2f v1 = velocity;
        sf::Vector2f v2 = other.velocity;
        float m1 = mass;
        float m2 = other.mass;

        sf::Vector2f newVelocity1 = ((m1 - m2) / (m1 + m2)) * v1 + ((2 * m2) / (m1 + m2)) * v2;
        sf::Vector2f newVelocity2 = ((2 * m1) / (m1 + m2)) * v1 + ((m2 - m1) / (m1 + m2)) * v2;

        if (m1 > m2) {
            velocity.x = (v1.x > 0) ? std::max(v1.x, newVelocity1.x) : std::min(v1.x, newVelocity1.x);
        }
        else {
            velocity.x = newVelocity1.x;
        }

        if (m2 > m1) {
            other.velocity.x = (v2.x > 0) ? std::max(v2.x, newVelocity2.x) : std::min(v2.x, newVelocity2.x);
        }
        else {
            other.velocity.x = newVelocity2.x;
        }

        float overlapX = std::max(0.f, (shape.getPosition().x + shape.getSize().x) - other.shape.getPosition().x);
        shape.move(-overlapX / 2, 0);
        other.shape.move(overlapX / 2, 0);

        const float damping = 0.95f;
        velocity *= damping;
        other.velocity *= damping;
    }

    void handleWallCollision(const sf::RenderWindow& window) {
        if (shape.getPosition().x < 0 || shape.getPosition().x + shape.getSize().x > window.getSize().x) {
            velocity.x *= -0.9f;
            if (shape.getPosition().x < 0) {
                shape.setPosition(0, shape.getPosition().y);
            }
            else if (shape.getPosition().x + shape.getSize().x > window.getSize().x) {
                shape.setPosition(window.getSize().x - shape.getSize().x, shape.getPosition().y);
            }
        }
    }

    void update() {
        shape.move(velocity);
        isColliding = false;
    }
};

std::string formatVelocity(float v) {
    return std::to_string(v);
}

std::string formatMass(float mass) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << mass;
    return stream.str();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Simulation");

    Cube cube1(1.0f, sf::Vector2f(5.0f, 0.0f), sf::Vector2f(100.0f, 450.0f), sf::Vector2f(50.0f, 50.0f), sf::Color::Red);
    Cube cube2(100.0f, sf::Vector2f(-2.0f, 0.0f), sf::Vector2f(600.0f, 400.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Blue);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading Arial.ttf" << std::endl;
        return 1;
    }

    sf::Text collisionText, cube1Text, cube2Text;
    collisionText.setFont(font);
    cube1Text.setFont(font);
    cube2Text.setFont(font);

    collisionText.setCharacterSize(24);
    cube1Text.setCharacterSize(20);
    cube2Text.setCharacterSize(20);

    collisionText.setFillColor(sf::Color::Black);
    cube1Text.setFillColor(sf::Color::Red);
    cube2Text.setFillColor(sf::Color::Blue);

    collisionText.setPosition(10, 10);
    cube1Text.setPosition(10, 40);
    cube2Text.setPosition(10, 70);

    // Create ground shape
    sf::RectangleShape ground(sf::Vector2f(800.0f, 100.0f));
    ground.setPosition(0.0f, 500.0f);
    ground.setFillColor(sf::Color(128, 128, 128)); // Set ground color

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cube1.update();
        cube2.update();

        sf::FloatRect bounds1 = cube1.shape.getGlobalBounds();
        sf::FloatRect bounds2 = cube2.shape.getGlobalBounds();
        if (bounds1.intersects(bounds2)) {
            cube1.collide(cube2);
        }

        cube1.handleWallCollision(window);
        cube2.handleWallCollision(window);

        collisionText.setString("Collisions: " + std::to_string(collisionCounter));
        cube1Text.setString("Cube 1 - Mass: " + formatMass(cube1.mass) + ", Velocity: " + formatVelocity(cube1.velocity.x));
        cube2Text.setString("Cube 2 - Mass: " + formatMass(cube2.mass) + ", Velocity: " + formatVelocity(cube2.velocity.x));

        window.clear(sf::Color::White);
        window.draw(ground); // Draw the ground
        window.draw(cube1.shape);
        window.draw(cube2.shape);
        window.draw(collisionText);
        window.draw(cube1Text);
        window.draw(cube2Text);
        window.display();

        sf::sleep(sf::milliseconds(5));
    }

    return 0;
}
