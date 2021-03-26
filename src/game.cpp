/* Source for class which stores all the information about the game */

#include <GLFW/glfw3.h>

#include "constants.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "maze/maze.hpp"
#include "objects/character.hpp"
#include "utils/resource_manager.hpp"

Game::Game(unsigned int width, unsigned int height) :
           State(GAME_ACTIVE), Keys(), Width(width), Height(height),
           Score(0), Health(100), Time(TIME_LIMIT) {  }

void Game::Init() {
    // Load the object shader program
    ResourceManager::LoadShader("../shaders/object.vert",
                                "../shaders/object.frag",
                                nullptr, "object");

    // Create projection matrix
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
                                      static_cast<float>(this->Height),
                                      0.0f, -1.0f, 1.0f);

    // Set projection matrix
    ResourceManager::GetShader("object").Use().SetMatrix4("projection", projection);

    // Create maze object
    Maze maze = Maze();

    // Generate maze
    // TODO: Unique duplicate walls
    this->Walls = maze.GenerateMaze();

    const float cellSizeX = (float)WIDTH / NCOLS;
    const float cellSizeY = (float)HEIGHT / NROWS;

    // Create player
    this->Player = new Character(glm::vec2(CHARACTER_SIZE / 2, CHARACTER_SIZE),
                                 glm::vec2(1.0f, 1.0f),
                                 Character::GenerateVerts(COLOR_YELLOW),
                                 COLOR_YELLOW);

    // Create imposter
    int cellX = (3*NCOLS / 4) + rand() % (NCOLS / 4);
    int cellY = (3*NROWS / 4) + rand() % (NROWS / 4);
    glm::vec2 impPosition = glm::vec2(cellX*cellSizeX + CHARACTER_SIZE / 2.0f,
                                      cellY*cellSizeY + CHARACTER_SIZE);
    this->Imposter = new Character(impPosition, glm::vec2(1.0f, 1.0f),
                                   Character::GenerateVerts(COLOR_RED),
                                   COLOR_RED);
}

void Game::Update(float dt, GLFWwindow *window) {
    // Process input
    if (this->State == GAME_ACTIVE) {
        float velocity = CHARACTER_VELOCITY * dt;
        if (this->Keys[GLFW_KEY_D]) {
            this->Player->Move(RIGHT, this->Walls, velocity);
        }
        if (this->Keys[GLFW_KEY_A]) {
            this->Player->Move(LEFT, this->Walls, velocity);
        }
        if (this->Keys[GLFW_KEY_W]) {
            this->Player->Move(UP, this->Walls, velocity);
        }
        if (this->Keys[GLFW_KEY_S]) {
            this->Player->Move(DOWN, this->Walls, velocity);
        }
    }

    // TODO: Check collision stuff here ig
    // Update time
    this->Time -= dt;
    if (this->Time <= 0.0f) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    // Check if player health is enough
    if (this->Health <= 0) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::Render() {
    for (auto object: this->Walls) {
        object.Render();
    }
    this->Player->Render();
    this->Imposter->Render();
}
