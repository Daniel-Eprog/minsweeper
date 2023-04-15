#include "gameboard.h"

using namespace std;

GameBoard::GameBoard(int gameBoardWidth, int gameBoardHeight, int mines)
{
	float initialX = 0.0f;
	float initialY = 0.0f;

	width = gameBoardWidth;
	height = gameBoardHeight;
	numberMines = mines;
	originalNumberMines = mines;
	
	//creates game tiles and sets positions
	for (int i = 0; i < height * width; i++)
	{
		if (i % width == 0 && i != 0)
		{
			initialY += 32.0f;
			initialX = 0.0f;
		}
		GameTile* nextTile = new GameTile(initialX, initialY);
		boardTiles.push_back(nextTile);
		initialX += 32.0f;
	}



	//sets random distribution of mines
	this->setMines(mines);
	this->findNeighbors();
	//sets neighboring mines count
	this->setNeighbors();
	//loads digit texturs for mine count
	this->loadDigits();

	this->loadFaces();

	for (int i = 0; i < 3; i++)
	{
		sf::Sprite* nextSprite = new sf::Sprite();
		nextSprite->setTexture(*this->digits.at(0));
		nextSprite->setPosition(21.0f + i * 21.0f, (static_cast<float>(height) * 32));
		this->mineCounter.push_back(nextSprite);
	}

	this->negativeCounter.setTexture(*this->digits.at(10));
	this->negativeCounter.setPosition(0.0f, (static_cast<float>(height) * 32));
	this->debugger.loadFromFile("images/debug.png");
	this->test_1.loadFromFile("images/test_1.png");
	this->test_2.loadFromFile("images/test_2.png");
	this->test_3.loadFromFile("images/test_3.png");
	this->debug.setTexture(debugger);
	this->test1.setTexture(test_1);
	this->test2.setTexture(test_2);
	this->test3.setTexture(test_3);
	this->gameFace.setTexture(*this->faces.at(0));
	gameFace.setPosition((static_cast<float>(width) * 32) / 2 - 32, (static_cast<float>(height) * 32));
	debug.setPosition((static_cast<float>(width) * 32) / 2 - 32 + 128, static_cast<float>(height) * 32);
	test1.setPosition((static_cast<float>(width) * 32) / 2 - 32 + 192, static_cast<float>(height) * 32);
	test2.setPosition((static_cast<float>(width) * 32) / 2 - 32 + 256, static_cast<float>(height) * 32);
	test3.setPosition((static_cast<float>(width) * 32) / 2 - 32 + 320, static_cast<float>(height) * 32);

}

//returns width of the board
int GameBoard::getWidth()
{
	return this->width;
}

//returns height of the board
int GameBoard::getHeight()
{
	return this->height;
}

//returns gametile based on position
GameTile* GameBoard::getGameTile(int position)
{
	try
	{
		return this->boardTiles.at(position);
	}
	catch (std::out_of_range& e)
	{
		return nullptr;
	}
}

//////////////////*INITIAL SETUP METHODS*//////////////////

//sets position of all mines at random
void GameBoard::setMines(int numMines)
{
	srand(time(NULL));
	int minesToSet = numMines;
	while(minesToSet > 0)
	{
		GameTile* placeMine = this->getGameTile(rand() % this->boardTiles.size());
		if (placeMine->hasMine())
		{
			continue;
		}
		else
		{
			placeMine->setMine();
			minesToSet -= 1;
		}
		
	}
}

void GameBoard::findNeighbors()
{
	for (int i = 0; i < this->boardTiles.size(); i++)
	{
		int left = i - 1;
		int leftTop = (i - this->width) - 1;
		int top = i - this->width;
		int rightTop = (i - this->width) + 1;
		int right = i + 1;
		int bottomRight = (i + this->width) + 1;
		int bottom = i + this->width;
		int bottomLeft = (i + this->width) - 1;
	
		if ((i % this->width) == this->width - 1)
		{
			this->getGameTile(i)->setNeighbors(this->getGameTile(top));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottom));
			this->getGameTile(i)->setNeighbors(this->getGameTile(left));
			this->getGameTile(i)->setNeighbors(this->getGameTile(leftTop));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottomLeft));
			this->getGameTile(i)->setNeighbors(nullptr);
			this->getGameTile(i)->setNeighbors(nullptr);
			this->getGameTile(i)->setNeighbors(nullptr);
		}
		else if (i % this->width == 0)
		{
			this->getGameTile(i)->setNeighbors(this->getGameTile(top));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottom));
			this->getGameTile(i)->setNeighbors(this->getGameTile(rightTop));
			this->getGameTile(i)->setNeighbors(this->getGameTile(right));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottomRight));
			this->getGameTile(i)->setNeighbors(nullptr);
			this->getGameTile(i)->setNeighbors(nullptr);
			this->getGameTile(i)->setNeighbors(nullptr);
		}
		else
		{
			this->getGameTile(i)->setNeighbors(this->getGameTile(top));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottom));
			this->getGameTile(i)->setNeighbors(this->getGameTile(rightTop));
			this->getGameTile(i)->setNeighbors(this->getGameTile(right));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottomRight));
			this->getGameTile(i)->setNeighbors(this->getGameTile(left));
			this->getGameTile(i)->setNeighbors(this->getGameTile(leftTop));
			this->getGameTile(i)->setNeighbors(this->getGameTile(bottomLeft));

		}
		
	}
}

//sets neighboring mine count for all game tiles
void GameBoard::setNeighbors()
{
	for (int i = 0; i < this->height * this->width; i++)
	{
		int mineCount = 0;
		GameTile* nextTile = this->getGameTile(i);
		//resets mine count to zero for saftey
		nextTile->setAdjacentMineCount(0);
		if (nextTile->hasMine())
		{
			continue;
		}
		else
		{
			for (int j = 0; j < nextTile->getNeighborVector().size(); j++)
			{
				if (nextTile->getNeighbors(j) == nullptr)
				{
					continue;
				}
				else if (nextTile->getNeighbors(j)->hasMine())
				{
					mineCount += 1;
				}
			}
			nextTile->setAdjacentMineCount(mineCount);
		}
	}
}


//loads digits into vector of textures upon object construction
void GameBoard::loadDigits()
{
	int coordinates = 0;
	for (int i = 0; i < 11; i++)
	{
		sf::Texture* digitTexture = new sf::Texture;
		digitTexture->loadFromFile("images/digits.png", sf::IntRect(coordinates, 0, 21, 32));
		this->digits.push_back(digitTexture);
		coordinates += 21;
	}

}

void GameBoard::loadFaces()
{
	vector<string> facePNG = { "happy", "lose", "win" };
	for (int i = 0; i < 3; i++)
	{
		sf::Texture* nextTexture = new sf::Texture;
		nextTexture->loadFromFile("images/face_" + facePNG.at(i) + ".png");
		this->faces.push_back(nextTexture);
	}
}

//////////////*UI BUTTON FUNCTIONALITY*////////////////////
vector<GameTile*> GameBoard::getBoardTiles()
{
	return this->boardTiles;
}

void GameBoard::drawGameBoard(sf::RenderWindow& gameWindow)
{
	//Iterates through game board tiles and draws them to the screen
	for (int i = 0; i < this->boardTiles.size(); i++)
	{
		//Draws individal tile textures to screen
		if (this->getGameTile(i)->isHidden())
		{
			gameWindow.draw(this->getGameTile(i)->getHidden());
		}
		else
		{
			gameWindow.draw(this->getGameTile(i)->getRevealed());
			gameWindow.draw(this->getGameTile(i)->getNeighbor());
		}
		if (this->getGameTile(i)->isFlagged())
		{
			gameWindow.draw(this->getGameTile(i)->getFlag());
		}
		if (this->getGameTile(i)->hasMine() && this->debugged)
		{
			gameWindow.draw(this->getGameTile(i)->getMine());
		}
		if (this->stillPlaying == false && this->getGameTile(i)->hasMine() && win)
		{
			gameWindow.draw(this->getGameTile(i)->getFlag());
			
		}
		if (this->stillPlaying == false && this->getGameTile(i)->hasMine() && loss)
		{
			gameWindow.draw(this->getGameTile(i)->getRevealed());
			gameWindow.draw(this->getGameTile(i)->getMine());

		}
		
	}

	for (int i = 0; i < this->mineCounter.size(); i++)
	{
		gameWindow.draw(*this->mineCounter.at(i));
	}

	if (this->numberMines < 0)
	{
		gameWindow.draw(this->negativeCounter);
	}

	gameWindow.draw(this->gameFace);
	gameWindow.draw(this->debug);
	gameWindow.draw(this->test1);
	gameWindow.draw(this->test2);
	gameWindow.draw(this->test3);

}

void GameBoard::checkWinConditions()
{
	int revealedTiles = 0;
	for (int i = 0; i < this->boardTiles.size(); i++)
	{
		GameTile* nextTile = this->getGameTile(i);
		if (!nextTile->isHidden())
		{
			revealedTiles += 1;
		}
	}
	if (revealedTiles == (this->boardTiles.size() - this->numberMines))
	{
		this->setVictory();
	}

}

sf::Sprite GameBoard::getDebug()
{
	return this->debug;
}

sf::Sprite GameBoard::getFace()
{
	return this->gameFace;

}

void GameBoard::isDebugged()
{
	this->debugged = !this->debugged;
}

void GameBoard::removeMines()
{
	for (int i = 0; i < this->boardTiles.size(); i++)
	{
		if (this->getGameTile(i)->hasMine())
		{
			this->getGameTile(i)->unsetMine();
			this->getGameTile(i)->setHiddenTexture();
		}
	}
}

void GameBoard::resetHidden()
{
	for (int i = 0; i < this->boardTiles.size(); i++)
	{
		this->getGameTile(i)->setHiddenTexture();
		if (this->getGameTile(i)->isFlagged())
		{
			this->getGameTile(i)->tileFlag();
		}
	}

	
}

void GameBoard::resetGameBoard()
{
	this->resetHidden();
	this->removeMines();
	this->setMines(this->originalNumberMines);
	this->numberMines = this->originalNumberMines;
	this->setNeighbors();
	this->gameFace.setTexture(*faces.at(0));
	this->stillPlaying = true;
}

void GameBoard::recursiveReveal(GameTile* reveal)
{
	vector<GameTile*> noneAdjacent;

	if (reveal->hasMine())
	{
		this->setLoss();
		reveal->tileReveal();
	}
	else
	{
		reveal->tileReveal();
		for (int j = 0; j < reveal->getNeighborVector().size(); j++)
		{
			if (reveal->getNeighbors(j) != nullptr)
			{
				if (!reveal->getNeighbors(j)->hasMine() && reveal->getNeighbors(j)->getAdjacentMineCount() == 0 && reveal->getNeighbors(j)->isHidden())
				{
					noneAdjacent.push_back(reveal->getNeighbors(j));
				}
				else if (!reveal->getNeighbors(j)->hasMine() && !reveal->getNeighbors(j)->isFlagged() && reveal->getNeighbors(j)->isHidden())
				{
					reveal->getNeighbors(j)->tileReveal();
				}
				
			}
			else
			{
				continue;
			}
		}
		for (int i = 0; i < noneAdjacent.size(); i++)
		{
			this->recursiveReveal(noneAdjacent.at(i));
		}
	}
}

void GameBoard::setVictory()
{
	this->win = true;
	this->stillPlaying = false;
	this->gameFace.setTexture(*faces.at(2));
	this->numberMines = 0;
}

void GameBoard::setLoss()
{
	this->loss = true;
	this->stillPlaying = false;
	this->gameFace.setTexture(*faces.at(1));

}

//LOAD AND RETRIEVE TEST BOARDS
void GameBoard::loadTest1()
{
	this->numberMines = 0;
	this->resetHidden();
	this->removeMines();
	string gameBoard;
	string tempRow;
	ifstream testFile;
	testFile.open("boards/testboard1.brd");
	if (!testFile.is_open())
	{
		cout << "Sorry could not open file" << endl;
	}
	while (!testFile.eof())
	{
		testFile >> tempRow;
		gameBoard += tempRow;
	}
	for (int i = 0; i < gameBoard.length(); i++)
	{
		if (gameBoard[i] == '1')
		{
			this->getGameTile(i)->setMine();
			this->numberMines += 1;
		}

	}
	this->setNeighbors();
	this->gameFace.setTexture(*faces.at(0));
	this->stillPlaying = true;

}

void GameBoard::loadTest2()
{
	this->numberMines = 0;
	this->resetHidden();
	this->removeMines();
	string gameBoard;
	string tempRow;
	ifstream testFile;
	testFile.open("boards/testboard2.brd");
	if (!testFile.is_open())
	{
		cout << "Sorry could not open file" << endl;
	}
	while (!testFile.eof())
	{
		testFile >> tempRow;
		gameBoard += tempRow;
	}
	for (int i = 0; i < gameBoard.length(); i++)
	{
		if (gameBoard[i] == '1')
		{
			this->getGameTile(i)->setMine();
			this->numberMines += 1;
		}

	}
	this->setNeighbors();
	this->gameFace.setTexture(*faces.at(0));
	this->stillPlaying = true;

}

void GameBoard::loadTest3()
{
	this->numberMines = 0;
	this->resetHidden();
	this->removeMines();
	string gameBoard;
	string tempRow;
	ifstream testFile;
	testFile.open("boards/testboard3.brd");
	if (!testFile.is_open())
	{
		cout << "Sorry could not open file" << endl;
	}
	while (!testFile.eof())
	{
		testFile >> tempRow;
		gameBoard += tempRow;
	}
	for (int i = 0; i < gameBoard.length(); i++)
	{
		if (gameBoard[i] == '1')
		{
			this->getGameTile(i)->setMine();
			this->numberMines += 1;
		}

	}
	this->setNeighbors();
	this->gameFace.setTexture(*faces.at(0));
	this->stillPlaying = true;
}

sf::Sprite GameBoard::getTest1()
{
	return this->test1;
}

sf::Sprite GameBoard::getTest2()
{
	return this->test2;
}

sf::Sprite GameBoard::getTest3()
{
	return this->test3;
}

bool GameBoard::playing()
{
	return this->stillPlaying;
}

void GameBoard::setMineCounter()
{
	
	string minesToString = to_string(this->numberMines);

	if (this->numberMines < 0)
	{
		while (minesToString.length() < 4)
		{
			minesToString.insert(1, "0");
		}
		for (int i = 1; i < minesToString.length(); i++)
		{
			this->mineCounter.at(i - 1)->setTexture(*this->digits.at(stoi(string(1, minesToString.at(i)))));
		}
	}
	else
	{
		while (minesToString.length() < 3)
		{
			minesToString.insert(0, "0");
		}
		for (int i = 0; i < minesToString.length(); i++)
		{
			this->mineCounter.at(i)->setTexture(*this->digits.at(stoi(string(1, minesToString.at(i)))));
		}
	}
	/*
	else
	{
		for (int i = 0; i < minesToString.length(); i++)
		{
			this->mineCounter.at(mineCounter.size() - minesToString.length() + i)->setTexture(*this->digits.at(stoi(minesToString.substr(i, i + 1))));
		}
	}
	*/
	
}

void GameBoard::decrementMineCount()
{
	this->numberMines -= 1;
}

void GameBoard::incrementMineCount()
{
	this->numberMines += 1;

}
