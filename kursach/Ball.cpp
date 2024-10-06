#pragma once
#include "ball.h"


Ball::Ball(float x, float y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
    velocity = sf::Vector2f(0.f, -BALL_VELOCITY);
}

void Ball::update(float dt) {
    shape.move(velocity * dt);
}

void Ball::applyGravity(float dt) {
    velocity.y += GRAVITY * dt;
}