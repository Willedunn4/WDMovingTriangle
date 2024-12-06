#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For seeding random numbers

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Movement with Wall Collision");
    window.setFramerateLimit(60);

    // Define a triangle shape
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, sf::Vector2f(50, 100));
    triangle.setPoint(2, sf::Vector2f(100, 0));
    triangle.setFillColor(sf::Color::Green);

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Function to generate a random color
    auto getRandomColor = []() {
        return sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
    };

    // Position and physics variables
    float x = 350.0f;
    float y = 400.0f;
    float gravity = 0.8f;
    float velocityY = 0.0f;
    bool isJumping = false;
    const float speed = 5.0f;

    // Window dimensions
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;

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
            x -= speed; // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += speed; // Move right
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y -= speed; // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += speed; // Move down
        }

        // Jump logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            velocityY = -15.0f; // Jump impulse
            isJumping = true;
        }

        // Apply gravity
        velocityY += gravity;
        y += velocityY;

        // Wall collision detection and color change
        bool hitWall = false;

        if (x < 0.0f) { // Left wall
            x = 0.0f;
            hitWall = true;
        }
        if (x + 100.0f > windowWidth) { // Right wall
            x = windowWidth - 100.0f;
            hitWall = true;
        }
        if (y < 0.0f) { // Top wall
            y = 0.0f;
            hitWall = true;
        }
        if (y + 100.0f > windowHeight) { // Bottom wall
            y = windowHeight - 100.0f;
            velocityY = 0.0f; // Reset vertical velocity
            isJumping = false;
            hitWall = true;
        }

        if (hitWall) {
            triangle.setFillColor(getRandomColor());
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