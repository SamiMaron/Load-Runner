#include "Board.h"

// Board C-tor
Board::Board()
{
	setImages();
	openNewLevel();
	srand((int)time(NULL));
	createStats();
}

//Set a new level
void Board::openNewLevel()
{
	m_level.createNewLevel();
	if (m_player!= NULL)
		m_player->updateLevel();
	clearAll();
	if (getLevelNum() != 5)
		buildObjects();
}

//Build objects from file
void Board::buildObjects()
{
	float scale_y = (float)WINDOWHEIGHT / (float)m_level.getHeight();
	float scale_x = (float)WINDOWWIDTH / (float)m_level.getWidth();
	float pos_x = 0, pos_y = 0;
	float player_x, player_y;
	char ch;
	for (int i = 0; i < m_level.getHeight(); i++)
	{
		for (int j = 0; j < m_level.getWidth(); j++)
		{
			ch = m_level.getChar(i, j);
			if (ch == player)
			{
				player_x = pos_x;
				player_y = pos_y;
			}
			buildObject(ch, pos_x, pos_y, scale_x, scale_y);
			pos_x += scale_x;
		}
		pos_x = 0;
		pos_y += scale_y;
	}
	setScales();
}

//build each object set a position and scales
void Board::buildObject(char ch, float pos_x, float pos_y, float scale_x, float scale_y)
{
	if (ch == player)
	{
		if(m_player == NULL)
			m_player = make_unique<Player>(m_images[1], pos_x, pos_y, scale_x, scale_y);
		else
		{
			int score = m_player->getScore();
			int life = m_player->getLife();
			int level = m_level.getNumLevel();
			m_player = make_unique<Player>(m_images[1], pos_x, pos_y, scale_x, scale_y);
			loadPlayerData(score, life, level);
		}
	}

	else if (ch == coin)
		m_eatable.push_back(make_unique<Coin>(m_images[0], pos_x, pos_y, scale_x, scale_y));

	else if (ch == wall)
		m_static.push_back(make_unique<Wall>(m_images[2], pos_x, pos_y, scale_x, scale_y));

	else if (ch == enemy)
	{
		int num = rand() % 3;
		if (num == 0)
			m_enemies.push_back(make_unique<SmartEnemy>(m_images[3], pos_x, pos_y, scale_x, scale_y));
		else if (num == 1)
			m_enemies.push_back(make_unique<CyclicEnemy>(m_images[3], pos_x, pos_y, scale_x, scale_y));
		else
			m_enemies.push_back(make_unique<RandomEnemy>(m_images[3], pos_x, pos_y, scale_x, scale_y));
	}


	else if (ch == ladder)
		m_static.push_back(make_unique<Ladder>(m_images[6], pos_x, pos_y, scale_x, scale_y));

	else if (ch == rope)
		m_static.push_back(make_unique<Rope>(m_images[4], pos_x, pos_y, scale_x, scale_y));

	else if (ch == presentw)
	{
		int num = rand() % 4;
		if (num == 0)
			m_eatable.push_back(make_unique<EnemyPresent>(m_images[9], pos_x, pos_y, scale_x, scale_y));
		else if (num == 1)
			m_eatable.push_back(make_unique<PointsPresent>(m_images[5], pos_x, pos_y, scale_x, scale_y));
		else if (num == 2)
			m_eatable.push_back(make_unique<LifePresent>(m_images[8], pos_x, pos_y, scale_x, scale_y));
		else
		{
			if (m_level.getTime() != -1)
				m_eatable.push_back(make_unique<TimePresent>(m_images[7], pos_x, pos_y, scale_x, scale_y));
			else
				m_eatable.push_back(make_unique<PointsPresent>(m_images[5], pos_x, pos_y, scale_x, scale_y));
		}
	}
}

// load files off image and texts
void Board::setImages()
{
	Texture text;
	text.loadFromFile("Coin.png");
	m_images.push_back(text);
	text.loadFromFile("Player.png");
	m_images.push_back(text);
	text.loadFromFile("Wall.png");
	m_images.push_back(text);
	text.loadFromFile("Enemy.png");
	m_images.push_back(text);
	text.loadFromFile("Rope.png");
	m_images.push_back(text);
	text.loadFromFile("PresentCoin.png");
	m_images.push_back(text);
	text.loadFromFile("Ladder.png");
	m_images.push_back(text);
	text.loadFromFile("PresentTime.png");
	m_images.push_back(text);
	text.loadFromFile("PresentLife.png");
	m_images.push_back(text);
	text.loadFromFile("PresentEnemy.png");
	m_images.push_back(text);
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

//draw the objects and the statics on the window
void Board::draw(RenderWindow& window, float time)
{
	for (int i = 0; i < m_static.size(); i++)
	{
		if (m_static[i]->isDig() && m_static[i]->dynamicOndig())
		{
			m_static[i]->setScale(6, 0, 0);
			m_static[i]->draw(window);
			m_static[i]->setScale(5, 0, 0);
		}
		else
			m_static[i]->draw(window);
	}
	for (int i = 0; i < m_eatable.size(); i++)
		m_eatable[i]->draw(window);
	for (int i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->draw(window);
	m_player->draw(window);
	for (int i = 0; i < 4; i++)
	{
		updateStats(time);
		window.draw(m_text[i]);
	}
}

//tell player do move if user push the buttons
void Board::movePlayer(const float& time)
{
	m_player->move(m_static, m_eatable, m_enemies, time, Vector2f(0,0));
}

//tell enemy to move
void Board::moveEnemy(const float& timex)
{
	for (int i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->move(m_static, m_eatable, m_enemies, timex,m_player->getPosition());
}

//update the stats of the player and the level and the time
void Board::updateStats(float time)
{
	for (int i = 0; i < NUMOFTEXT; i++)
	{
		m_text[i].setFont(m_font);
		if (i == 0)
		{
			string str("Score = ");
			str += to_string(m_player->getScore());
			m_text[i].setString(str);
		}
		else if (i == 1)
		{
			string str("Life = ");
			str += to_string(m_player->getLife());
			m_text[i].setString(str);
		}
		else if (i == 2)
		{
			string str("Time = ");
			if (time != -1)
				str += to_string((int)time);
			m_text[i].setString(str);
		}
		else
		{
			string str("Level = ");
			str += to_string(m_level.getNumLevel());
			m_text[i].setString(str);
		}
	}
}

//check if player collect all the coins
bool Board::noMoreCoin()
{
	for (int i = 0; i < m_eatable.size(); i++)
	{
		Coin* coin = dynamic_cast<Coin*>(m_eatable[i].get());
		if (coin)
			return false;
	}
	return true;
}

//player failed and we reset the level
void Board::resetLevel()
{
	clearAll();
	buildObjects();
}

//get time from file
float Board::getTime()const
{
	return m_level.getTime();
}

//player failed update is life down
void Board::takeLife()
{
	m_player->takeLife();
}

//get number of level
int Board::getLevelNum()const
{
	return m_level.getNumLevel();
}

//clear all the objects if we move level or restart level
void Board::clearAll()
{
	m_eatable.clear();
	m_static.clear();
	m_enemies.clear();
}

//build the stats on the screen help to C-tor
void Board::createStats()
{
	for (int i = 0; i < NUMOFTEXT; i++)
	{
		m_text[i].setCharacterSize(STATSSIZE);
		m_text[i].setColor(Color::White);
		if (i == 0)
			m_text[i].setPosition(0, WINDOWHEIGHT);
		else if (i == 1)
			m_text[i].setPosition(WINDOWWIDTH / 4, WINDOWHEIGHT);
		else if (i == 2)
			m_text[i].setPosition(WINDOWWIDTH / 2, WINDOWHEIGHT);
		else
			m_text[i].setPosition(WINDOWWIDTH - WINDOWWIDTH / 4, WINDOWHEIGHT);
	}
}

//set special scales for dynamic objects and ropes
void Board::setScales()
{
	for (int i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->setScale(1, 0, 0);
	m_player->setScale(1, 0, 0);
	for (int i = 0; i < m_static.size(); i++)
		if (dynamic_cast<Rope*>(m_static[i].get()))
			m_static[i]->setScale(2, 0, 0);
}

//if player take a bad present we add a enemy
void Board::addEnemy()
{
	if (m_player->addEnemy())
	{
		bool rightplace = false;
		m_enemies.push_back(make_unique<RandomEnemy>(m_images[3], 1, 1, (float)WINDOWWIDTH / (float)m_level.getWidth(), (float)WINDOWWIDTH / (float)m_level.getHeight()));
		m_enemies[m_enemies.size() - 1]->setScale(1, 0, 0);

		//set the position on (1,1) and check for availble location
		while (!rightplace)
		{
		rightplace = true;
		for (int i = 0; i < m_static.size(); i++)
			if (dynamic_cast<Wall*>(m_static[i].get()))
				if (m_static[i]->checkCollision(m_enemies[m_enemies.size() - 1]->getGlobalBounds()))
				{
					m_enemies[m_enemies.size() - 1]->setPosition(Vector2f(1.f, 1.f));
						rightplace = false;
				}
		}
	}
	m_player->setNoAddEnemy();
}

//the controler ask if the player take the present of time and if its true he add 10 sec
bool Board::addTime()
{
	if (m_player->addTime())
	{
		m_player->setNoAddTime();
		return true;
	}
	return false;
}

//get the player life
int Board::getPlayerLife() const
{
	return m_player->getLife();
}

//check if player step on enmy
bool Board::PlayerOnEnemy() const
{
	return m_player->onEnemy();
}

//get player score for stats
int Board::getPlayerScore()const
{
	return m_player->getScore();
}

//load the last data if we reset the level or move to the next one
void Board::loadPlayerData(int score, int life, int level)
{
	m_player->setScore(score);
	m_player->setNoAddEnemy();
	m_player->setNoAddTime();
	m_player->setNoOnEnemy();
	m_player->setLevel(level);
	m_player->setLife(life);
}
