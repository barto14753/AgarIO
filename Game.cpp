//
// Created by Bartosz Włodarski on 06/06/2021.
//

#include "Game.h"


Game::Game(int width, int height) :
        width(width),
        height(height),
        window(sf::VideoMode(width,height,64), "Agar.io"),
        player(Player(2500,2500,"Player")),
        highscore(Highscore()),
        menu(Menu()),
        menuOpen(true)
{
    srand(time(nullptr));
    for(int i=0; i<START_DOTS_COUNT; i++)
    {
        addRandomDot();
    }

    bots.push_back(player);
    for(int i=0; i<BOTS_COUNT; i++)
    {
        bots.push_back(Player(rand() % borderWidth, rand() % borderHeight, "Bot " + std::to_string(i+1)));
    }
}

int randomSign()
{
    if(rand()%2 == 0) return 1;
    return -1;
}

void Game::run() {
    while (window.isOpen())
    {
        if(menuOpen)
        {
            if(menu.renderMenu(window) == 1) return;
            menuOpen = false;
        }

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.moveDown();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.moveRight();

        window.clear();
        simulateBots();
        collisions();
        drawPlayers();
        drawDots();
        window.draw(highscore.createHighscore(bots, player));
        window.display();
        sf::sleep(sf::microseconds(FRAME_STOP));

        GameResult result = isSomeoneWinner();
        if(bots.size() == 0 || result == WIN) endGame(WIN);
        else if(result == LOSS) endGame(LOSS);
    }

}

void Game::drawDots() {
    for(Dot dot: dots)
    {
        window.draw(dot.getShape(player.getPosX() - (width/2), player.getPosY() - (height/2)));
    }

}


int Game::borderWidth = BORDER_WIDTH;
int Game::borderHeight = BORDER_HEIGHT;

void Game::repairPos(float &x, float &y, float size) {
    if(x + size >= borderWidth) x = borderWidth- size;
    else if(x - size <= 0) x = size;

    if(y + size >= borderHeight) y = borderHeight - size;
    else if(y - size <= 0) y = size;

}

bool isCollision(Dot p, Dot d)
{
    float xDiff = p.getPosX() - d.getPosX();
    float yDiff = p.getPosY() - d.getPosY();
    float distance = sqrt(xDiff*xDiff + yDiff*yDiff);
    return distance <= p.getSize() + d.getSize();
}

void Game::collisions() {
    for(int i=0; i<dots.size(); i++)
    {
        if(isCollision(player, dots[i]))
        {
            player.addSize(dots[i]);
            dots.erase(dots.begin()+i);
            addRandomDot();
        }

        for(int j=0; j<bots.size(); j++)
        {
            if(isCollision(bots[j], dots[i]))
            {
                bots[j].addSize(dots[i]);
                dots.erase(dots.begin()+i);
                addRandomDot();
            }

        }

    }
    for(int i=0; i<bots.size(); i++)
    {
        if(isCollision(bots[i], player))
        {
            if(bots[i].getSize() > player.getSize())
            {
                bots[i].addSize(player);
                endGame(LOSS);

            }
            else if(bots[i].getSize() < player.getSize())
            {
                player.addSize(bots[i]);
                bots.erase(bots.begin()+i);

            }
        }
        for(int j=i+1; j<bots.size(); j++)
        {
            if(isCollision(bots[i], bots[j]))
            {
                if(bots[i].getSize() > bots[j].getSize())
                {
                    bots[i].addSize(bots[j]);
                    bots.erase(bots.begin()+j);

                }
                else if(bots[i].getSize() < bots[j].getSize())
                {
                    bots[j].addSize(bots[i]);
                    bots.erase(bots.begin()+i);

                }

            }

        }
    }

}

void Game::addRandomDot() {
    dots.push_back(Dot(rand() % borderWidth, rand() % borderHeight, DOT_SIZE));
}

void Game::simulateBots() {
    for(int i=1; i<bots.size(); i++)
    {
        bots[i].randomMove();
    }
}

void Game::drawPlayers() {
    window.draw(player.getShape(width, height));
    for(int i=1; i<bots.size(); i++)
    {
        window.draw(bots[i].getBotShape(player.getPosX() - (width/2), player.getPosY() - (height/2)));
    }
}

void Game::endGame(GameResult result) {

    if(result == WIN)
    {
        Result result("You won", player.getSize());
        result.renderResult(window);
    }
    else
    {
        Result result("You lost", player.getSize());
        result.renderResult(window);
    }

    menuOpen = true;
    bots.clear();
    dots.clear();
    srand(time(nullptr));
    player = Player(2500,2500,"Player");

    for(int i=0; i<START_DOTS_COUNT; i++)
    {
        addRandomDot();
    }

    bots.push_back(player);
    for(int i=0; i<BOTS_COUNT; i++)
    {
        bots.push_back(Player(rand() % borderWidth, rand() % borderHeight, "Bot " + std::to_string(i+1)));
    }

    return;

}

GameResult Game::isSomeoneWinner() {
    if(player.getSize() >= MAX_SIZE) return WIN;
    for(int i=1; i<bots.size(); i++)
    {
        if(bots[i].getSize() >= (MAX_SIZE)) return LOSS;
    }
    return UNKNOWN;
}

