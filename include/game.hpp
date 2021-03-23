/* Header for class which stores all the information about the game */
#ifndef GAME_HPP
#define GAME_HPP

// Current state of the game
enum GameState  {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_PAUSED
};

// Class to store information about the current game
class Game {
    public:
        GameState State;
        bool Keys[1024];
        unsigned int Width, Height;
        Game(unsigned int width, unsigned int height);
        ~Game();
        void Init();
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};

#endif
