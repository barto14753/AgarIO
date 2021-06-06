//
// Created by Bartosz Włodarski on 06/06/2021.
//

#ifndef AGARIO_PLAYER_H
#define AGARIO_PLAYER_H


#include "Dot.h"


#define MAX_SPEED 10.0
#define INIT_SIZE 30.0
#define MAX_SIZE 600.0
#define GROWTH_RATE 1.0
#define MAX_MOVE_TICKS 100
#define MIN_MOVE_TICKS 10

enum Direction{UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT, LAST};

class Player : public Dot{
    std::string nick;
    Direction currentMove;
    int moveTicksLast;

public:
    Player(float x, float y, std::string nick) : Dot(x, y, INIT_SIZE),  nick(nick), moveTicksLast(0) {}

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void repairPos();
    sf::CircleShape getShape(float width, float hegiht);
    sf::CircleShape getBotShape(float x, float y);
    void addSize(Dot d);

    void randomMove(std::vector<Player> players, int index);
    void randomMove();
    void moveToDirection(Direction dir);

    std::string getNick() { return nick; };


};


#endif //AGARIO_PLAYER_H
