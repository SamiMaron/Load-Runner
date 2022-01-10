#pragma once

#include "RandomEnemy.h"
#include "Coin.h"
#include "PointsPresent.h"
#include "EnemyPresent.h"
#include "TimePresent.h"
#include "LifePresent.h"
#include "SmartEnemy.h"
#include "ObjectBase.h"

class Wall;

class Player : public DynamicObject
{
public:
	using DynamicObject::DynamicObject;
	void move( vector<unique_ptr<ObjectBase>>& statics,  vector<unique_ptr<Eatable>>& eatable,  vector<unique_ptr<DynamicObject>>& enemies, float time, Vector2f playerpos);
	virtual void handleCollision(DynamicObject& gameObject);
	virtual void handleCollision(PointsPresent& gameObject);
	virtual void handleCollision(EnemyPresent& gameObject);
	virtual void handleCollision(Coin& gameObject);
	virtual void handleCollision(TimePresent& gameObject);
	virtual void handleCollision(LifePresent& gameObject);
	virtual void handleCollision(Ladder& gameObject);
	virtual void handleCollision(Wall& gameObject);
	virtual void handleCollision(Rope& gameObject);
	void checkEatableCollison( vector<unique_ptr<Eatable>>& eatable);
	void checkEnemiesCollision(const vector<unique_ptr<DynamicObject>>& enemies);
	int getLife()const;
	int getScore()const;
	void updateLevel();
	void takeLife();
	bool addEnemy();
	bool addTime();
	void setNoAddEnemy();
	bool onEnemy()const;
	void setNoOnEnemy();
	void setNoAddTime();
	void setScore(int);
	void setLife(int);
	void setLevel(int);
	void setSound();
	void dig(const vector<unique_ptr<ObjectBase>>& statics, const vector<unique_ptr<DynamicObject>>& enemies);

private:
	int m_score = 0;
	int m_lives = 3;
	int m_level = 1;
	int m_tempscore = 0;
	bool m_onladder = false;
	bool m_addEnemy = false;
	bool m_addtime = false;
	bool m_onenemy = false;
	bool m_soundon = false;
	bool m_onroop = false;
	bool m_checkdig = false;
	bool m_onwall = false;
	SoundBuffer m_takecoin;
	Sound m_ptrtakecoin;
};