#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


#include "settings.h"
#include "player.h"
#include "ball.h"
#include "collision.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Football Heads");

    Player player1(100.f, WINDOW_HEIGHT - PLAYER_HEIGHT, color1);
    Player player2(WINDOW_WIDTH - 150.f, WINDOW_HEIGHT - PLAYER_HEIGHT, color2);


    Ball ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);


    sf::RectangleShape leftGoal;
    leftGoal.setSize(sf::Vector2f(10.f, GOAL_HEIGHT));
    leftGoal.setPosition(0.f, WINDOW_HEIGHT - GOAL_HEIGHT);
    leftGoal.setFillColor(sf::Color::White);

    sf::RectangleShape rightGoal;
    rightGoal.setSize(sf::Vector2f(10.f, GOAL_HEIGHT));
    rightGoal.setPosition(WINDOW_WIDTH - 10.f, WINDOW_HEIGHT - GOAL_HEIGHT);
    rightGoal.setFillColor(sf::Color::White);


    int score1 = 0;
    int score2 = 0;


    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player1.moveLeft(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player1.moveRight(dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player2.moveLeft(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player2.moveRight(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player1.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player2.jump();
        }

        ball.applyGravity(dt);
        ball.update(dt);
        player1.update(dt);
        player2.update(dt);


        if (ball.shape.getPosition().x <= 0 || ball.shape.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH) {
            ball.velocity.x = -ball.velocity.x * ENERGY_LOSS;
        }


        if (ball.shape.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT) {
            ball.shape.setPosition(ball.shape.getPosition().x, WINDOW_HEIGHT - BALL_RADIUS * 2);
            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS;
        }

        // Потолок
        if (ball.shape.getPosition().y <= 0) {
            ball.velocity.y = -ball.velocity.y * ENERGY_LOSS; // Отскок от потолка
        }

        // Столкновение с игроком
        if (isBallCollidingWithPlayer(ball, player1)) {

            if (ball.shape.getPosition().x + BALL_RADIUS > player1.shape.getPosition().x) {
                ball.velocity.x = BALL_VELOCITY * ENERGY_LOSS;
            }
            else {
                ball.velocity.x = -BALL_VELOCITY * ENERGY_LOSS;
            }
            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS;
        }

        if (isBallCollidingWithPlayer(ball, player2)) {

            if (ball.shape.getPosition().x < player2.shape.getPosition().x + PLAYER_WIDTH) {
                ball.velocity.x = -BALL_VELOCITY * ENERGY_LOSS; // Отскок влево
            }
            else {
                ball.velocity.x = BALL_VELOCITY * ENERGY_LOSS; // Отскок вправо
            }
            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // Отскок вверх
        }

        //    //Гол в левые
        if (isGoal(ball, leftGoal)) {
            score2++;
            std::cout << "Player 2 scores! Score: " << score1 << " - " << score2 << std::endl;
            ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
            ball.velocity = sf::Vector2f(0, -BALL_VELOCITY);
        }

        //    //Гол в правые
        if (isGoal(ball, rightGoal)) {
            score1++;
            std::cout << "Player 1 scores! Score: " << score1 << " - " << score2 << std::endl;
            ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
            ball.velocity = sf::Vector2f(0, -BALL_VELOCITY);
        }

        window.clear();
        window.draw(player1.shape);
        window.draw(player2.shape);
        window.draw(ball.shape);
        window.draw(leftGoal);
        window.draw(rightGoal);
        window.display();
    }

    return 0;
}
