#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "ball.h"
#include "player.h"

// Проверка столкновения мяча с игроком
bool isBallCollidingWithPlayer(const Ball& ball, const Player& player) {
    // Определяем центры мяча и игрока
    sf::Vector2f ballCenter = ball.shape.getPosition() + sf::Vector2f(BALL_RADIUS, BALL_RADIUS);
    sf::Vector2f playerCenter = player.shape.getPosition() + sf::Vector2f(PLAYER_RADIUS, PLAYER_RADIUS);

    // Вычисляем разницу по координатам
    float dx = ballCenter.x - playerCenter.x;
    float dy = ballCenter.y - playerCenter.y;

    // Вычисляем расстояние между центрами
    float distanceSquared = dx * dx + dy * dy; // Не берем корень, чтобы избежать лишних вычислений

    // Вычисляем сумму радиусов
    float radiusSum = BALL_RADIUS + PLAYER_RADIUS;

    // Проверяем столкновение
    return distanceSquared <= radiusSum * radiusSum; // Сравниваем с квадратом суммы радиусов
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
        ball.velocity.y *= -1; // Отскок вверх
    }
}

// Проверка столкновения мяча с потолком
void checkCeilingCollision(Ball& ball) {
    if (ball.shape.getPosition().y <= 0) {
        ball.velocity.y = -ball.velocity.y;// Отскок от потолка
    }
}


#endif // COLLISION_H
