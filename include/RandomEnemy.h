#pragma once

#include "CyclicEnemy.h"

class RandomEnemy : public DynamicObject
{
public:
	virtual void move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>& eatable, vector<unique_ptr<DynamicObject>>& enemies, float time, Vector2f playerpos);
	using DynamicObject::DynamicObject;
	void setRandomMove();
	void setFirstMove();
	virtual void handleCollision(Wall& gameObject);
	virtual void handleCollision(Ladder& gameObject);

private:
	float m_time = 0;
	bool m_onladder;
};