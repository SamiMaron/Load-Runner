#include "ObjectBase.h"
#include "DynamicObject.h"

//each object C-tor set position and texture and scale
ObjectBase::ObjectBase(const Texture& text, float pos_x, float pos_y, float scale_x, float scale_y)
{
	m_sprite.setTexture(text);

	m_sprite.setScale(Vector2f(scale_x / m_sprite.getGlobalBounds().width, scale_y / m_sprite.getGlobalBounds().height));

	setPosition(Vector2f(pos_x, pos_y));
}

//draw the object on the window
void ObjectBase::draw(RenderWindow& window)
{
	if (isDig())
		setDigTime();
	window.draw(m_sprite);
}

//get position of the oobject
Vector2f ObjectBase::getPosition()const
{
	return m_sprite.getPosition();
}

//set position to the object
void ObjectBase::setPosition(const Vector2f& position)
{
	m_sprite.move(position);
}

//check if object colide with other oobject
bool ObjectBase::checkCollision(FloatRect floatRect)const
{
	return m_sprite.getGlobalBounds().intersects(floatRect);
}

//get the globalbounds of the object
FloatRect ObjectBase::getGlobalBounds()const
{
	return m_sprite.getGlobalBounds();
}

//set specific scale for object
void ObjectBase::setScale(int sign,float x, float y)
{
	if (sign == 1)
		m_sprite.scale(0.8f, 0.8f);
	if (sign == 2)
		m_sprite.scale(1.0f, 0.1f);
	if (sign == 3)
		m_sprite.scale(-1.f, 1.f);
	if (sign == 4)
		m_sprite.setScale(Vector2f(x, y));
	if (sign == 5)
	{
		m_sprite.scale(1.0f, 10.f);
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height + 1.f);
	}
	if (sign == 6)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + m_sprite.getGlobalBounds().height - 1.f);
		m_sprite.scale(1.0f, 0.1f);
	}
}

//move to the direct point
void ObjectBase::moveDirect(const Vector2f& pos)
{
	m_sprite.setPosition(pos);
}

//virtual
void ObjectBase::setDig()
{
}

//virtual
bool ObjectBase::isDig()const
{
	return false;
}

//virtual
void ObjectBase::setDigTime()
{
}

//virtual
bool ObjectBase::digOver()
{
	return false;
}

//virtual
void ObjectBase::setDigClear()
{
}

//virtual
void ObjectBase::handleCollision(DynamicObject&)
{
}

bool ObjectBase::dynamicOndig()
{
	return false;
}

void ObjectBase::setDynamicOnDig()
{
}
