#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class GameTile
{
    private:
        //boolean conditions for each tile
        int adjacentMineCount = 0;
        bool minePresent = false;
        bool hidden = true;
        bool flagged = false;
        //vector position of neighboring tiles
        vector<GameTile*> neighbors;
        //sprites and textures
        sf::Sprite hiddenTile;
        sf::Sprite mineTile;
        sf::Sprite flagTile;
        sf::Sprite revealedTile;
        sf::Sprite numberNeighborsTile;
        sf::Texture hideTile;
        sf::Texture mine;
        sf::Texture flag;
        sf::Texture revealed;
        sf::Texture numNeighbors;

    public:
        GameTile(float Xpos = 0.0f, float Ypos = 0.0f); //class constructor
        void tileReveal(); //turns the current texture of class sprite to revealed
        void tileFlag(); //turns the current texture of class sprite to flag and conditin to true
        void setMine(); //sets a mine at tile position
        void unsetMine(); 
        bool isFlagged(); //returns whether or not tile is flagged
        bool isHidden(); //returns whether or not tile is hidden
        bool hasMine(); //returns whether or not tile has mine
        GameTile* getNeighbors(int position); //returns vector position of neighboring tiles
        void setAdjacentMineCount(int numMines);//increments adjacent mine count
        void setNeighbors(GameTile* nextNeighbor);
        vector<GameTile*> getNeighborVector();
        int getAdjacentMineCount();
        void setHiddenTexture(); //sets hidden tile texture when debug is switched off
        sf::Sprite getFlag();
        sf::Sprite getMine();
        sf::Sprite getHidden();
        sf::Sprite getRevealed();
        sf::Sprite getNeighbor();
        sf::Texture setFlag();

};
