#include "ball.h"


Ball::Ball(float x, float y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
    velocity = sf::Vector2f(0.f, -BALL_VELOCITY);
}

void Ball::update(float dt) {
    shape.move(velocity * dt);
    velocity.y += GRAVITY * dt;
    if (shape.getPosition().x + 2 * BALL_RADIUS >= WINDOW_HEIGHT - 5) {
        velocity.x *= 0.8;
    }
}