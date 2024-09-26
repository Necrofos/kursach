#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "Ball.h"
#include "player.h"

// Проверка столкновения мяча с игроком
bool isBallCollidingWithPlayer(const Ball& ball, const Player& player) {
    return ball.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds());
}

// Проверка попадания мяча в ворота
bool isGoal(const Ball& ball, const sf::RectangleShape& goal) {
    return ball.shape.getGlobalBounds().intersects(goal.getGlobalBounds());
}

// Проверка столкновения мяча со стенами (лево и право)
void checkWallCollision(Ball& ball) {
    if (ball.shape.getPosition().x <= 0 || ball.shape.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH) {
        ball.velocity.x = -ball.velocity.x * ENERGY_LOSS; // Отскок от боковых стенок
    }
}

// Проверка столкновения мяча с нижней границей (земля)
void checkGroundCollision(Ball& ball) {
    if (ball.shape.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT) {
        ball.shape.setPosition(ball.shape.getPosition().x, WINDOW_HEIGHT - BALL_RADIUS * 2); // Устанавливаем на нижнюю границу
        ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // Отскок вверх
    }
}

// Проверка столкновения мяча с потолком
void checkCeilingCollision(Ball& ball) {
    if (ball.shape.getPosition().y <= 0) {
        ball.velocity.y = -ball.velocity.y * ENERGY_LOSS; // Отскок от потолка
    }
}

#endif // COLLISION_H
