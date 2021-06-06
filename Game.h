//
// Created by Bartosz Włodarski on 06/06/2021.
//

#ifndef AGARIO_GAME_H
#define AGARIO_GAME_H



#include <SFML/Graphics.hpp>
#include "Player.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Highscore.h"
#include "Menu.h"
#include "Result.h"

#define BORDER_WIDTH 10000
#define BORDER_HEIGHT 10000
#define START_DOTS_COUNT 500
#define DOT_SIZE 10
#define FRAME_STOP 100
#define BOTS_COUNT 10

class Game{
private:
    int width;
    int height;
    static int borderWidth;
    static int borderHeight;
    std::vector<Dot> dots;
    std::vector<Player> bots;
    Player player;
    Highscore highscore;
    Menu menu;
    bool menuOpen;
public:
    sf::RenderWindow window;
    Game(int width, int height);
    void drawDots();
    static void repairPos(float &x, float &y, float size);

    void run();
    void collisions();
    void addRandomDot();
    void simulateBots();
    void drawPlayers();
    void endGame(bool isWin);

};



#endif //AGARIO_GAME_H
