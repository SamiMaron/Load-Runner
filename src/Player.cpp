#include "Player.h"
#include <memory>
#include "Wall.h"

//this function move the player and dig, check if the player can move and than check which buttom the user press and do the step or dig. after that checking colide with coins presents and enemies
void Player::move( vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>& eatable, vector<unique_ptr<DynamicObject>>& enemies, float time, Vector2f )
{
	m_checkdig = false;

	if (!m_soundon)//set the eat coin sound
	{
		setSound();
		m_soundon = true;
	}

	setTime(time);

	m_onladder = false;

	if (!checkAvailbleLoc(statics))//if not in air or in a dig
		return;

	if (Keyboard::isKeyPressed(Keyboard::Left))
		setDirection(left_);

	else if (Keyboard::isKeyPressed(Keyboard::Right))
		setDirection(right_);

	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		//first check if on ladder if no return with no move
		checkMove(statics);
		if (m_onladder)
			setDirection(up);
		else
			return;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Down))
		setDirection(down);

	else if ((Keyboard::isKeyPressed(Keyboard::X)))
	{
		setDirection(right_);
		dig(statics, enemies);
		setDirection(Vector2f(0, 0));
		return;
	}

	else if ((Keyboard::isKeyPressed(Keyboard::Z)))
	{
		setDirection(left_);
		dig(statics, enemies);
		setDirection(Vector2f(0, 0));
		return;
	}

	setPosition(getDirection() * getTime() * speed_player);

	checkScale();

	checkMove(statics);//check if the move okay

	checkEatableCollison(eatable);//check colides with coins and presents

	checkEnemiesCollision(enemies);//check colide with enemies

	setDirection(Vector2f(0, 0));//reset direction
}

//get player life for stats
int Player::getLife()const
{
	return m_lives;
}

//get player score for stats
int Player::getScore()const
{
	return m_score + m_tempscore;
}

//if player push X or Z this function set a dig on wall. move one cell to the direction and check if the is a wall there and
//no static object or fynamic object up to this cell if its true dig else return and not do nothing
void Player::dig(const vector<unique_ptr<ObjectBase>>& statics, const vector<unique_ptr<DynamicObject>>& enemies)
{
	Vector2f pos = getPosition();
	float x = statics[0]->getGlobalBounds().width;

	if (getDirection() == left_)
		x = -x;

	//for check if there is something up to wall
	m_onladder = false;
	m_onroop = false;
	m_onwall = false;

	//set step to the neighbor cell
	moveDirect(Vector2f(getPosition().x + x, getPosition().y));
	checkMove(statics);

	//check if nothing up do this cell
	if (m_onladder || m_onroop || m_onwall)
	{
		moveDirect(Vector2f(getPosition().x - x, getPosition().y));
		return;
	}

	//check if no enemies in up this cell
	for (int i = 0; i < enemies.size(); i++)
		if (this->checkCollision(enemies[i]->getGlobalBounds()))
			return;

	//set sign to the wall to dig		
	m_checkdig = true;
	moveDirect(Vector2f(getPosition().x, getPosition().y + 5.f));
	checkMove(statics);
	m_checkdig = false;

	//return to the original position
	moveDirect(pos);
}

//handle collide with enemies take life reset the points from this level and set sign to the controler to handle with this situation
void Player::handleCollision(DynamicObject& )
{
	m_lives--;
	m_tempscore = 0;
	m_onenemy = true;
}

//handle collide with points present add 20 points for player
void Player::handleCollision(PointsPresent& )
{
	m_tempscore += 20;
}

//handle collide with enemy present set sign to the board to add enemy
void Player::handleCollision(EnemyPresent& )
{
	m_addEnemy = true;
}

//handle colide with coin add 2*level points and set a sound
void Player::handleCollision(Coin& )
{
	m_tempscore += 2 * m_level;
	m_ptrtakecoin.play();
}

//and collide with time present set a sign to the board that he need to add 10 sec
void Player::handleCollision(TimePresent& )
{
	m_addtime = true;
}

//handle collide with life present add a life
void Player::handleCollision(LifePresent&)
{
	m_lives++;
}

//handle collide with ladder set a sign that the player on ladder
void Player::handleCollision(Ladder& )
{
	m_onladder = true;
}

//handle collide with wall if player press X and the function off dig check that the wallcan dig tell wo this wall to dig else take step back to handle with player on wall
void Player::handleCollision(Wall& gameObject)
{
	if (m_checkdig)
	{
		moveDirect(Vector2f(getPosition().x - (getDirection().x * gameObject.getGlobalBounds().width), getPosition().y));
		if (!gameObject.checkCollision(this->getGlobalBounds()))
		{
			ObjectBase* wall = dynamic_cast<ObjectBase*>(&gameObject);
			wall->setDig();
		}
		moveDirect(Vector2f(getPosition().x + (getDirection().x * gameObject.getGlobalBounds().width), getPosition().y));
		return;
	}
	setPosition(-getDirection() * getTime() * speed_player);
	if (this->checkCollision(gameObject.getGlobalBounds()))
		setPosition(-getDirection() * getTime() * speed_player);
}

//handle a collide with rope set a sign that the player on rope
void Player::handleCollision(Rope& )
{
	m_onroop = true;
}

//check with all the coints and presents if there is collide if true handle and remove this object
void Player::checkEatableCollison( vector<unique_ptr<Eatable>>& eatable)
{
	for (int i = 0; i < eatable.size(); i++)
		if (eatable[i]->checkCollision(this->getGlobalBounds()))
		{
			eatable[i]->handleCollision(*this);
			eatable.erase(eatable.begin() + i);
		}
}

//check with all the enemiues if there is collide if true handle
void Player::checkEnemiesCollision(const vector<unique_ptr<DynamicObject>>& enemies)
{
	for (int i = 0; i < enemies.size(); i++)
		if (enemies[i]->checkCollision(this->getGlobalBounds()))
			enemies[i]->handleCollision(*this);
}

//user win the level update the score and the level
void Player::updateLevel()
{
	m_score += 50 * m_level;
	m_score += m_tempscore;
	m_level++;
	m_tempscore = 0;
}

//take life and reset the points from this level
void Player::takeLife()
{
	m_lives--;
	m_tempscore = 0;
}

//set a sign to the board to add enemy
bool Player::addEnemy()
{
	return m_addEnemy;
}

//set a sign to the controler to add time
bool Player::addTime()
{
	return m_addtime;
}

//reset the sign of add enemy
void Player::setNoAddEnemy()
{
	m_addEnemy = false;
}

//set a sign that collide with enemy
bool Player::onEnemy()const
{
	return m_onenemy;
}

//reset the sign that collide with enemy
void Player::setNoOnEnemy()
{
	m_onenemy = false;
}

//reset the sign that add time
void Player::setNoAddTime()
{
	m_addtime = false;
}

//set score from board
void Player::setScore(int num)
{
	m_score = num;
}

//set life from board
void Player::setLife(int num)
{
	m_lives = num;
}

//set life from board
void Player::setLevel(int num)
{
	m_level = num;
}

//set sound off eating coin
void Player::setSound()
{
	m_takecoin.loadFromFile("coin.wav");
	m_ptrtakecoin.setBuffer(m_takecoin);
}
