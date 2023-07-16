#include <iostream>
#include "Game.h"


//Private Function

/* initVariables()
* action: initialize variable to use during the class
* input:
* output:
* algorithm: assign values to variables
*/
void Game::initVariables()
{
	this->window = nullptr;
	this->spawnTimerMax = 10.0f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 50;
	this->totalBalls = 0;
	this->redBalls = 0;
	this->blueBalls = 0;
	this->yellowBalls = 0;
	this->whiteBalls = 0;
	this->blackBalls = 0;
	this->balance = 1000;
	this->auxWinBet = 0;
	this->drawBet = 5; //5 is a number out of array, if we initialize as a 0 could be the first element higher then others and game state would be draw
	this->betsPlayed = 0;
}

/* initWindow()
* action: initialize window's variables
* input:
* output:
* algorithm: create a windoh 800x600 limiting framerate.
*/
void Game::initWindow()
{
	//Create a window defining a size
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Roulette", sf::Style::Titlebar | sf::Style::Close);
	this->event = new sf::Event();

	//limit the framerate
	this->window->setFramerateLimit(60);
}

/* initBackground()
* action: initialize background's variables
* input:
* output:
* algorithm: searches for the texture to use as a background and applies it by changing the scale
*/
void Game::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Background/table.jpg"))
	{
		std::cout << "Error loading background" << std::endl;
	}
	this->background.setTexture(backgroundTexture);
	this->background.setScale(1.9f, 1.9f);
}

/* initFont()
* action: initialize Font's variables
* input:
* output:
* algorithm: searches for the font to use as a main font and applies it
*/
void Game::initFont()
{
	if (!this->font.loadFromFile("Font/phantomstorm.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
}

/* initText()
* action: initialize text's variables
* input:
* output:
* algorithm: initialize the text from UI changing Position, Color and text size
*/
void Game::initText()
{
	//Balls played
	this->textBP.setFont(this->font);
	this->textBP.setFillColor(sf::Color(0, 20, 0));
	this->textBP.setCharacterSize(36);

	//Credits IN
	this->textCIN.setFont(this->font);
	this->textCIN.setFillColor(sf::Color(0, 20, 0));
	this->textCIN.setCharacterSize(20);
	this->textCIN.setPosition(275, 475);

	//Credits Out
	this->textCOUT.setFont(this->font);
	this->textCOUT.setFillColor(sf::Color(0, 20, 0));
	this->textCOUT.setCharacterSize(20);
	this->textCOUT.setPosition(450, 475);

	//Balance
	this->textBLC.setFont(this->font);
	this->textBLC.setFillColor(sf::Color(0, 20, 0));
	this->textBLC.setCharacterSize(36);
	this->textBLC.setPosition(600, 0);

	//Bets Played
	this->textBETS.setFont(this->font);
	this->textBETS.setFillColor(sf::Color(0, 20, 0));
	this->textBETS.setCharacterSize(24);
	this->textBETS.setPosition(720, 570);
}

/* initButtons()
* action: initialize Button's variables
* input:
* output:
* algorithm: initialize the buttons from UI giving the parameters requested by the constructor
*/
void Game::initButtons()
{
	//Start Button
	this->startButton = new Button(25, 500, 160, 50, &this->font, "Start",
		sf::Color(0, 25, 0, 180),
		sf::Color(0, 25, 0, 200),
		sf::Color(0, 25, 0, 255));


	//CreditsIn Button
	this->creditsInButton = new Button(225, 500, 160, 50, &this->font, "Credits IN",
		sf::Color(0, 25, 0, 180),
		sf::Color(0, 25, 0, 200),
		sf::Color(0, 25, 0, 255));

	//CreditsOut Button
	this->creditsOutButton = new Button(425, 500, 160, 50, &this->font, "Credits OUT",
		sf::Color(0, 25, 0, 180),
		sf::Color(0, 25, 0, 200),
		sf::Color(0, 25, 0, 255));

	//CloseGame Button
	this->closeGameButton = new Button(625, 500, 160, 50, &this->font, "Close Game",
		sf::Color(0, 25, 0, 180),
		sf::Color(0, 25, 0, 200),
		sf::Color(0, 25, 0, 255));
}

/*void Game::initMusic()
{
	//Init Music
	if (!this->music.openFromFile("Sound/GameSound.mp3")) {
		std::cout << "Error loading audio" << std::endl;
	}
	//Play music
	this->music.play();
}*/


//Constructor and Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initBackground();
	this->initFont();
	this->initText();
	this->initButtons();
	//this->initMusic();
}
Game::~Game()
{
	delete this->window;
	delete this->event;
	delete this->startButton;
	delete this->creditsInButton;
	delete this->creditsOutButton;
	delete this->closeGameButton;
	this->balls.clear();
}


//Accessors
const bool Game::Running() const
{
	return this->window->isOpen();
}

//Function

/* PollEvents()
* action: manage game events
* input:
* output:
* algorithm: close the window if player press escape or close button from titlebar
*/
void Game::PollEvents()
{
	//Event polling
	while (this->window->pollEvent(*this->event))
	{
		//close the game in title bar or with key "escape"
		switch (this->event->type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event->key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}


/* SpawnBalls()
* action: function to generate the balls
* input:
* output:
* algorithm: create a spwan time between each ball and add balls to the vector
*/
void Game::SpawnBalls()
{
	//Delay on ball's spawning
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 0.3f;
	}
	else
	{
		//generate ball until maxball number
		if (this->balls.size() < this->maxBalls)
		{
			//save the ball on vector
			this->balls.push_back(Ball(*this->window));
			this->spawnTimer = 0.0f;
			this->totalBalls++;
		}
	}
}


/* SelectBalls()
* action: function to select each ball went out more often
* input:
* output: returns the index that came out the most times (0 to 4), or return 5 if its draw
* algorithm: it goes through the array and adds the balls taking into account the index assigned to each color
* create an array (int) to save ho many ball have for wach color
* runs through this array to find out which ball came out the most times and saves the respective index
* if two balls come out same time its draw
*/
int Game::SelectBalls()
{
	for (int i = 0; i < this->balls.size(); i++)
	{
		switch (this->balls[i].indexColor)
		{
		case 0:
			this->redBalls++;
			break;
		case 1:
			this->blueBalls++;
			break;
		case 2:
			this->yellowBalls++;
			break;
		case 3:
			this->whiteBalls++;
			break;
		case 4:
			this->blackBalls++;
			break;
		}
	}

	std::cout << "Red Balls: " << this->redBalls <<
		", Blue Balls: " << this->blueBalls <<
		", Yellow Balls: " << this->yellowBalls <<
		", White Balls: " << this->whiteBalls <<
		", Black Balls: " << this->blackBalls << std::endl;

	//create an array to save number of ball for each color
	int arrayColorsAux[5];
	arrayColorsAux[0] = redBalls;
	arrayColorsAux[1] = blueBalls;
	arrayColorsAux[2] = yellowBalls;
	arrayColorsAux[3] = whiteBalls;
	arrayColorsAux[4] = blackBalls;

	//search for win color
	for (int i = 0; i < 5; i++)
	{
		if (arrayColorsAux[i] == this->auxWinBet)
		{
			//save the draw color
			this->drawBet = this->indexAuxBet;
		}
		//choose higher number
		else if (arrayColorsAux[i] > this->auxWinBet)
		{
			//change is is higher 
			this->auxWinBet = arrayColorsAux[i];
			//set indexColor
			this->indexAuxBet = i;
		}
	}
	//check if bet got any color with same balls
	if (this->indexAuxBet != drawBet)
		return this->indexAuxBet;
	else
		return 5;
}
/* ChoosePlayerBet()
* action: function to choose a random number to be a winner
* input:
* output:return the number that will be winner
* algorithm: generate a random number between 0 and 4 and save it in a variable
*/
int Game::ChoosePlayerBet()
{
	//Generate a random number between 0 and 4
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->winColor = std::rand() % 5;

	std::cout << "Player bet: " << this->winColor << std::endl;

	return this->winColor;
}

/* WinBet()
* action: function to check if the color chosen to win was the one that came out the most times
* input:
* output: return the gamestate. 0 - draw; 1 - win; 2 - lose
* algorithm: Call SelectBalls() to select which ball came out more times
* call ChoosePlayerBet() to choose player's bet
* change gameState taking into account received values
*/
int Game::WinBet()
{
	//get the highest value
	this->auxWinBet = this->SelectBalls();

	//generate a win color
	this->winBet = this->ChoosePlayerBet();

	//check if the game is a draw
	if (this->auxWinBet == 5)
	{
		this->gameState = 0;
		return this->gameState;
	}
	//check if player win or lose
	else
	{
		//Win
		if (this->winBet == auxWinBet)
		{
			this->gameState = 1;
			std::cout << "Win Bet: " << this->auxWinBet << std::endl;
			return this->gameState;
		}
		//Lose
		else
		{
			this->gameState = 2;
			std::cout << "Win Bet: " << this->auxWinBet << std::endl;
			return this->gameState;
		}
	}
}
/* WinLose()
* action: function to distribute rewards depending on the result
* input:
* output:
* algorithm: It receives an integer from the Win Bet function that will say if it is a draw, victory or defeat
* give rewards to the player and change UI to gives him feedback
*/
void Game::WinLose()
{
	//check if was Win or Lose
	int winLose = this->WinBet();

	switch (winLose)
	{
	case 0:
		//Draw
		//Change color of balance to yellow
		this->textBLC.setFillColor(sf::Color(225, 225, 0));
		//Return the bet
		balance += this->creditsIn;
		this->creditsIn = 0;
		std::cout << "Draw" << std::endl;
		break;

	case 1:
		//Win
		//Change color of balance and withdraw to green
		this->textBLC.setFillColor(sf::Color(0, 225, 0));
		this->textCOUT.setFillColor(sf::Color(0, 225, 0));

		//Multiply the bet * 3
		this->creditsOut = this->creditsIn * 3;
		std::cout << "Player wins: " << this->creditsOut << std::endl;
		break;

	case 2:
		//Lose
		//Change color of balance to red
		this->textBLC.setFillColor(sf::Color(225, 0, 0));
		//Remove Bet
		std::cout << "Player loses: " << this->creditsIn << std::endl;
		this->creditsIn -= this->creditsIn;
		break;
	}
}


/* ResetGui()
* action: function to reset UI colors that gives feedback to player
* input:
* output:
* algorithm: set ui to initial values
*/
void Game::ResetGui()
{
	//Reset UI
	this->startButton->ChangeButtonColor(sf::Color(0, 25, 0, 180),
		sf::Color(0, 25, 0, 200),
		sf::Color(0, 25, 0, 255));
	this->textBLC.setFillColor(sf::Color(0, 20, 0));
	this->textCOUT.setFillColor(sf::Color(0, 20, 0));
}

/* UpdateGui()
* action: function to update UI
* input:
* output:
* algorithm: show ui on screen
*/
void Game::UpdateGui()
{
	std::stringstream ballsPlayed;
	std::stringstream creditsIn;
	std::stringstream creditsOut;
	std::stringstream balance;
	std::stringstream betsPlayed;
	std::stringstream winLose;

	//BallsPlayed
	ballsPlayed << "Balls played: " << this->totalBalls;
	this->textBP.setString(ballsPlayed.str());

	//CreditsIN
	creditsIn << "Bet: " << this->creditsIn;
	this->textCIN.setString(creditsIn.str());

	//CreditsOUT
	creditsOut << "Withdraw: " << this->creditsOut;
	this->textCOUT.setString(creditsOut.str());

	//Balance
	balance << "Balance: " << this->balance;
	this->textBLC.setString(balance.str());

	//BetsPlayed
	betsPlayed << "Bets: " << this->betsPlayed;
	this->textBETS.setString(betsPlayed.str());
}

/* UpdateInfos()
* action: function to update infos from UI and distribuite profits
* input:
* output:
* algorithm: call WinLose bet to distribuite rewards, reset the infos, clear the vector , add one to the bets and reset play button
*/
void Game::UpdateInfos()
{
	//this->SelectBalls();

	//distribute profits
	WinLose();

	//clear the vector for new bet
	this->balls.clear();

	//clear necessary infos
	this->creditsIn = 0;
	this->redBalls = 0;
	this->blueBalls = 0;
	this->yellowBalls = 0;
	this->whiteBalls = 0;
	this->blackBalls = 0;
	this->totalBalls = 0;

	//finish one bet
	this->betsPlayed += 1;

	//set start button for idle pos
	this->startButton->wasPressed = false;
}

/* UpdateBalls()
* action: function to update balls
* input:
* output:
* algorithm: call the function on class Ball that moves the ball on screen
*/

void Game::UpdateBalls()
{
	for (int i = 0; i < this->balls.size(); i++)
	{
		this->balls[i].UpdateBall(0.5f, 0.0f);
	}
}

/* UpdateButtons()
* action: function to update buttons
* input:
* output:
* algorithm: call the function on class Button that updates Buttons
* check if the buttons were pressed
* if yes, it performs an action depending on the button pressed
*/
void Game::UpdateButtons()
{
	this->startButton->UpdateButton(*this->window, this->event, this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
	this->creditsInButton->UpdateButton(*this->window, this->event, this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
	this->creditsOutButton->UpdateButton(*this->window, this->event, this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
	this->closeGameButton->UpdateButton(*this->window, this->event, this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));

	//Start Button
	if (this->startButton->isPressed() == true && this->creditsIn <= 0)
		this->startButton->wasPressed = false;
	else if (this->creditsIn > 0)
	{
		this->startButton->ChangeButtonColor(sf::Color(0, 150, 0, 180),
			sf::Color(0, 150, 0, 200),
			sf::Color(0, 150, 0, 255));

		if (this->startButton->isPressed() == true)
		{
			//remove 1 from balance
			if (this->delay.getElapsedTime().asSeconds() >= 0.5f && this->balls.size() == 0)
			{
				this->balance -= 1;
			}
			this->delay.restart();

			//UpdateBalls
			this->UpdateBalls();
			this->SpawnBalls();
			//Reset UI
			this->ResetGui();
			//delay to make sure that player just add a credit for each click
			if (this->balls.size() == 50)
			{
				this->UpdateInfos();
			}
		}
	}


	//CreditsIN Button
	//Add credits to player's bet removing from balance
	if (this->creditsInButton->isPressed() == true && this->startButton->isPressed() == false)
	{
		//delay to make sure that player just add a credit for each click
		if (this->delay.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->balance -= 1;
			this->creditsIn += 1;
		}
		this->delay.restart();
		this->creditsInButton->wasPressed = false;
	}

	//CreditsOut Button
	//Remove the credits from creditsOut and add to player's balance
	if (this->creditsOutButton->isPressed() == true && this->startButton->wasPressed == false)
	{
		if (this->delay.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->balance += this->creditsOut;
			this->creditsOut = 0;
		}

		this->delay.restart();
		this->creditsOutButton->wasPressed = false;
	}

	//Close Game
	if (this->closeGameButton->isPressed() == true)
	{
		this->window->close();
	}
}

/* Update()
* action: main update
* input:
* output:
* algorithm: call necessarys updates
*/
void Game::Update()
{
	this->PollEvents();

	this->UpdateButtons();
	this->UpdateGui();
}

/* RenderGui()
* action: render game UI
* input: receive a target for rendering operations
* output:
* algorithm: Render texts on screen
*/
void Game::RenderGui(sf::RenderTarget* target)
{
	window->draw(background);
	target->draw(this->textBP);
	target->draw(this->textCIN);
	target->draw(this->textCOUT);
	target->draw(this->textBLC);
	target->draw(this->textBETS);
}

/* RenderButtons()
* action: render game buttons
* input: receive a target for rendering operations
* output:
* algorithm: Render texts on screen
*/
void Game::RenderButtons(sf::RenderTarget* target)
{
	this->startButton->RenderButton(target);
	this->creditsInButton->RenderButton(target);
	this->creditsOutButton->RenderButton(target);
	this->closeGameButton->RenderButton(target);
}

/* RenderButtons()
* action: main render
* input:
* output:
* algorithm: call Render Functions
* if startButton was press, Render Balls
*/
void Game::Render()
{
	//Draw UI
	this->RenderGui(this->window);

	//Draw Buttons
	this->RenderButtons(this->window);

	//just draw if the player set credits to bet
	if (this->startButton->isPressed() == true && this->creditsIn <= 0)
		this->startButton->wasPressed = false;
	else if (this->startButton->isPressed() == true && this->creditsIn > 0)
	{
		//Draw a game objects
		for (auto i : this->balls)
		{
			i.RenderBall(*this->window);
		}
	}
	//Display the scene
	this->window->display();
}




