#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 20;
const int MAX_BALLS = 2;
const float BALL_SPEED = 200.0f;
const int POINTS_PER_BALL = 10;
const int MAX_POINTS = 300;

struct Ball {
    sf::CircleShape shape;
    float speed;

    Ball(float x, float y, float speed) : speed(speed) {
        shape.setRadius(BALL_RADIUS);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }

    void update(float deltaTime) {
        shape.move(speed * deltaTime, 0.0f);
    }

    bool isClicked(const sf::Vector2f& mousePos) const {
        return shape.getGlobalBounds().contains(mousePos);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tiro al Disco");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<Ball> balls;
    int score = 0; // Marcador


    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Equipo\\Desktop\\Tipografia\\Manrope-VariableFont_Wght.ttf")) {
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(36);
    winnerText.setFillColor(sf::Color::Green);
    winnerText.setString("¡Has ganado!\nLlegaste a la puntuación máxima de 300.\nYOU WINNER");
    winnerText.setPosition(SCREEN_WIDTH / 14, SCREEN_HEIGHT / 3);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);


                for (auto it = balls.begin(); it != balls.end();) {
                    if (it->isClicked(mousePos)) {
                        it = balls.erase(it);
                        score += POINTS_PER_BALL;
                    }
                    else {
                        ++it;
                    }
                }
            }
        }


        if (score >= MAX_POINTS) {
            window.clear(sf::Color::Black);
            window.draw(winnerText);
            window.display();
            sf::sleep(sf::seconds(3));
            window.close();
            break;
        }


        float deltaTime = clock.restart().asSeconds();


        for (auto& ball : balls) {
            ball.update(deltaTime);


            if (ball.shape.getPosition().x > SCREEN_WIDTH) {
                ball.shape.setPosition(-BALL_RADIUS * 2, std::rand() % (SCREEN_HEIGHT - BALL_RADIUS * 2));
            }
        }


        if (balls.empty()) {
            for (int i = 0; i < MAX_BALLS; ++i) {
                float startY = std::rand() % (SCREEN_HEIGHT - BALL_RADIUS * 2);
                balls.emplace_back(-BALL_RADIUS * 2, startY, BALL_SPEED);
            }
        }


        scoreText.setString("Puntos: " + std::to_string(score));


        window.clear(sf::Color::Black);
        window.draw(scoreText);

        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }

        window.display();
    }

    return 0;
}

