#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "ball.h"
#include "player.h"

// �������� ������������ ���� � �������
bool isBallCollidingWithPlayer(const Ball& ball, const Player& player) {
    // ���������� ������ ���� � ������
    sf::Vector2f ballCenter = ball.shape.getPosition() + sf::Vector2f(BALL_RADIUS, BALL_RADIUS);
    sf::Vector2f playerCenter = player.shape.getPosition() + sf::Vector2f(PLAYER_RADIUS, PLAYER_RADIUS);

    // ��������� ������� �� �����������
    float dx = ballCenter.x - playerCenter.x;
    float dy = ballCenter.y - playerCenter.y;

    // ��������� ���������� ����� ��������
    float distanceSquared = dx * dx + dy * dy; // �� ����� ������, ����� �������� ������ ����������

    // ��������� ����� ��������
    float radiusSum = BALL_RADIUS + PLAYER_RADIUS;

    // ��������� ������������
    return distanceSquared <= radiusSum * radiusSum; // ���������� � ��������� ����� ��������
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
        ball.velocity.y *= -1; // ������ �����
    }
}

// �������� ������������ ���� � ��������
void checkCeilingCollision(Ball& ball) {
    if (ball.shape.getPosition().y <= 0) {
        ball.velocity.y = -ball.velocity.y;// ������ �� �������
    }
}


#endif // COLLISION_H
