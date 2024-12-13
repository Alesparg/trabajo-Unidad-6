#include <SFML/Graphics.hpp>

int main() {

    const int windowWidth = 800;
    const int windowHeight = 600;


    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Rebote ");


    sf::CircleShape sphere(20.0f);
    sphere.setFillColor(sf::Color::Red);
    sphere.setPosition(windowWidth / 2, 0);


    float posY = 0.0f;
    float velocity = 0.0f;
    const float gravity = 0.3f;
    const float reboundFactor = 0.7f;
    const float floorY = windowHeight - 40;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        velocity += gravity;
        posY += velocity;


        if (posY > floorY) {
            posY = floorY;
            velocity = -velocity * reboundFactor;
        }


        sphere.setPosition(windowWidth / 2 - 20, posY);


        window.clear(sf::Color::Black);
        window.draw(sphere);
        window.display();
    }

    return 0;
}
