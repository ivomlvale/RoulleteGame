#include "Ball.h"
#include <iostream>

//Private Function

/* initVariables()
* action: initialize variable to use during the class
* input:
* output:
* algorithm: assign values to variables
*/
void Ball::initVariables()
{
	//init the position ball out of the screen 
	this->ballPosition.x = -100.0f;
	this->ballPosition.y = 250.0f;

	//init velocity
	this->velocity = 5.5f;
}

/* initBall()
* action: initialize ball's variables to use during the class
* input: receive a game window
* output:
* algorithm: init a radius and move the ball to right position
* Create an array with 5 color for balls (Red, Blue, Yellow, White, Black)
* Generate a random calor and set that color on the ball
*/
void Ball::initBall(const sf::RenderWindow& window)
{
	//Define radius of ball
	this->ball.setRadius(50.0f);
	//move the ball
	this->ball.setPosition(ballPosition);

	//The color will be between Red, Blue, Yellow, White and Black
	sf::Color ballColor[5];
	ballColor[0] = sf::Color::Red;
	ballColor[1] = sf::Color::Blue;
	ballColor[2] = sf::Color::Yellow;
	ballColor[3] = sf::Color::White;
	ballColor[4] = sf::Color::Black;

	//Get a random index to choose the right color
	this->indexColor = GetRandomColor();

	//set the color
	this->ball.setFillColor(ballColor[this->indexColor]);
}

//Constructor and Destructor
Ball::Ball(const sf::RenderWindow& window)
{
	this->initVariables();
	this->initBall(window);
}

Ball::~Ball()
{
}

//Function

/* GetRandomColor()
* action: generate a random color for a ball
* input:
* output: returns the generated number
* algorithm: create a random number between 0 and 4.
*/
int Ball::GetRandomColor()
{
	//Generate a random number between 0 and 4
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->index = std::rand() % 5;

	//std::cout << this->index << std::endl;

	return index;
}

/* UpdateBall()
* action: update ball
* input:
* output:
* algorithm: move the ball giving a velocity
*/
void Ball::UpdateBall(const float dirX, const float dirY)
{
	this->ball.move(this->velocity * dirX, this->velocity * dirY);
}

/* RenderBall()
* action: render ball on screen
* input: receive a target for rendering operations
* output:
* algorithm: draw the ball on screen
*/
void Ball::RenderBall(sf::RenderTarget& target)
{
	target.draw(this->ball);
}

