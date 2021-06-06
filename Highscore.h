//
// Created by Bartosz Włodarski on 06/06/2021.
//

#ifndef AGARIO_HIGHSCORE_H
#define AGARIO_HIGHSCORE_H


#include <SFML/Graphics.hpp>
#include "Player.h"

#define TOP_PLAYERS 5
#define POS_X 30.0
#define POS_Y 10.0

class Highscore {
private:
    sf::Font font;
public:
    Highscore();
    sf::Text createHighscore(std::vector<Player> players, Player player);
};



#endif //AGARIO_HIGHSCORE_H
