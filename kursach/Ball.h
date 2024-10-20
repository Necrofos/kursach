#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "settings.h"

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float k_energy;
    float p_energy;

    Ball(float x = 0, float y = 0);
    void update(float dt);
};