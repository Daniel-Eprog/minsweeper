#include "gametile.h"

GameTile::GameTile(float Xpos, float Ypos)
{
	this->hideTile.loadFromFile("images/tile_hidden.png");
	this->mine.loadFromFile("images/mine.png");
	this->flag.loadFromFile("images/flag.png");
	this->revealed.loadFromFile("images/tile_revealed.png");
	this->mineTile.setTexture(this->mine);
	this->flagTile.setTexture(this->flag);
	this->hiddenTile.setTexture(this->hideTile);
	this->revealedTile.setTexture(this->revealed);
	this->revealedTile.setPosition(Xpos, Ypos);
	this->hiddenTile.setPosition(Xpos, Ypos);
	this->mineTile.setPosition(Xpos, Ypos);
	this->flagTile.setPosition(Xpos, Ypos);
	this->numberNeighborsTile.setPosition(Xpos, Ypos);

}

void GameTile::tileFlag()
{
	this->flagged = !this->flagged;

}

void GameTile::tileReveal()
{
	this->hidden = false;
}

void GameTile::setMine()
{
	this->minePresent = true;
}

void GameTile::unsetMine()
{
	this->minePresent = false;
}

//boolean conidton methods
bool GameTile::isFlagged()
{
	return this->flagged;
}

bool GameTile::isHidden()
{
	return this->hidden;
}

bool GameTile::hasMine()
{
	if (this == nullptr)
	{
		return false;
	}
	else
	{
		return this->minePresent;
	}
}

//returns neighbor based on position
GameTile* GameTile::getNeighbors(int position)
{
	return this->neighbors.at(position);
}

vector<GameTile*> GameTile::getNeighborVector()
{
	return this->neighbors;
}

void GameTile::setAdjacentMineCount(int numMines)
{
	 this->adjacentMineCount = numMines;
	 if (numMines > 0)
	 {
		 this->numNeighbors.loadFromFile("images/number_" + to_string(numMines) + ".png");
		 this->numberNeighborsTile.setTexture(this->numNeighbors);
	 }
	 else
	 {
		 this->numberNeighborsTile.setTexture(this->revealed);
	 }
	 
	 

}

void GameTile::setHiddenTexture()
{
	this->hidden = true;
}

int GameTile::getAdjacentMineCount()
{
	return this->adjacentMineCount;
}

sf::Sprite GameTile::getFlag()
{
	return this->flagTile;
}

sf::Sprite GameTile::getMine()
{
	return this->mineTile;
}

sf::Sprite GameTile::getHidden()
{
	return this->hiddenTile;
}

sf::Sprite GameTile::getRevealed()
{
	return this->revealedTile;
}

sf::Sprite GameTile::getNeighbor()
{
	return this->numberNeighborsTile;
}

void GameTile::setNeighbors(GameTile* nextNeighbor)
{
		this->neighbors.push_back(nextNeighbor);
}

sf::Texture GameTile::setFlag()
{
	return this->flag;
}
