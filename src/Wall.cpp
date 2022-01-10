#include "Wall.h"
#include "Player.h"

//this function set a dig in wall set a time for a dig set a scale for a dig update that this wall is dig
void Wall::setDig()
{
	m_releasefromdig = false;
	m_dig = true;
	m_time = 10.f;
	setScale(6, 0, 0);
}

//this function return if this wall dig
bool Wall::isDig()const
{
	return m_dig;
}

//this function handle dig time and if the time over update the set no dig. if there is a dynamic object on this dig set a sign to release him
void Wall::setDigTime()
{
	auto time = m_clock.restart().asSeconds();
	m_time -= time;
	if (m_time <= 0)
	{
		if(!dynamicOndig())
			setScale(5, 0, 0);
		m_dig = false;
		m_thereisdynamic = false;
		m_releasefromdig = true;
	}
}

//send to dynamic object tell him that he on wall
void Wall::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}

//set dig is over
void Wall::setOverDig()
{
	m_releasefromdig = false;
}

//return if sig over
bool Wall::digOver()
{
	return m_releasefromdig;
}

//return if dynamic on dig
bool Wall::dynamicOndig()
{
	return m_thereisdynamic;
}

//set dynamic on dig
void Wall::setDynamicOnDig()
{
	m_thereisdynamic = true;
}
