#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Movement");
    window.setFramerateLimit(60);

    // Define a triangle shape
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, sf::Vector2f(50, 100));
    triangle.setPoint(2, sf::Vector2f(100, 0));
    triangle.setFillColor(sf::Color::Green);

    // Position the triangle
    float x = 350.0f;
    float y = 400.0f;
    float gravity = 0.8f;
    float velocityY = 0.0f;
    bool isJumping = false;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Movement controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x -= 5.0f; // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += 5.0f; // Move right
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y -= 5.0f; // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += 5.0f; // Move down
        }

        // Jump logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            velocityY = -15.0f; // Jump impulse
            isJumping = true;
        }

        // Apply gravity
        velocityY += gravity;
        y += velocityY;

        // Ground collision
        if (y >= 400.0f) { // Ground level
            y = 400.0f;
            velocityY = 0.0f;
            isJumping = false;
        }

        // Update triangle position
        triangle.setPosition(x, y);

        // Clear and draw
        window.clear();
        window.draw(triangle);
        window.display();
    }

    return 0;
}