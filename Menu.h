//
// Created by Bartosz Włodarski on 06/06/2021.
//

#ifndef AGARIO_MENU_H
#define AGARIO_MENU_H


#include <SFML/Graphics.hpp>

enum Button{START, QUIT, NONE};

class Menu {
private:
    sf::Text title;
    sf::Text startButton;
    sf::Text quitButton;
    sf::Font font;
    Button currentButton;
public:
    Menu();
    int renderMenu(sf::RenderWindow& window);
    Button getButton(float x, float y);
};



#endif //AGARIO_MENU_H
