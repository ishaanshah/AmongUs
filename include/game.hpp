/* Header for class which stores all the information about the game */
#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>
#include <vector>

#include "game_object.hpp"
#include "objects/character.hpp"
#include "utils/shader.hpp"
#include "utils/text_renderer.hpp"

// Current state of the game
enum GameState  {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_PAUSED
};

// Class to store information about the current game
class Game {
    public:
        Character *Player, *Imposter;
        GameState State;
        TextRenderer *Text;
        bool Keys[1024];
        float Time;
        int Score, Health;
        std::vector<GameObject> Walls; // TODO: Change to pointer to object
        std::vector<GameObject *> Coins, Bombs;
        unsigned int Width, Height;

        Game(unsigned int width, unsigned int height);

        void Init();
        void Update(float dt, GLFWwindow *window);
        void Render();
};

#endif
