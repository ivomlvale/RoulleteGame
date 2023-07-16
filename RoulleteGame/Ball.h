#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

/*
	Class that will be responsible for balls.
*/

class Ball
{
private:

	//GameObject
	sf::CircleShape ball;

	//Private functions
	void initVariables();
	void initBall(const sf::RenderWindow& window);

public:

	//Variables
	int index;
	int indexColor;
	sf::Vector2f ballPosition;
	float velocity;


	//Construtor and Destructor
	Ball(const sf::RenderWindow& window);
	virtual ~Ball();

	//Functions
	int GetRandomColor();
	void UpdateBall(const float dirX, const float dirY);
	void RenderBall(sf::RenderTarget& target);
};



