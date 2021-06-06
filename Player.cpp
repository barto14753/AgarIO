//
// Created by Bartosz Włodarski on 06/06/2021.
//


#include "Player.h"
#include "Game.h"

void Player::moveUp() {
    posY -= MAX_SPEED;
    this->repairPos();
}

void Player::moveDown() {
    posY += MAX_SPEED;
    this->repairPos();
}

void Player::moveLeft() {
    posX -= MAX_SPEED;
    this->repairPos();
}

void Player::moveRight() {
    posX += MAX_SPEED;
    this->repairPos();
}

void Player::repairPos() {
    Game::repairPos(this->posX, this->posY, this->size);

}

sf::CircleShape Player::getShape(float width, float height) {
    this->update();
    sf::CircleShape c(size);
    c.setFillColor(color);
    c.setOrigin(size, size);
    c.setPosition(width/2, height/2);

    return c;
}

void Player::addSize(Dot d) {
    size += d.getSize() * GROWTH_RATE;

}


float getTangens(Dot p, Dot d) {
    float xDiff = p.getPosX() - d.getPosX();
    float yDiff = p.getPosY() - d.getPosY();
    return yDiff/xDiff;

}

float distance(Player p, Player d) {
    float xDiff = p.getPosX() - d.getPosX();
    float yDiff = p.getPosY() - d.getPosY();
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}

Direction getDirection(Player p, Player d)
{
    float tangens = getTangens(p, d);
    if(tangens >= tan((-1/16)*2*M_PI) && tangens <= tan((1/16)*2*M_PI)) return RIGHT;
    else if(tangens >= tan((1/16)*2*M_PI) && tangens <= tan((3/16)*2*M_PI)) return UPRIGHT;
    else if(tangens >= tan((3/16)*2*M_PI) && tangens <= tan((5/16)*2*M_PI)) return UP;
    else if(tangens >= tan((5/16)*2*M_PI) && tangens <= tan((7/16)*2*M_PI)) return UPLEFT;
    else if(tangens >= tan((7/16)*2*M_PI) && tangens <= tan((9/16)*2*M_PI)) return LEFT;
    else if(tangens >= tan((9/16)*2*M_PI) && tangens <= tan((11/16)*2*M_PI)) return DOWNLEFT;
    else if(tangens >= tan((11/16)*2*M_PI) && tangens <= tan((13/16)*2*M_PI)) return DOWN;
    else if(tangens >= tan((13/16)*2*M_PI) && tangens <= tan((15/16)*2*M_PI)) return DOWNRIGHT;
    return UP;
}

Direction oppositeDirection(Direction dir)
{
    switch(dir)
    {
        case RIGHT: return LEFT;
        case UPRIGHT: return DOWNLEFT;
        case UP: return DOWN;
        case UPLEFT: return DOWNRIGHT;
        case LEFT: return RIGHT;
        case DOWNLEFT: return UPRIGHT;
        case DOWN: return UP;
        case DOWNRIGHT: return  UPLEFT;
    }
}


bool compareAscending(Player player, Player player1, Player player2)
{
    return distance(player, player1) < distance(player, player2);
}


//

void Player::moveToDirection(Direction dir) {
    switch(dir)
    {
        case RIGHT: {moveRight(); break;}
        case UPRIGHT: {moveUp(); moveRight(); break;}
        case UP: {moveUp(); break;}
        case UPLEFT: {moveUp(), moveLeft(); break;}
        case LEFT: {moveLeft(); break;}
        case DOWNLEFT: {moveDown(); moveLeft(); break;}
        case DOWN: {moveDown(); break;}
        case DOWNRIGHT: {moveDown(); moveRight(); break;}
    }
}

sf::CircleShape Player::getBotShape(float x, float y) {
    this->update();
    sf::CircleShape c(size);
    c.setFillColor(color);
    c.setPosition(posX - x, posY - y);
    c.setOrigin(size/2, size/2);

    return c;
}

Direction randomDirection()
{
    return Direction(rand() % LAST);
}

int randomTime()
{
    int r = rand() % (MAX_MOVE_TICKS - MIN_MOVE_TICKS);
    return r + MIN_MOVE_TICKS;
}
void Player::randomMove()
{
    printf("Making random move | %d\n", moveTicksLast);
    if(moveTicksLast <= 0)
    {
        currentMove = randomDirection();
        moveTicksLast = randomTime();
    }
    moveToDirection(currentMove);
    moveTicksLast--;
}




void Player::randomMove(std::vector<Player> players, int index) {
    std::vector<Player> weakerPlayers;
    int nearestStronger = index;
    for(int i=0; i<players.size(); i++)
    {
        if(i == index) continue;
        if(players[i].getSize() < this->getSize()) weakerPlayers.push_back(players[i]);
        if(players[i].getSize() >= players[nearestStronger].getSize()) nearestStronger = i;
    }
    //std::sort(weakerPlayers.begin(), weakerPlayers.end(), std::bind(compareAscending, this, std::placeholders::_1, std::placeholders::_2));


    if(nearestStronger != index)
    {
        Direction dangerDir = getDirection(*this, players[nearestStronger]);
        for(unsigned int i=0; i<weakerPlayers.size(); i++)
        {
            Direction playerDir = getDirection(*this, weakerPlayers[i]);
            if(playerDir == dangerDir)
            {
                weakerPlayers.erase(weakerPlayers.begin() + i);
                i--;
            }
            else
            {
                break;
            }
        }
        if(!weakerPlayers.empty())
        {
            Direction dir = getDirection(*this, weakerPlayers[0]);
            this->moveToDirection(dir);
        }
        else
        {
            this->moveToDirection(oppositeDirection(getDirection(*this, players[nearestStronger])));
        }
    }
    else
    {
        if(!weakerPlayers.empty()) this->moveToDirection(getDirection(*this, weakerPlayers[0]));
        else
        {
            return;
        }
    }
    //TODO - sorting weakerPlayers -> founding nearest danger -> deleting weakerPlayers with


}



