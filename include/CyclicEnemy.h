#pragma once

#include "SmartEnemy.h"

class CyclicEnemy : public DynamicObject
{
public:
	using DynamicObject::DynamicObject;
	void move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>& eatable, vector<unique_ptr<DynamicObject>>& enemies, float time, Vector2f playerpos)override;
	virtual void handleCollision(Wall& gameObject);
	void changeDirection();

private:
	bool m_start = false;//sign if set a first move
};