#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "Ball.h"
#include "player.h"

// �������� ������������ ���� � �������
bool isBallCollidingWithPlayer(const Ball& ball, const Player& player) {
    return ball.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds());
}

// �������� ��������� ���� � ������
bool isGoal(const Ball& ball, const sf::RectangleShape& goal) {
    return ball.shape.getGlobalBounds().intersects(goal.getGlobalBounds());
}

// �������� ������������ ���� �� ������� (���� � �����)
void checkWallCollision(Ball& ball) {
    if (ball.shape.getPosition().x <= 0 || ball.shape.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH) {
        ball.velocity.x = -ball.velocity.x * ENERGY_LOSS; // ������ �� ������� ������
    }
}

// �������� ������������ ���� � ������ �������� (�����)
void checkGroundCollision(Ball& ball) {
    if (ball.shape.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT) {
        ball.shape.setPosition(ball.shape.getPosition().x, WINDOW_HEIGHT - BALL_RADIUS * 2); // ������������� �� ������ �������
        ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // ������ �����
    }
}

// �������� ������������ ���� � ��������
void checkCeilingCollision(Ball& ball) {
    if (ball.shape.getPosition().y <= 0) {
        ball.velocity.y = -ball.velocity.y * ENERGY_LOSS; // ������ �� �������
    }
}

#endif // COLLISION_H
