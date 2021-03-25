/* Header for class which stores all the information about the game */
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "game_object.hpp"
#include "objects/character.hpp"
#include "utils/shader.hpp"

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
        std::vector<GameObject> Objects;
        bool Keys[1024];
        unsigned int Width, Height;
        Character *Player;

        Game(unsigned int width, unsigned int height);

        void Init();
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};

#endif
