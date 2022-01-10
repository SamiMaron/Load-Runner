#include "Level.h"
#include <string>

//this function set a new level. update the num of level. read the map from file and delete the last level
void Level::createNewLevel()
{
	m_level.clear();
	m_counter_level++;
	ifstream file;
	openFile(file);
	readFromFile(file);
}

//this function open a file of specipic level
void Level::openFile(ifstream& file) const
{
	if (m_counter_level == LevelOne)
		file.open("level1.txt");
	else if (m_counter_level == LevelTwo)
		file.open("level2.txt");
	else if (m_counter_level == LevelThree)
		file.open("level3.txt");
	else if (m_counter_level == LevelFour)
		file.open("level4.txt");
	else
		return;
}

//this function read the map from the file
void Level::readFromFile(ifstream& file)
{
	file >> m_width;
	file >> m_height;
	file >> m_time;
	string str;
	getline(file, str);
	while (getline(file, str))
		m_level.push_back(str);
}

//get the width of ther map
int Level::getWidth() const
{
	return m_width;
}

//get the height of the map
int Level::getHeight() const
{
	return m_height;
}

//get the char of the specific location
char Level::getChar(int x, int y) const
{
	return m_level[x][y];
}

//get the time off the level
float Level::getTime()const
{
	return m_time;
}

//get the num off the level
int Level::getNumLevel()const
{
	return m_counter_level;
}

