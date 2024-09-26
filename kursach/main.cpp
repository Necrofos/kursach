#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


#include "settings.h"
#include "player.h"
#include "Ball.h"


bool isBallCollidingWithPlayer(const Ball& ball, const Player& player) {
    return ball.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds());
}

bool isGoal(const Ball& ball, const sf::RectangleShape& goal) {
    return ball.shape.getGlobalBounds().intersects(goal.getGlobalBounds());
}

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Football Heads");

    // Создаем игроков
    Player player1(100.f, WINDOW_HEIGHT - PLAYER_HEIGHT);
    Player player2(WINDOW_WIDTH - 150.f, WINDOW_HEIGHT - PLAYER_HEIGHT);

    // Создаем мяч
    Ball ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

    // Создаем ворота
    sf::RectangleShape leftGoal;
    leftGoal.setSize(sf::Vector2f(10.f, GOAL_HEIGHT));
    leftGoal.setPosition(0.f, WINDOW_HEIGHT - GOAL_HEIGHT);
    leftGoal.setFillColor(sf::Color::White);

    sf::RectangleShape rightGoal;
    rightGoal.setSize(sf::Vector2f(10.f, GOAL_HEIGHT));
    rightGoal.setPosition(WINDOW_WIDTH - 10.f, WINDOW_HEIGHT - GOAL_HEIGHT);
    rightGoal.setFillColor(sf::Color::White);

    // Счет игры
    int score1 = 0;
    int score2 = 0;

    // Время кадра
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Управление игроками
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player1.moveLeft(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player1.moveRight(dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player2.moveLeft(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player2.moveRight(dt);
        }

        // Обновляем положение мяча с учетом гравитации
        ball.applyGravity(dt);
        ball.update(dt);

        // Проверка столкновений с границами окна
        if (ball.shape.getPosition().x <= 0 || ball.shape.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH) {
            ball.velocity.x = -ball.velocity.x * ENERGY_LOSS; // Отскок от боковых стенок
        }

        // Проверка столкновения с нижней границей окна (земля)
        if (ball.shape.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT) {
            ball.shape.setPosition(ball.shape.getPosition().x, WINDOW_HEIGHT - BALL_RADIUS * 2); // Устанавливаем на нижнюю границу
            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // Отскок вверх
        }

        // Проверка столкновений с потолком
        if (ball.shape.getPosition().y <= 0) {
            ball.velocity.y = -ball.velocity.y * ENERGY_LOSS; // Отскок от потолка
        }

        // Проверка столкновения мяча с игроками
        if (isBallCollidingWithPlayer(ball, player1)) {
            // Если мяч касается левого игрока, отскакивает в обратную сторону
            if (ball.shape.getPosition().x + BALL_RADIUS > player1.shape.getPosition().x) {
                ball.velocity.x = BALL_VELOCITY * ENERGY_LOSS; // Отскок вправо
            }
            else {
                ball.velocity.x = -BALL_VELOCITY * ENERGY_LOSS; // Отскок влево
            }
            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // Отскок вверх
        }

        if (isBallCollidingWithPlayer(ball, player2)) {
            // Если мяч касается правого игрока, отскакивает в обратную сторону
            if (ball.shape.getPosition().x < player2.shape.getPosition().x + PLAYER_WIDTH) {
                ball.velocity.x = -BALL_VELOCITY * ENERGY_LOSS; // Отскок влево
            }
            else {
                ball.velocity.x = BALL_VELOCITY * ENERGY_LOSS; // Отскок вправо
            }
            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // Отскок вверх
        }

        // Проверка на гол в левые ворота
        if (isGoal(ball, leftGoal)) {
            score2++; // Увеличиваем счет второго игрока
            std::cout << "Player 2 scores! Score: " << score1 << " - " << score2 << std::endl;
            ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f); // Мяч в центр
            ball.velocity = sf::Vector2f(BALL_VELOCITY, -BALL_VELOCITY); // Обнуляем скорость
        }

        // Проверка на гол в правые ворота
        if (isGoal(ball, rightGoal)) {
            score1++; // Увеличиваем счет первого игрока
            std::cout << "Player 1 scores! Score: " << score1 << " - " << score2 << std::endl;
            ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f); // Мяч в центр
            ball.velocity = sf::Vector2f(BALL_VELOCITY, -BALL_VELOCITY); // Обнуляем скорость
        }

        // Отрисовка
        window.clear();
        window.draw(player1.shape);
        window.draw(player2.shape);
        window.draw(ball.shape);
        window.draw(leftGoal);
        window.draw(rightGoal);
        window.display();
    }

    return 0;
}
