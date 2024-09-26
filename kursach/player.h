#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "settings.h"




class Player {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Player(float x, float y) {
        shape.setRadius(PLAYER_WIDTH / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
        shape.setScale(1.0f, 1.3f);
        velocity = sf::Vector2f(0.f, 0.f);
    }

    void moveLeft(float dt) {
        shape.move(-PLAYER_VELOCITY * dt, 0.f);
    }

    void moveRight(float dt) {
        shape.move(PLAYER_VELOCITY * dt, 0.f);
    }
};