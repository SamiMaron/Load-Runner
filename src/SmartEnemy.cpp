#include "SmartEnemy.h"

//move the smart enemy. if the x cordinad in the same position move left or right if player up to enemy search for closes ladder if player down to enemy check for top ladder or fall down to enemy
void SmartEnemy::move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>&, vector<unique_ptr<DynamicObject>>&, float time, Vector2f playerpos)
{
	if (!checkAvailbleLoc(statics))//if not in air or in a dig
		return;

	m_onwalls = false;

	m_onladder = false;

	on_topladder = false;
	
	m_sign = false;

	setTime(time);

	setDirection(setSmartMove(statics, playerpos));

	lastmove = getDirection();

	setPosition(getDirection() * getTime() * speed_enemy);
}

//this function check if the x cordinad in the same position move left or right if player up to enemy search for closes ladder if player down to enemy check for top ladder or fall down to enemy
Vector2f SmartEnemy::setSmartMove(const vector<unique_ptr<ObjectBase>>& statics, Vector2f playerpos)
{
	float y = 0;
	Vector2f pos = getPosition();
	if (getPosition().y > playerpos.y)//check if player up to enemy
		y = -1.f;
	else if (getPosition().y < playerpos.y)//check if player down to enemy
		y = 1.f;
	

	if (abs(getPosition().y - playerpos.y) >= 0 && abs(getPosition().y - playerpos.y) <= 2.f)//check if the player and enemy in the same cordinate x
	{
													//if enemy need to left check move first and if true return left
		if (getPosition().x > playerpos.x)
		{
			if (checkStepCordinateX(statics, left_, pos))
			{
				return left_;
			}
		}
		else if (getPosition().x < playerpos.x)//if enemy need to right check move first and if true return right
		{
			if (checkStepCordinateX(statics, right_, pos))
			{
				return right_;
			}
		}
		else
		{
			return Vector2f(0,0);
		}
	}

	m_onladder = false;
	m_onwalls = false;

	if (y == -1.f)//handle if player up to enemy
		{
			setPosition(up * getTime() * speed_enemy);//set step up and check collides
			checkMove(statics);
			setPosition(down * getTime() * speed_enemy);

			if (m_onladder)//if enemy step is on ladder set step. if player on ladder and walls exit from ladder
			{
				setPosition(up * getTime() * speed_enemy);
				if (m_onwalls)//if the enemy is on wall and ladder set a direction to exit from ladder
				{
					setPosition(down * getTime() * speed_enemy);
					int counterleft = goOutFromLadder(statics, left_);
					moveDirect(pos);
					int counterright = goOutFromLadder(statics, right_);
					moveDirect(pos);
					if (counterleft > counterright)
						return left_;
					else if (counterright > counterleft)
						return right_;
				}
				setPosition(down * getTime() * speed_enemy);
				return up;//if enemy only on ladder move up
			}

			//enemy no on ladder than search for closes one to go up counter and return the lowest steps for ladder
			int counterleft = checkClosesLadder(statics, left_);
			moveDirect(pos);
			int counterright = checkClosesLadder(statics, right_);
			moveDirect(pos);

			int step = getMinimunStepToDestianation(counterleft, counterright);//get the direction for the closes ladder
			if (step == counterleft)
				return left_;
			else if (step == counterright)
				return right_;
			else
				return lastmove;
		}

	else//player down enemy up check if player can go down if not search for place to fall down or check for ladder that go down
	{
		moveDirect(Vector2f(getPosition().x, getPosition().y + 1.f));
		Vector2f posdown = getPosition();
		checkMove(statics);

		if (m_onladder)//if move down is on ladder that go down
		{
			if (m_onwalls)// if move down is alse on wall set direction to center ladder
			{
				moveDirect(Vector2f(getPosition().x, getPosition().y - 1.f));
				m_onwalls = false;
				m_onladder = false;
				checkMove(statics);
				if (!m_onwalls && !m_onladder)
				{
					moveDirect(posdown);
					int counterleft = goOutFromLadder(statics, left_);
					moveDirect(posdown);
					int counterright = goOutFromLadder(statics, right_);
					moveDirect(pos);
					if (counterleft > counterright)
						return left_;
					else if (counterright > counterleft)
						return right_;
				}
			}
			else//if down is availble step
			{
				moveDirect(pos);
				return down;
			}
		}

		//if player need to get down and need to search for top ladder
		moveDirect(posdown);
		int counterleft = checkCloseTopLadder(statics, left_);
		moveDirect(posdown);
		int counterright = checkCloseTopLadder(statics, right_);
		moveDirect(pos);

		int step = getMinimunStepToDestianation(counterleft, counterright);//get the direction for the closes ladder
		if (step == counterleft)
			return left_;
		else if (step == counterright)
			return right_;
		else
			return lastmove;

	}
}

//this function find the closes ladder that go up to player
int SmartEnemy::checkClosesLadder(const vector<unique_ptr<ObjectBase>>& statics, Vector2f move)
{
	m_onwalls = false;
	m_onladder = false;
	int counter = 0;
	while(!m_onwalls)//while there is no wall or no and screen move step right or left and counter the steps for ladder than return the direction with less step
	{
		moveDirect(Vector2f(getPosition().x + 10.f*move.x, getPosition().y));
		checkMove(statics);
		if (m_onladder)
			return counter;
		counter++;
	}
	return -1;//return no way to ladder
}

//this function is when enemy no on the center of the ladder and this function tell him which direction to go to the center
int SmartEnemy::goOutFromLadder(const vector<unique_ptr<ObjectBase>>& statics, Vector2f move)
{
	int counter = 0;
	m_onladder = false;

	while (!m_onladder)//while the player on ladder move to the left and the right and search for center
	{
		moveDirect(Vector2f(getPosition().x + 10.f * move.x, getPosition().y));
		checkMove(statics);
		if (m_onladder)
			m_onladder = false;
		else
			m_onladder = true;
		counter++;
	}
	return counter;
}
//this function finding the closes top ladder to get down or to fall down return the firection the close to the this target
int SmartEnemy::checkCloseTopLadder(const vector<unique_ptr<ObjectBase>>& statics, Vector2f move)
{
	Vector2f pos = getPosition();
	int counter = 0;
	m_onwalls = false;
	m_onladder = false;
	while (true)//while we dont fint the targen we go left or right and if its not possible we return -1 else we return the step
	{
		moveDirect(Vector2f(getPosition().x +move.x * 10.f, getPosition().y));
		checkMove(statics);
		if (isOffScreen())//no way return -1
			return -1;
		if (!m_onwalls && !m_onladder && !isOffScreen())//if there is fall down return steps
			return counter;
		if (m_onladder)//check if enemy can go up if not keep counting
		{
			moveDirect(Vector2f(getPosition().x, getPosition().y + 50.f));
			m_onladder = false;
			checkMove(statics);
			if (m_onladder)
				return counter;
			else
				moveDirect(Vector2f(getPosition().x, getPosition().y - 50.f));
		}
		counter++;
		m_onwalls = false;
		m_onladder = false;
	}
}

bool SmartEnemy::checkStepCordinateX(const vector<unique_ptr<ObjectBase>>& statics, Vector2f direction, Vector2f lastpos)//if enemy in the same line with player check availble close move to player
{
	setPosition(direction * speed_enemy * getTime());
	checkMove(statics);
	moveDirect(lastpos);
	if (!m_onwalls)//if availble and enemy not collide with wall and go offscreen
		return true;
	return false;
}

int SmartEnemy::getMinimunStepToDestianation(int left, int right)//check which step is close and availble to climbe or go down
{
	if (right == -1 && left == -1)
		return -1;
	else if (left == -1)
		return right;
	else if (right == -1)
		return left;
	else if (left < right)
		return left;
	else if (right < left)
		return right;
	else
		return -1;
}

void SmartEnemy::handleCollision(Wall& )//set enemy on wall
{
	m_onwalls = true;
}

void SmartEnemy::handleCollision(Ladder& )//set enemy on ladder
{
	m_onladder = true;
}

void SmartEnemy::handleCollision(Rope& )//set enemy on rope
{
	m_onrope = true;
}
