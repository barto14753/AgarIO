//
// Created by Bartosz Włodarski on 06/06/2021.
//

#ifndef AGARIO_DOT_H
#define AGARIO_DOT_H


#include <SFML/Graphics.hpp>

class Dot {
protected:
    float posX;
    float posY;
    float size;
    sf::Color color;
    sf::CircleShape dot;
public:
    Dot(float x, float y, float s);
    float getPosX() { return this->posX; }
    float getPosY() { return this->posY; }
    float getSize() { return this->size; };
    sf::CircleShape getShape(float x, float y);
    void update();
};


#endif //AGARIO_DOT_H
