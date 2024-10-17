#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "settings.h"


class Player {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool isJumping = false;
    float k_energy;
    float p_energy;

    Player(float x = 0, float y = 0, sf::Color color = sf::Color::Green);

    void moveLeft(float dt);
    void moveRight(float dt);
    void jump();
    void update(float dt);
};