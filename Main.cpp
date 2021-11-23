#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "ScoreList.h"

using namespace sf;
using namespace std;
#define w 1920
#define h 1080
#include "Game.hpp"

int main()
{
    ScoreList score_list("highscore.txt");
    score_list.loadFile();

    srand(time(0));

    Game game(&score_list);
    Music music;
    if (!music.openFromFile("Sound/opengame.wav"))
        cout << "error shoot" << endl;
    music.setVolume(50);
    music.setLoop(true);
    music.play();

    while (game.isRunning()) {

        game.processEvent();  
        game.update();   
        game.clearScreen();       
        game.drawScreen();
        game.displayScreen();
    }

    score_list.saveFile();
    return EXIT_SUCCESS;
}