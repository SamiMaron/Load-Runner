#pragma once

#include "ObjectBase.h"
#include "Eatable.h"
#include "Wall.h"
#include "Ladder.h"
#include <EnemyPresent.h>
#include <TimePresent.h>
#include <LifePresent.h>
#include <PointsPresent.h>

const float speed_player = 115.f;
const float speed_enemy = 90.f;

const Vector2f left_ = { -1,0 };
const Vector2f right_ = { 1,0 };
const Vector2f up = { 0,-1 };
const Vector2f down = { 0,1 };

const int WINDOWWIDTH = 900;
const int WINDOWHEIGHT = 900;

class DynamicObject : public ObjectBase
{
public:
	using ObjectBase::ObjectBase;
	virtual void move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>& eatable, vector<unique_ptr<DynamicObject>>& enemies, float time, Vector2f playerpos);
	void setDirection(const Vector2f&);
	Vector2f getDirection()const;
	void setTime(float time);
	float getTime();
	virtual void handleCollision(Wall& gameObject);
	virtual void handleCollision(Ladder& gameObject);
	virtual void handleCollision(Rope& gameObject);
	virtual void handleCollision(DynamicObject& gameObject);
	virtual void handleCollision(ObjectBase& gameObject);
	virtual void handleCollision(PointsPresent& gameObject);
	virtual void handleCollision(EnemyPresent& gameObject);
	virtual void handleCollision(Coin& gameObject);
	virtual void handleCollision(TimePresent& gameObject);
	virtual void handleCollision(LifePresent& gameObject);
	virtual void checkMove(const vector <unique_ptr<ObjectBase>>&);
	bool checkAvailbleLoc(const vector <unique_ptr<ObjectBase>>& statics);
	bool isOffScreen();
	void checkScale();
private:
	Vector2f m_direction = { 0,0 };
	float m_time;
	bool m_onleft = false;
	bool m_onright = true;
	bool m_on_dig = false;
	int num_dig;
};