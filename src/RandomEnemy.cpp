#include "RandomEnemy.h"

//this function move the random enemy every %10 sec or if move failed chenge direction
void RandomEnemy::move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>& , vector<unique_ptr<DynamicObject>>& , float time, Vector2f )
{
	if (m_time <= 0)//time past set a new move
	{
		setRandomMove();

		m_time = (float)(rand() % 10);
	}

	setTime(time);

	m_time -= getTime();// handke time off move

	if (!checkAvailbleLoc(statics))//if not in air or in a dig
		return;

	m_onladder = false;

	setPosition(getDirection() * getTime() * speed_enemy);

	checkScale();

	checkMove(statics);//check move with static objects

	if (getDirection() == up && !m_onladder)//if player with direction up and not on ladder change move
		setRandomMove();
}

//this function rand a new move
void RandomEnemy::setRandomMove()
{
	int num;
	num = rand() % 4;
	if (num == 0)
		setDirection(left_);
	else if (num == 1)
		setDirection(right_);
	else if(num == 2)
		setDirection(up);
	else
		setDirection(down);
}

//this function turn the random machin and set first move
void RandomEnemy::setFirstMove()
{
	srand((int)time(NULL));
	setRandomMove();
}

//if collide with wall back one step and set new move
void RandomEnemy::handleCollision(Wall& gameObject)
{
	setPosition(-getDirection() * getTime() * speed_player);
	if (this->checkCollision(gameObject.getGlobalBounds()))
		setPosition(-getDirection() * getTime() * speed_player);

	setRandomMove();
}

//if collide with ladder set a sign
void RandomEnemy::handleCollision(Ladder& )
{
	m_onladder = true;
}
