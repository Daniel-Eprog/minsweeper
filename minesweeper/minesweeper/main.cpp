#include <iostream>
#include <fstream>
#include <vector>
#include "gameboard.h"

using namespace std;

//void recursiveReveal(GameTile nextTile);

int main()
{

    //Declare board dimensions to be taken from config file
    string boardWidth;
    string boardHeight;
    string numMines;
    //Declare and open config file to set board dimensions
    ifstream gameConfig;
    gameConfig.open("boards/config.cfg");
    if (!gameConfig.is_open())
    {
        cout << "Sorry there was trouble opening your file" << endl;
    }
    gameConfig >> boardWidth;
    gameConfig >> boardHeight;
    gameConfig >> numMines;

    //Open window with correct board dimensions
    sf::RenderWindow window(sf::VideoMode(stoi(boardWidth) * 32, (stoi(boardHeight) * 32) + 100), "Minesweeper");
    //Create Game Board
    GameBoard newGameBoard = GameBoard(stoi(boardWidth), stoi(boardHeight), stoi(numMines));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //checks for left mouse click
            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                //iterates over sprites and finds one with matching position of mouse
                for (int i = 0; i < newGameBoard.getHeight() * newGameBoard.getWidth(); i++)
                {
                    auto mousePos = sf::Mouse::getPosition(window); // Mouse position relative to the window
                    auto translatedPos = window.mapPixelToCoords(mousePos);
                    sf::Sprite clickedTileSprite = newGameBoard.getGameTile(i)->getHidden();
                    if (clickedTileSprite.getGlobalBounds().contains(translatedPos) && !newGameBoard.getGameTile(i)->isFlagged() && newGameBoard.getGameTile(i)->isHidden() && newGameBoard.playing())
                    {
                        GameTile* clickedTile = newGameBoard.getGameTile(i);
                        newGameBoard.recursiveReveal(clickedTile);
                    }
                    else if (newGameBoard.getDebug().getGlobalBounds().contains(translatedPos) && newGameBoard.playing())
                    {
                        newGameBoard.isDebugged();
                        break;
                    }
                    else if (newGameBoard.getFace().getGlobalBounds().contains(translatedPos))
                    {
                        newGameBoard.resetGameBoard();
                        break;
                    }
                    else if (newGameBoard.getTest1().getGlobalBounds().contains(translatedPos))
                    {
                        newGameBoard.loadTest1();
                        break;
                    }
                    else if (newGameBoard.getTest2().getGlobalBounds().contains(translatedPos))
                    {
                        newGameBoard.loadTest2();
                        break;
                    }
                    else if (newGameBoard.getTest3().getGlobalBounds().contains(translatedPos))
                    {
                        newGameBoard.loadTest3();
                        break;
                    }
                }

            }
            //checks for right mouse click
            else if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
            {
                for (int i = 0; i < newGameBoard.getHeight() * newGameBoard.getWidth(); i++)
                {
                    auto mousePos = sf::Mouse::getPosition(window); // Mouse position relative to the window
                    auto translatedPos = window.mapPixelToCoords(mousePos);
                    if (newGameBoard.getGameTile(i)->getHidden().getGlobalBounds().contains(translatedPos) && newGameBoard.getGameTile(i)->isHidden() &&newGameBoard.playing())
                    {
                        if (newGameBoard.getGameTile(i)->isFlagged())
                        {
                            newGameBoard.incrementMineCount();
                        }
                        else
                        {
                            newGameBoard.decrementMineCount();
                        }
                        newGameBoard.getGameTile(i)->tileFlag();
                    }
                }
            }
        }

        /// RENDERING GAME WINDOW AND TILES ///

        window.clear(sf::Color(255, 255, 255, 255)); //clears screen between frames with specified color 
        newGameBoard.drawGameBoard(window);
        newGameBoard.setMineCounter();
        newGameBoard.checkWinConditions();
        window.display();
    }

	return 0;

}

/*
void recursiveReveal(GameTile nextTile, GameBoard gameBoard)
{
    for (int i = 0; i < gameBoard.getBoardTiles( ).size(); i++)
    {

        for (int j = 0; j < 8 < j++)
        {
            if (nextTile.getNeighbors(j) == )
        }
    }

}
*/