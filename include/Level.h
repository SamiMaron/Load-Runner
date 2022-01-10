#pragma once

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

enum levelNum
{
	LevelOne = 1,
	LevelTwo = 2,
	LevelThree = 3,
	LevelFour = 4,
	LevelFive = 5
};

enum ObjectType
{
	enemy = '%',
	player = '@',
	wall = '#',
	present = '!',
	rope = '-',
	ladder = 'H',
	coin = '*',
	presentw = '+'
};


class Level {
public:
	void createNewLevel();
	void openFile(ifstream& file)const;
	void readFromFile(ifstream& file);
	int getWidth()const;
	int getHeight()const;
	char getChar(int x, int y)const;
	float getTime()const;
	int getNumLevel()const;
private:

	vector<string> m_level;
	float m_time=0;
	int m_width=0;
	int m_height =0;
	int m_counter_level = 0;
};