#include "CyclicEnemy.h"

//move cyclic object every circle check if player colide with wall or end screen and if true change direction
void CyclicEnemy::move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>&, vector<unique_ptr<DynamicObject>>&, float time, Vector2f)
{
	if (!m_start)
	{
		setDirection(left_);
		m_start = true;
	}

	setTime(time);

	if (!checkAvailbleLoc(statics))
		return;

	checkScale();

	setPosition(getDirection() * getTime() * speed_enemy);

	if (isOffScreen())
	{
		setPosition(-getDirection() * getTime() * speed_player);

		changeDirection();
	}

	checkMove(statics);

}

//if colide with wall take step back and change direction
void CyclicEnemy::handleCollision(Wall& gameObject)
{

	setPosition(-getDirection() * getTime() * speed_player);
	if (this->checkCollision(gameObject.getGlobalBounds()))
		setPosition(-getDirection() * getTime() * speed_player);

	changeDirection();
}

//chenge direction function
void CyclicEnemy::changeDirection()
{
	if (getDirection() == left_)
		setDirection(right_);
	else
		setDirection(left_);
}

