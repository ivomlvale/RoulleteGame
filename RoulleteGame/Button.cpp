#include "Button.h"


/* initVariables()
* action: initialize variable to use during the class
* input :
* output :
* algorithm : assign values to variables
*/
void Button::initVaribles()
{
	//initialize the state button o idle
	this->wasPressed = false;
	this->buttonState = ButtonIdle;
}

//Constructor and Destructor
Button::Button(float x, float y, float widht, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	initVaribles();

	//set pos and size of button
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(widht, height));

	//set text infos
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(36);
	this->text.setPosition(							//center de text on button
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width) / 2.0f - this->text.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height) / 2.0f - this->text.getGlobalBounds().height / 2.0f - 10.0f
	);


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == ButtonActive)
		return true;
	else
		return false;
}

//Functions

/* ChangeButtonColor()
* action: assign colors to the respective states
* input : receive 3 Sf:Color for each state
* output :
* algorithm : assigns the values received by variables to the button states
*/
void Button::ChangeButtonColor(sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

/* UpdateButton()
* action: update the state of the button
* input : receive the window of game, the event and mouse position to work with button state
* output :
* algorithm : change the button state depending on the mouse position and if button was pressed or not
*/
void Button::UpdateButton(sf::RenderWindow& window, const sf::Event* event, const sf::Vector2f mousePos)
{
	/* Update the booleans for clicky button*/
	if (wasPressed == false)
	{
		//Idle
		this->buttonState = ButtonIdle;

		//Hover
		if (this->shape.getGlobalBounds().contains(mousePos))
		{
			this->buttonState = ButtonHover;

			if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
			{
				this->wasPressed = true;
				this->buttonState = ButtonActive;
			}
			if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
			{
				this->buttonState = ButtonHover;
			}
		}
	}


	//assign the color for each state
	switch (this->buttonState)
	{
	case ButtonIdle:
		this->shape.setFillColor(this->idleColor);
		break;
	case ButtonHover:
		this->shape.setFillColor(this->hoverColor);
		break;
	case ButtonActive:
		this->shape.setFillColor(this->activeColor);
		break;
	}
}

/* RenderButton()
* action: render button on screen
* input: receive a target for rendering operations
* output:
* algorithm: draw the Button on screen, shape and text
*/
void Button::RenderButton(sf::RenderTarget* target)
{
	//draw button
	target->draw(this->shape);
	target->draw(this->text);
}



