#include "DynamicObject.h"
#include "player.h"

//virtual
void DynamicObject::move(vector<unique_ptr<ObjectBase>>& , vector<unique_ptr<Eatable>>& , vector<unique_ptr<DynamicObject>>& , float, Vector2f )
{
}

//set direction
void DynamicObject::setDirection(const Vector2f& direction)
{
	m_direction = direction;
}

//get direction
Vector2f DynamicObject::getDirection() const
{
	return m_direction;
}

//set time for move
void DynamicObject::setTime(float time)
{
	m_time = time;
}

//get time for move
float DynamicObject::getTime()
{
	return m_time;
}

//check every colide of the dynamic object with static objects
void DynamicObject::checkMove(const vector<unique_ptr<ObjectBase>>& statics)
{
	for (int i = 0; i < statics.size(); i++)
		if (statics[i]->checkCollision(this->getGlobalBounds()))
			statics[i]->handleCollision(*this);

	if (isOffScreen())
	{
		for (int i = 0; i < statics.size(); i++)
			if (dynamic_cast<Wall*>(statics[i].get()))
			{
				statics[i]->handleCollision(*this);
				return;
			}
	}
}

//check if dynamic object stand on wall or on ladder or rope if not set step down, 
//also check if dynamic on dig if true set sign for this dig that close the whole and behave like its regular wall
//when times dig over return dynamic to up cell
bool DynamicObject::checkAvailbleLoc(const vector<unique_ptr<ObjectBase>>& statics)
{
	if (m_on_dig && statics[num_dig]->digOver())//if dynamic on dig and dig over move to up cell and set dynamic free
	{
		while (statics[num_dig]->checkCollision(this->getGlobalBounds()))
			moveDirect(Vector2f(getPosition().x, getPosition().y - 0.3f));
		m_on_dig = false;
	}

	else if (m_on_dig && statics[num_dig]->isDig())//if dynamic on dig and still dig return with no move
		return false;

	moveDirect(Vector2f(getPosition().x, getPosition().y + 0.3f));//move step down

	for (int i = 0; i < statics.size(); i++)//check collision with static objects
		if (statics[i]->checkCollision(this->getGlobalBounds()))
		{
			if (statics[i]->isDig() && !statics[i]->dynamicOndig())//if dynamic on dig and no sign for that set sign and close the dig
			{
				statics[i]->setDynamicOnDig();
				statics[i]->setScale(5, 0, 0);//return wall to regular
				m_on_dig = true;//set player on dig
				num_dig = i;//set num of place dig in vector
				moveDirect(Vector2f(getPosition().x, getPosition().y - 0.3f));//return to original spot
				return false;
			}
			moveDirect(Vector2f(getPosition().x, getPosition().y - 0.3f));//if player on something return to original spot and continue to catch a move from dynamic
			return true;
		}
	return false;
}

//return if player off the screen
bool DynamicObject::isOffScreen()
{
	return (getGlobalBounds().left < 0 || getGlobalBounds().top < 0 || (getGlobalBounds().left + getGlobalBounds().width) > WINDOWWIDTH || (getGlobalBounds().height + getGlobalBounds().top) > WINDOWHEIGHT);
}

//colide with wall return step back
void DynamicObject::handleCollision(Wall& )
{
	setPosition(-getDirection() * getTime() * speed_player);
}

//virtual
void DynamicObject::handleCollision(Ladder& )
{
}

//virtual
void DynamicObject::handleCollision(Rope& )
{
}

//enemies colide with player return the conreol to the player
void DynamicObject::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}

//virtual
void DynamicObject::handleCollision(ObjectBase& )
{
}

//virtual
void DynamicObject::handleCollision(PointsPresent& )
{
}

//virtual
void DynamicObject::handleCollision(EnemyPresent& )
{
}

//virtual
void DynamicObject::handleCollision(Coin& )
{
}

//virtual
void DynamicObject::handleCollision(TimePresent& )
{
}

//virtual
void DynamicObject::handleCollision(LifePresent& )
{
}

//check if a player look to the right way
void DynamicObject::checkScale()
{
	if (!m_onleft && getDirection() == left_)
	{
		setScale(3, 0,0);
		m_onright = false;
		m_onleft = true;
	}
	if (!m_onright && getDirection() == right_)
	{
		setScale(3, 0,0);
		m_onright = true;
		m_onleft = false;
	}

}