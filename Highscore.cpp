//
// Created by Bartosz Włodarski on 06/06/2021.
//


#include "Highscore.h"

bool compareInterval(Player p1, Player p2)
{
    return (p1.getSize() > p2.getSize());
}

sf::Text Highscore::createHighscore(std::vector<Player> players, Player player) {
    std::sort(players.begin(), players.end(), compareInterval);


    bool playerOut = true;
    std::string text = "Highscore:";
    for(int i=0; i<players.size() && i<TOP_PLAYERS; i++)
    {
        if(player.getSize() >= players[i].getSize() && playerOut)
        {
            playerOut = false;
            text += "\n  " + player.getNick() + " : " + std::to_string(player.getSize());
            if(i == players.size() - 1) break;
        }
        text += "\n  " + players[i].getNick() + " : " + std::to_string(players[i].getSize());
    }
    if(playerOut)
    {
        text += "\n " + player.getNick() + " : " + std::to_string(player.getSize());
    }

    sf::Text highscore;
    highscore.setFont(font);
    highscore.setCharacterSize(32);
    highscore.setString(text);
    highscore.setFillColor(sf::Color::White);
    highscore.setPosition(POS_X, POS_Y);


    return highscore;
}

Highscore::Highscore() {
    font.loadFromFile("../font.ttf");
}
