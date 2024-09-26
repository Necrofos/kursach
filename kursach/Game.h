//#ifndef GAME_H
//#define GAME_H
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "settings.h"
//#include "Collision.h"
//
//// ����� ����
//class Game {
//public:
//    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Football Heads"),
//        player1(100.f, WINDOW_HEIGHT - PLAYER_HEIGHT),
//        player2(WINDOW_WIDTH - 150.f, WINDOW_HEIGHT - PLAYER_HEIGHT),
//        ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f),
//        leftGoal(sf::Vector2f(10.f, GOAL_HEIGHT)),
//        rightGoal(sf::Vector2f(10.f, GOAL_HEIGHT)) {
//
//        leftGoal.setPosition(0.f, WINDOW_HEIGHT - GOAL_HEIGHT);
//        leftGoal.setFillColor(sf::Color::White);
//
//        rightGoal.setPosition(WINDOW_WIDTH - 10.f, WINDOW_HEIGHT - GOAL_HEIGHT);
//        rightGoal.setFillColor(sf::Color::White);
//
//        score1 = 0;
//        score2 = 0;
//    }
//
//    void run() {
//        sf::Clock clock;
//
//        while (window.isOpen()) {
//            float dt = clock.restart().asSeconds();
//            handleEvents();
//            update(dt);
//            render();
//        }
//    }
//
//private:
//    sf::RenderWindow window;
//    Player player1;
//    Player player2;
//    Ball ball;
//    sf::RectangleShape leftGoal;
//    sf::RectangleShape rightGoal;
//    int score1, score2;
//
//    void handleEvents() {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // ���������� ��������
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//            player1.moveLeft(1.f); // dt ����� ������� �������������
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//            player1.moveRight(1.f); // dt ����� ������� �������������
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//            player2.moveLeft(1.f);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//            player2.moveRight(1.f);
//        }
//    }
//
//    void update(float dt) {
//        // ��������� ��������� ���� � ������ ����������
//        ball.applyGravity(dt);
//        ball.update(dt);
//
//        // �������� ������������
//        checkWallCollision(ball); // �������� ������������ �� ��������
//        checkGroundCollision(ball); // �������� ������������ � ������
//        checkCeilingCollision(ball); // �������� ������������ � ��������
//
//        // �������� ������������ ���� � ��������
//        handleBallPlayerCollision(ball, player1);
//        handleBallPlayerCollision(ball, player2);
//
//        // �������� �� ��� � ����� ������
//        if (isGoal(ball, leftGoal)) {
//            score2++; // ����������� ���� ������� ������
//            std::cout << "Player 2 scores! Score: " << score1 << " - " << score2 << std::endl;
//            resetBall();
//        }
//
//        // �������� �� ��� � ������ ������
//        if (isGoal(ball, rightGoal)) {
//            score1++; // ����������� ���� ������� ������
//            std::cout << "Player 1 scores! Score: " << score1 << " - " << score2 << std::endl;
//            resetBall();
//        }
//    }
//
//    void render() {
//        window.clear();
//        window.draw(player1.shape);
//        window.draw(player2.shape);
//        window.draw(ball.shape);
//        window.draw(leftGoal);
//        window.draw(rightGoal);
//        window.display();
//    }
//
//    void handleBallPlayerCollision(Ball& ball, Player& player) {
//        if (isBallCollidingWithPlayer(ball, player)) {
//            // ������������� ������������ �������� ������� � �������������� � ������� �������
//            ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS; // ������ �����
//            ball.velocity.x = (ball.shape.getPosition().x + BALL_RADIUS > player.shape.getPosition().x)
//                ? BALL_VELOCITY * ENERGY_LOSS // ������ ������ � ������� �������
//                : -BALL_VELOCITY * ENERGY_LOSS; // ������ ����� � ������� �������
//        }
//    }
//
//    void resetBall() {
//        ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f); // ��� � �����
//        ball.velocity = sf::Vector2f(BALL_VELOCITY, -BALL_VELOCITY); // �������� ��������
//    }
//};
//
//#endif // GAME_H
