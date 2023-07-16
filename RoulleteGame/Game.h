#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include "Ball.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


/*
	Class that will be responsible for the game mechanics.
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event* event;
	sf::Clock delay;

	//Audio
	//sf::Music music;

	//Ball Functions
	std::vector <Ball> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;
	int totalBalls;
	int redBalls, blueBalls, yellowBalls, whiteBalls, blackBalls;

	//GUI Variables
	sf::Font font;
	sf::Text textBP;
	sf::Text textCIN;
	sf::Text textCOUT;
	sf::Text textBLC;
	sf::Text textBETS;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Buttons Variables
	Button* startButton;
	Button* creditsInButton;
	Button* creditsOutButton;
	Button* closeGameButton;

	//Bet Variables
	int creditsIn;
	int creditsOut;
	int balance;
	int betsPlayed;
	int winColor;
	int winBet;
	int auxWinBet;
	int indexAuxBet;
	int drawBet;
	int gameState; //Game State (0 = draw; 1 = win; 2 = lose)

	//Private functions
	void initVariables();
	void initWindow();
	void initBackground();
	void initFont();
	void initText();
	void initButtons();
	void initMusic();


public:

	//Construtor and Destructor
	Game();
	virtual ~Game();


	//Accessors
	const bool Running() const;

	//Functions
	void PollEvents();

	//Ball Functions
	void SpawnBalls();
	int SelectBalls();

	//Bet Functions
	int ChoosePlayerBet();
	int WinBet();
	void WinLose();

	//Reset UI
	void ResetGui();

	//Update Functions
	void UpdateGui();
	void UpdateInfos();
	void UpdateBalls();
	void UpdateButtons();
	void Update();

	//Render Functions
	void RenderGui(sf::RenderTarget* target);
	void RenderButtons(sf::RenderTarget* target);
	void Render();
};

