/* Source for class which stores all the information about the game */

#include <GLFW/glfw3.h>

#include "constants.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "maze/maze.hpp"
#include "objects/character.hpp"
#include "utils/resource_manager.hpp"

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {  }

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
    std::vector<GameObject> walls = maze.GenerateMaze();
    this->Objects.insert(this->Objects.begin(), walls.begin(), walls.end());

    // Create player
    this->Player = new Character(glm::vec2(CHARACTER_SIZE / 2, CHARACTER_SIZE),
                                 glm::vec2(1.0f, 1.0f),
                                 Character::generateVerts(COLOR_YELLOW),
                                 COLOR_YELLOW);
}

void Game::Update(float dt) {
    // TODO: Check collision stuff here ig
}

void Game::ProcessInput(float dt) {
    if (this->State == GAME_ACTIVE) {
        float velocity = CHARACTER_VELOCITY * dt;
        if (this->Keys[GLFW_KEY_D]) {
            this->Player->Move(RIGHT, this->Objects, velocity);
        }
        if (this->Keys[GLFW_KEY_A]) {
            this->Player->Move(LEFT, this->Objects, velocity);
        }
        if (this->Keys[GLFW_KEY_W]) {
            this->Player->Move(UP, this->Objects, velocity);
        }
        if (this->Keys[GLFW_KEY_S]) {
            this->Player->Move(DOWN, this->Objects, velocity);
        }
    }
}

void Game::Render() {
    for (auto object: this->Objects) {
        object.Render();
    }
    this->Player->Render();
}
