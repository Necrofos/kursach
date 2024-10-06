#pragma once
#include "player.h"

Player::Player(float x, float y, sf::Color color) {
    shape.setRadius(PLAYER_WIDTH / 2);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    velocity = sf::Vector2f(0.f, 0.f);
}

void Player::moveLeft(float dt) {
    shape.move(-PLAYER_VELOCITY * dt, 0.f);
}

void Player::moveRight(float dt) {
    shape.move(PLAYER_VELOCITY * dt, 0.f);
}

void Player::jump() {
    if (!isJumping) {
        velocity.y = -JUMP_FORCE;
        isJumping = true;
    }
}

void Player::update(float dt) {
    if (isJumping) {
        velocity.y += GRAVITY * dt;
        shape.move(0.f, velocity.y * dt);

        if (shape.getPosition().y + shape.getRadius() >= GROUD_FLOOR) {
            isJumping = false;
            velocity.y = 0;
            shape.setPosition(shape.getPosition().x, GROUD_FLOOR - shape.getRadius());
        }
    }
}