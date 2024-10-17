#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "settings.h"
#include "player.h"
#include "ball.h"
#include "collision.h"
#include <iostream>
#include <cmath>

class Game {
public:
	Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Football Heads") {
		player1 = Player(100.f, WINDOW_HEIGHT - PLAYER_HEIGHT, color1);
		player2 = Player(WINDOW_WIDTH - 150.f, WINDOW_HEIGHT - PLAYER_HEIGHT, color2);
		ball = Ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

		leftGoal.setSize(sf::Vector2f(10.f, GOAL_HEIGHT));
		leftGoal.setPosition(0.f, WINDOW_HEIGHT - GOAL_HEIGHT);
		leftGoal.setFillColor(sf::Color::White);

		rightGoal.setSize(sf::Vector2f(10.f, GOAL_HEIGHT));
		rightGoal.setPosition(WINDOW_WIDTH - 10.f, WINDOW_HEIGHT - GOAL_HEIGHT);
		rightGoal.setFillColor(sf::Color::White);
	}

	void run() {
		sf::Clock clock;
		while (window.isOpen()) {
			float dt = clock.restart().asSeconds();
			update(dt);
			Check_Events(dt);
			draw();
		}
	}

private:
	Player player1;
	Player player2;
	sf::RenderWindow window;
	Ball ball;
	sf::RectangleShape leftGoal;
	sf::RectangleShape rightGoal;
	int score1 = 0;
	int score2 = 0;

	void Check_Events(float dt) {
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
	}

	void update(float dt) {
		ball.update(dt);
		player1.update(dt);
		player2.update(dt);
		Check_collisions(dt);
		Check_goals();
	}

	void Check_collisions(float dt) {
		checkCeilingCollision(ball);
		checkGroundCollision(ball);
		checkWallCollision(ball);
		checkPlayerWalls(player1);
		checkPlayerWalls(player2);

		checkBallPlayer(ball, player1);
		checkBallPlayer(ball, player2);
		//if (isBallCollidingWithPlayer(ball, player1)) {
		//	sf::Vector2f ballCenter = ball.shape.getPosition() + sf::Vector2f(BALL_RADIUS, BALL_RADIUS);
		//	sf::Vector2f playerCenter = player1.shape.getPosition() + sf::Vector2f(PLAYER_RADIUS, PLAYER_RADIUS);

		//	float dx = ballCenter.x - playerCenter.x;
		//	float dy = ballCenter.y - playerCenter.y;

		//	float distance = sqrt(dx * dx + dy * dy);


		//	float nx = dx / distance;
		//	float ny = dy / distance;

		//	float dotProduct = ball.velocity.x * nx + ball.velocity.y * ny;

		//	ball.velocity.x -= 2 * dotProduct * nx;
		//	ball.velocity.y -= 2 * dotProduct * ny;

		//	ball.velocity.x += player1.velocity.x;
		//	ball.velocity.y += player1.velocity.y;

		//	float overlap = (BALL_RADIUS + PLAYER_RADIUS) - distance;
		//	if (overlap > 0) {
		//		ball.shape.setPosition(ballCenter.x + nx * overlap, ballCenter.y + ny * overlap);
		//	}
		//}

		/*if (isBallCollidingWithPlayer(ball, player2)) {
			if (ball.shape.getPosition().x < player2.shape.getPosition().x + PLAYER_WIDTH) {
				ball.velocity.x = -BALL_VELOCITY * ENERGY_LOSS;
			}
			else {
				ball.velocity.x = BALL_VELOCITY * ENERGY_LOSS;
			}
			ball.velocity.y = -BALL_VELOCITY * ENERGY_LOSS;
		}*/
	}

	void Check_goals() {
		if (isGoal(ball, leftGoal)) {
			score2++;
			std::cout << "Player 2 scores! Score: " << score1 << " - " << score2 << std::endl;
			ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
			ball.velocity = sf::Vector2f(0, -BALL_VELOCITY);
		}

		if (isGoal(ball, rightGoal)) {
			score1++;
			std::cout << "Player 1 scores! Score: " << score1 << " - " << score2 << std::endl;
			ball.shape.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
			ball.velocity = sf::Vector2f(0, -BALL_VELOCITY);
		}
	}

	void draw() {
		window.clear();
		window.draw(player1.shape);
		window.draw(player2.shape);
		window.draw(ball.shape);
		window.draw(leftGoal);
		window.draw(rightGoal);
		window.display();
	}
};
