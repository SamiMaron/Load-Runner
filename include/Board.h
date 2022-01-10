#pragma once

#include "Level.h"
#include "Player.h"
#include "SmartEnemy.h"
#include "CyclicEnemy.h"
#include "RandomEnemy.h"
#include "Rope.h"
#include <memory>
#include <iostream>

using namespace std;

const int TABLE_HEIGHT = 100;

const int NUMOFTEXT = 4;

const int LIFESTART = 3;

const int STATSSIZE = 30;

class Board {
public:
	Board();
	void openNewLevel();
	void buildObjects();
	void buildObject(char, float, float, float, float);
	void setImages();
	void draw(RenderWindow& window, float);
	void movePlayer(const float&);
	void moveEnemy(const float&);
	void updateStats(float time);
	bool noMoreCoin();
	void resetLevel();
	float getTime()const;
	void takeLife();
	int getLevelNum()const;
	void clearAll();
	void createStats();
	void setScales();
	void addEnemy();
	bool addTime();
	int getPlayerLife()const;
	bool PlayerOnEnemy()const;
	int getPlayerScore()const;
	void loadPlayerData(int,int,int);

private:
	Level m_level;
	vector <unique_ptr<Eatable>> m_eatable;//eatable objets
	vector <unique_ptr<ObjectBase>> m_static;//statics objects
	vector <Texture> m_images;//image for objects
	vector <unique_ptr<DynamicObject>> m_enemies;//enemies
	unique_ptr <Player> m_player = NULL;//player
	Font m_font;//font to stats
	Text m_text[NUMOFTEXT];//text for stats
	Sprite playerSprite;
};