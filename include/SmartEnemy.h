#pragma once

#include "DynamicObject.h"
#include <Board.h>

class SmartEnemy : public DynamicObject
{
public:
	using DynamicObject::DynamicObject;
	void move(vector<unique_ptr<ObjectBase>>& statics, vector<unique_ptr<Eatable>>& eatable, vector<unique_ptr<DynamicObject>>& enemies, float time, Vector2f playerpos)override;
	virtual void handleCollision(Wall& gameObject);
	virtual void handleCollision(Ladder& gameObject);
	virtual void handleCollision(Rope& gameObject);
	Vector2f setSmartMove(const vector<unique_ptr<ObjectBase>>& statics, Vector2f playerpos);
	int checkClosesLadder(const vector<unique_ptr<ObjectBase>>& statics, Vector2f);
	int goOutFromLadder(const vector<unique_ptr<ObjectBase>>& statics, Vector2f);
	int checkCloseTopLadder(const vector<unique_ptr<ObjectBase>>& statics, Vector2f);
	bool checkStepCordinateX(const vector<unique_ptr<ObjectBase>>& statics, Vector2f, Vector2f);
	int getMinimunStepToDestianation(int, int);
private:
	bool m_sign = false;
	bool on_topladder = false;
	bool m_onladder = false;
	bool m_onwalls = false;
	bool m_onrope = false;
	Vector2f lastmove;
};