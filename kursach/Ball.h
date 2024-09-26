#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "settings.h"

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Ball(float x, float y) {
        shape.setRadius(BALL_RADIUS);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
        velocity = sf::Vector2f(BALL_VELOCITY, -BALL_VELOCITY);
    }

    void update(float dt) {
        shape.move(velocity * dt);
    }

    void applyGravity(float dt) {
        velocity.y += GRAVITY * dt;
    }
};