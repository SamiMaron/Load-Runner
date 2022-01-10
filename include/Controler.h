#include "Board.h"

class Controler {
public:
	Controler();
	void run();
	void setTime();
	bool outOfTime()const;
	void openMenu();
	void lastScreen(int);
	void setStats();
	void addTime();
	void setImages();
	void setLoopMusic();
	void hanleTime();
	void checkIfEndOffGame();
	void checkIfPlayerFail();
	void checkIfLoadNextLevel();
	void MoveDynamicObject(float&);

private:
	RenderWindow m_window = RenderWindow(VideoMode(WINDOWWIDTH, WINDOWHEIGHT + TABLE_HEIGHT), "Lude Runner");//window
	Clock m_clock;//clock of the game
	Board m_board;//all the objects
	float m_time;//time of level
	Texture m_images[4];//hold the image for open and end screen
	Sprite m_ptrimage[4];//pointers to textures
	Text m_text;
	Font m_font;
	Music m_music;
	SoundBuffer m_succeslevel, m_fail;
	Sound m_ptr;
};