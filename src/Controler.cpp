#include "Controler.h"

//controler C-tor
Controler::Controler()
{
    setTime();
    setImages();
    setLoopMusic();
}

//the main function in a loop move every circl move the dynamic objects and update the time check if player succcess in level or failed allso print the objects on the board
void Controler::run()
{
    openMenu();
    Clock clock;
    while (m_window.isOpen())
    {
        hanleTime();

        m_window.clear();
        
        m_board.draw(m_window, m_time);

        m_window.display();

        checkIfEndOffGame();

        checkIfPlayerFail();

        checkIfLoadNextLevel();

        Event event;
        while (m_window.pollEvent(event))
        {
            if ((event.type == Event::Closed) ||
                ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
            {
                m_window.close();
                break;
            }
        }
        auto time = clock.restart().asSeconds();

        MoveDynamicObject(time);
    }
}

//set the time from the file
void Controler::setTime()
{
    m_time = m_board.getTime();
}

//check if the time past
bool Controler::outOfTime()const
{
    return (m_time <= 0 && m_time > -1);
}

//open the first screen - nenu . ask the user if he want to play or exit
void Controler::openMenu()
{

    while (m_window.isOpen())
    {
        m_window.clear();
        m_window.draw(m_ptrimage[0]);
        m_window.draw(m_ptrimage[1]);
        m_window.display();
        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                {
                    if (m_ptrimage[0].getLocalBounds().contains(location))
                        return;
                    if (m_ptrimage[1].getGlobalBounds().contains(location))
                    {
                        m_window.close();
                        return;
                    }
                }
                }
                break;
            }
            }
        }
    }

}

//lase screen of the game tell the user if we win or lose and print how many points he maoke
void Controler::lastScreen(int num)
{
    setStats();
    while (m_window.isOpen())
    {
        m_window.clear();
        if (num == 0)
            m_window.draw(m_ptrimage[3]);
        else
            m_window.draw(m_ptrimage[2]);
        m_window.draw(m_text);
        m_window.display();
        Event event;
        while (m_window.pollEvent(event))
        {
            if ((event.type == Event::Closed) ||
                ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
            {
                m_window.close();
                break;
            }
        }
    }
}

//set the points in the last screen
void Controler::setStats()
{
    string str("Score = ");
    str += to_string(m_board.getPlayerScore());
    m_text.setString(str);
}

//if player take a time present the boaard add 10 sec
void Controler::addTime()
{
    m_time += 10;
}

//set image of first and last screen also set a position for them
void Controler::setImages()
{
    m_images[0].loadFromFile("newgame.png");
    m_images[1].loadFromFile("exitgame.png");
    m_images[2].loadFromFile("youwin.png");
    m_images[3].loadFromFile("youlose.png");
    m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    m_ptrimage[0].setTexture(m_images[0]);
    m_ptrimage[1].setTexture(m_images[1]);
    m_ptrimage[2].setTexture(m_images[2]);
    m_ptrimage[3].setTexture(m_images[3]);
    m_text.setFont(m_font);
    m_ptrimage[3].setPosition(0, 0);
    m_ptrimage[2].setPosition(0, 0);
    m_ptrimage[0].setPosition(0, 0);
    m_ptrimage[1].setPosition(0, 500);
    m_text.setPosition(0, 600);
    m_text.setCharacterSize(160);
    m_text.setColor(Color::White);
}

//set the main music and play
void Controler::setLoopMusic()
{
    m_music.openFromFile("loop.wav");
    m_music.setLoop(true);
    m_music.play();
    m_succeslevel.loadFromFile("missionsucces.wav");
    m_fail.loadFromFile("fail.wav");
}

//update the time each loop in the main function
void Controler::hanleTime()
{
    if (m_time != -1)
        m_time -= m_clock.restart().asSeconds();
}

//check if player have no life or player in the game if true go the last screen
void Controler::checkIfEndOffGame()
{
    if (m_board.getPlayerLife() == 0)
        lastScreen(0);
    if (m_board.getLevelNum() == 5)
        lastScreen(1);
}

//check if player failed and if true end the game or reset the level
void Controler::checkIfPlayerFail()
{
    if (m_board.PlayerOnEnemy() || outOfTime())
    {
        m_ptr.setBuffer(m_fail);
        m_ptr.play();
        m_board.resetLevel();
        m_time = m_board.getTime();
        if (outOfTime())//check if past the time
            m_board.takeLife();
    }
}

//check if the player win if true check if player win the game or set a new level
void Controler::checkIfLoadNextLevel()
{
    if (m_board.noMoreCoin())//check if no more coins in screen
    {
        m_ptr.setBuffer(m_succeslevel);
        m_ptr.play();
        m_board.openNewLevel();
        if (m_board.getLevelNum() == 5)
            lastScreen(1);
        m_time = m_board.getTime();
        m_clock.restart().asSeconds();
    }
}

//funcion that move the dynamic objects
void Controler::MoveDynamicObject(float& time)
{
    m_board.movePlayer(time);
    if (m_board.addTime())//check if player take the present time
        m_time += 10.f;
    m_board.addEnemy();//check if player take the bad present
    m_board.moveEnemy(time);
}