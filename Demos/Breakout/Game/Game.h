#pragma once

enum GameStatus{
    Game_Active,
    Game_Pause,
    Game_Menu,
    Game_Win,
    Game_Over
};

class Game
{
public:
    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();
    void update(double dt);
    void inputProcess(double dt);

    void render();
public:
    GameStatus status;
    bool Keys[1024];
private:
    unsigned int width, height;

};