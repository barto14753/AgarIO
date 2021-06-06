//
// Created by Bartosz Włodarski on 06/06/2021.
//


#include "Result.h"

Result::Result(std::string message, int score) {
    font.loadFromFile("../font.ttf");

    title.setFont(font);
    result.setFont(font);
    callToAction.setFont(font);

    title.setCharacterSize(120);
    result.setCharacterSize(80);
    callToAction.setCharacterSize(80);


    title.setString(message);
    result.setString("Score: " + std::to_string(score));
    callToAction.setString("Press Space");

    title.setFillColor(sf::Color::White);
    result.setFillColor(sf::Color::White);
    callToAction.setFillColor(sf::Color::White);

    title.setPosition(650,100);
    result.setPosition(715,500);
    callToAction.setPosition(675, 800);

}

int Result::renderResult(sf::RenderWindow &window) {

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                    return 0;
            }
        }

        window.clear();
        window.draw(title);
        window.draw(result);
        window.draw(callToAction);
        window.display();
    }


    return 0;
}


