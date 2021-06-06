//
// Created by Bartosz Włodarski on 06/06/2021.
//

#include "Dot.h"


Dot::Dot(float x, float y, float s=10) {
    this->posX = x;
    this->posY = y;
    this->size = s;
    this->color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
    this->dot.setRadius(size);
    this->dot.setPosition(x,y);
    this->dot.setFillColor(this->color);

}

void Dot::update() {
    this->dot.setRadius(this->size);
    this->dot.setPosition(this->posX, this->posY);
    this->dot.setFillColor(this->color);
}

sf::CircleShape Dot::getShape(float x, float y) {
    this->update();
    sf::CircleShape c(size);
    c.setFillColor(color);
    c.setPosition(posX - x, posY - y);
    c.setOrigin(size/2, size/2);

    return c;
}
