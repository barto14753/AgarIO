//
// Created by Bartosz Włodarski on 06/06/2021.
//

#ifndef AGARIO_RESULT_H
#define AGARIO_RESULT_H


#include <SFML/Graphics.hpp>

class Result {
private:
    sf::Text title;
    sf::Text result;
    sf::Text callToAction;
    sf::Font font;

public:
    Result(std::string message, int score);
    int renderResult(sf::RenderWindow& window);
};



#endif //AGARIO_RESULT_H
