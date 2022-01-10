#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

class Present;
class Player;
class Enemy;
class Ladder;
class Coin;
class Rope;
class DynamicObject;
class Wall;

class ObjectBase {
public:
	ObjectBase(const Texture&, float , float , float , float );
	void draw(RenderWindow&);
	Vector2f getPosition()const;
	void setPosition(const Vector2f &);
	bool checkCollision(FloatRect)const;
	FloatRect getGlobalBounds()const;
	void setScale(int,float,float);
	virtual ~ObjectBase() = default;
	void moveDirect(const Vector2f&);
	virtual void setDig();
	virtual bool isDig()const;
	virtual void setDigTime();
	virtual bool digOver();
	virtual void setDigClear();
	virtual void handleCollision(DynamicObject& gameObject);
	virtual bool dynamicOndig();
	virtual void setDynamicOnDig();

private:
	Sprite m_sprite;
};