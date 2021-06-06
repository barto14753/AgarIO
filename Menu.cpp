//
// Created by Bartosz Włodarski on 06/06/2021.
//


#include "Menu.h"

int Menu::renderMenu(sf::RenderWindow &window) {

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i pos;

        while (window.pollEvent(event))
        {
            pos = sf::Mouse::getPosition(window);
            currentButton = getButton(pos.x, pos.y);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            switch(currentButton)
            {
                case START: return 0;
                case QUIT: return 1;
            }
        }

        window.clear();
        window.draw(title);
        window.draw(startButton);
        window.draw(quitButton);
        window.display();
    }

}

Menu::Menu() : currentButton(NONE) {
    font.loadFromFile("../font.ttf");

    title.setFont(font);
    startButton.setFont(font);
    quitButton.setFont(font);

    title.setCharacterSize(120);
    startButton.setCharacterSize(80);
    quitButton.setCharacterSize(80);

    title.setString("Agar.io");
    startButton.setString("Start");
    quitButton.setString("Quit");

    title.setFillColor(sf::Color::White);
    startButton.setFillColor(sf::Color::White);
    quitButton.setFillColor(sf::Color::White);

    title.setPosition(700,100);
    startButton.setPosition(800,500);
    quitButton.setPosition(815, 800);

}

Button Menu::getButton(float x, float y) {
    //f("GET (%f, %f)\n", x, y);
    float startX = x - startButton.getPosition().x;
    float startY = y - startButton.getPosition().y;
    float quitX = x - quitButton.getPosition().x;
    float quitY = y - quitButton.getPosition().y;

    if(startX > 0 && startY > 0 && startX < startButton.getGlobalBounds().width && startY < startButton.getGlobalBounds().height)
    {
        //printf("START\n");
        startButton.setFillColor(sf::Color::Red);
        quitButton.setFillColor(sf::Color::White);
        return START;
    }
    else if(quitX > 0 && quitY > 0 && quitX < quitButton.getGlobalBounds().width && quitY < quitButton.getGlobalBounds().height)
    {
        //printf("QUIT\n");
        startButton.setFillColor(sf::Color::White);
        quitButton.setFillColor(sf::Color::Red);
        return QUIT;
    }
    else
    {
        startButton.setFillColor(sf::Color::White);
        quitButton.setFillColor(sf::Color::White);
        return NONE;
    }
}

