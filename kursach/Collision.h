#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "ball.h"
#include "player.h"
#include <iostream>

bool isBallCollidingWithPlayer(const Ball& ball, const Player& player) {
    sf::Vector2f ballCenter = ball.shape.getPosition() + sf::Vector2f(BALL_RADIUS, BALL_RADIUS);
    sf::Vector2f playerCenter = player.shape.getPosition() + sf::Vector2f(PLAYER_RADIUS, PLAYER_RADIUS);

    float dx = ballCenter.x - playerCenter.x;
    float dy = ballCenter.y - playerCenter.y;

    float distanceSquared = dx * dx + dy * dy; 

    float radiusSum = BALL_RADIUS + PLAYER_RADIUS;

    return distanceSquared <= radiusSum * radiusSum;
}


bool isGoal(const Ball& ball, const sf::RectangleShape& goal) {
    return ball.shape.getGlobalBounds().intersects(goal.getGlobalBounds());
}

// Проверка столкновения мяча со стенами (лево и право)
void checkWallCollision(Ball& ball) {
    if (ball.shape.getPosition().x <= 0 || ball.shape.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH) {
        ball.velocity.x = -ball.velocity.x * ENERGY_LOSS; // Отскок от боковых стенок
    }
}

// Проверка столкновения мяча с землёй)
void checkGroundCollision(Ball& ball) {
    if (ball.shape.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT) {
        ball.shape.setPosition(ball.shape.getPosition().x, WINDOW_HEIGHT - BALL_RADIUS * 2); // Устанавливаем на нижнюю границу
        ball.velocity.y *= -ENERGY_LOSS; // Отскок вверх
    }
}

// Проверка столкновения мяча с потолком
void checkCeilingCollision(Ball& ball) {
    if (ball.shape.getPosition().y <= 0) {
        ball.velocity.y = -ball.velocity.y;// Отскок от потолка
    }
}

//Проверка столкновения игрока со стеной
void checkPlayerWalls(Player& player){
    if (player.shape.getPosition().x <= 0) {
        player.shape.setPosition(0, player.shape.getPosition().y);
        player.velocity.x = 0;
    }
    else if (player.shape.getPosition().x + 2 * PLAYER_RADIUS > WINDOW_WIDTH) {
        player.shape.setPosition(WINDOW_WIDTH - 2 * PLAYER_RADIUS - 1, player.shape.getPosition().y);
        player.velocity.x = 0;
    }
}

void checkBallPlayer(Ball& ball, Player& player) {
    if (isBallCollidingWithPlayer(ball, player)) {
        sf::Vector2f ballCenter = ball.shape.getPosition() + sf::Vector2f(BALL_RADIUS, BALL_RADIUS);
        sf::Vector2f playerCenter = player.shape.getPosition() + sf::Vector2f(PLAYER_RADIUS, PLAYER_RADIUS);
        float dx = ballCenter.x - playerCenter.x;
        float dy = ballCenter.y - playerCenter.y;

        ball.velocity.x = dx * 8;
        ball.velocity.y = dy * 8;
    }
}

