#ifndef SETTINGS_H
#define SETTINGS_H
#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


const float BALL_RADIUS = 30.f;
const float BALL_VELOCITY = 300.f;



const float PLAYER_RADIUS = 40.f;
const float PLAYER_WIDTH = 2 * PLAYER_RADIUS;
const float PLAYER_HEIGHT = 2 * PLAYER_RADIUS;
const float PLAYER_VELOCITY = 350.f;
const float JUMP_FORCE = 500.f;
const float GROUD_FLOOR = 550.f;

const sf::Color color1 = sf::Color::Blue;
const sf::Color color2 = sf::Color::Green;


const float GRAVITY = 981.f;
const float ENERGY_LOSS = 0.8f;


const float GOAL_WIDTH = 100.f;
const float GOAL_HEIGHT = 200.f;

#endif // SETTINGS_H