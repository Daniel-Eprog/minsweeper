#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "gametile.h"

using namespace std;

class GameBoard
{
 
    private:
        int width;
        int height;
        int numberMines;
        int originalNumberMines;
        bool stillPlaying = true;
        bool win = false;
        bool loss = false;
        bool debugged = false;
        vector<GameTile*> boardTiles;
        //UI Tiles and Textures
        sf::Sprite gameFace;
        sf::Texture test_1;
        sf::Texture test_2;
        sf::Texture test_3;
        sf::Texture debugger;
        sf::Sprite debug;
        sf::Sprite test1;
        sf::Sprite test2;
        sf::Sprite test3;
        sf::Sprite negativeCounter;
        vector<sf::Sprite*> mineCounter;
        vector<sf::Texture*> faces;
        vector<sf::Texture*> digits;

    public:
        GameBoard(int gameBoardWidth, int gameBoardHeight, int mines); //construtor for gameboard
        sf::Sprite getTile(int tileLocation); //returns sprite of specified tile
        GameTile* getGameTile(int position); //returns a game tile based on position
        int getWidth(); //returns width of the game board
        int getHeight(); //returns height of the game board
        void setMines(int numMines); //distributes specified number of mines at random 
        void setNeighbors(); //sets adjacent mine counts
        vector<GameTile*> getBoardTiles(); //retunrs vector of game tiles
        void drawGameBoard(sf::RenderWindow& gameWindow); //draws game board to window
        sf::Sprite getDebug(); //returns debug button to check for clicks
        sf::Sprite getFace(); //returns face button to check for clicks
        sf::Sprite getTest1();
        sf::Sprite getTest2();
        sf::Sprite getTest3();
        void checkWinConditions(); //checks win conditions
        void loadDigits(); //loads digit textures into vector
        void loadFaces(); //loads face textures into vector
        void isDebugged(); //returns boolean to see if game board is in debug mode
        void removeMines(); //removes mines from the board
        void resetGameBoard();//resets the gameboard
        void resetHidden(); //resets all the tiles to hidden
        void recursiveReveal(GameTile* reveal);
        void findNeighbors();
        void loadTest1();
        void loadTest2();
        void loadTest3();
        void setVictory();
        void setLoss();
        bool playing();
        void setMineCounter();
        void decrementMineCount();
        void incrementMineCount();
        
};
