/* Header for class which stores all the information about the game */
#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>
#include <vector>

#include "game_object.hpp"
#include "objects/character.hpp"
#include "objects/tasks.hpp"
#include "maze/maze.hpp"
#include "utils/shader.hpp"
#include "utils/text_renderer.hpp"

// Class to store information about the current game
class Game {
    public:
        Character *Player, *Imposter;
        Maze *MyMaze;
        TaskPowerups *TaskP;
        TaskVaporise *TaskV;
        TextRenderer *Text;
        Direction ImposterDirection;
        bool Keys[1024], LightsOn;
        float Time;
        int Score, Health, Tasks;
        std::vector<GameObject *> Coins, Bombs;
        std::vector<GameObject> Walls; // TODO: Change to pointer to object
        unsigned int Width, Height;

        Game(unsigned int width, unsigned int height);

        void Init();
        void Update(float dt, GLFWwindow *window);
        void Render();
};

#endif
