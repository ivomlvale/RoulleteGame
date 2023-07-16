#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


//enum for button´s state
enum buttonState { ButtonIdle = 0, ButtonHover = 1, ButtonActive = 2 };

class Button
{
private:
	short unsigned  buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	void initVaribles();

public:
	//Construtor and Destructor
	Button(float x, float y, float widht, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Variable
	bool wasPressed;

	//Accessors
	const bool isPressed() const;

	//Function
	void ChangeButtonColor(sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	void UpdateButton(sf::RenderWindow& window, const sf::Event* event, const sf::Vector2f mousePos);
	void RenderButton(sf::RenderTarget* target);

};

