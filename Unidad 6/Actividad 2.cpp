#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath> 

template <typename T>
T clamp(T valor, T minimo, T maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Movimiento con Aceleración Variable");
    window.setFramerateLimit(60);


    sf::CircleShape circle(20.f);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(400, 300);


    float velocidadX = 0.0f, velocidadY = 0.0f;
    float aceleracionX = 0.0f, aceleracionY = 0.0f;
    const float maxVelocidad = 10.0f;
    const float desaceleracion = 0.98f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        aceleracionX = 0.0f;
        aceleracionY = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            aceleracionX = -0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            aceleracionX = 0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            aceleracionY = -0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            aceleracionY = 0.2f;
        }


        velocidadX += aceleracionX;
        velocidadY += aceleracionY;

        if (aceleracionX == 0.0f) {
            velocidadX *= desaceleracion;
        }
        if (aceleracionY == 0.0f) {
            velocidadY *= desaceleracion;
        }


        if (velocidadX > maxVelocidad) velocidadX = maxVelocidad;
        if (velocidadX < -maxVelocidad) velocidadX = -maxVelocidad;

        if (velocidadY > maxVelocidad) velocidadY = maxVelocidad;
        if (velocidadY < -maxVelocidad) velocidadY = -maxVelocidad;

        circle.move(velocidadX, velocidadY);


        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
