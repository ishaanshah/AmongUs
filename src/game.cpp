/* Source for class which stores all the information about the game */

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
    Character player = Character(glm::vec2(CHARACTER_SIZE / 2, CHARACTER_SIZE),
                                 glm::vec2(1.0f, 1.0f),
                                 Character::generateVerts(COLOR_YELLOW),
                                 COLOR_YELLOW);
    this->Objects.push_back(player);
}

void Game::Update(float dt) {
    // TODO: Check collision stuff here ig
}

void Game::ProcessInput(float dt) {
    // TODO: Pretty clear what should go over here
}

void Game::Render() {
    for (auto object: this->Objects) {
        object.Render();
    }
}
