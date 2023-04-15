#include "minecounter.h"

MineCounter::MineCounter()
{
	for (int i = 1; i < 9; i++) 
	{
		sf::Texture* numTexture = new sf::Texture;
		numTexture->loadFromFile("images/number_" + to_string(i) + ".png");
		this->mineCount.push_back(numTexture);
	}
}

sf::Texture* MineCounter::getMineCount(int numMines)
{
	return this->mineCount.at(numMines);
}

