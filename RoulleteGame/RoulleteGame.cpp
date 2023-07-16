#include <iostream>

#include "Game.h"
#include "Ball.h"
#include "Button.h"


int main()
{
    //initialize random seed
    srand(static_cast<unsigned>(time(0)));

    //Init Game Engine
    Game game;

    //Play music
    sf::Music music;

    if (!music.openFromFile("Sound/GameSound.wav"))
    {
        std::cout << "Error loading music" << std::endl;
    }
    music.play();
    music.setVolume(50.0f);
    music.setLoop(true);

    //Game Loop
    while (game.Running())
    {

        //Update
        game.Update();
        //Render
        game.Render();
    }

    return 0;
}