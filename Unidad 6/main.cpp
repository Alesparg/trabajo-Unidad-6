#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Círculo en Movimiento");
    window.setFramerateLimit(60);


    sf::CircleShape circle(20.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(0, 300);


    float V0 = 2.0f;
    float Vfinal = 10.0f;
    float velocidad = V0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        circle.move(velocidad, 0);


        if (circle.getPosition().x > window.getSize().x) {
            circle.setPosition(-circle.getRadius() * 2, circle.getPosition().y);
            velocidad += 1.0f;
            if (velocidad >= Vfinal) {
                std::cout << "Velocidad final alcanzada: " << velocidad << " píxeles/frame\n";
                window.close();
            }
        }


        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}


