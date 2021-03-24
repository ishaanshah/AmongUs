/* Source for class which stores all the information about the game */

#include "constants.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "utils/resource_manager.hpp"

#include "glm/fwd.hpp"

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

    // TODO: Put object creation over here
    std::vector<float> vertices1 {
        0.0f, 0.0f,
        10.0f, 0.0f,
        10.0f, 1080.0f,

        0.0f, 0.0f,
        0.0f, 1080.0f,
        10.0f, 1080.0f
    };
    std::vector<float> vertices2 {
        0.0f, 0.0f,
        1920.0f, 0.0f,
        1920.0f, 10.0f,

        0.0f, 0.0f,
        0.0f, 10.0f,
        1920.0f, 10.0f
    };
    for (int i = 0; i <= NCOLS; i++) {
        float x = i * (1920.0f / NCOLS) - 5;
        this->Objects.push_back(GameObject(glm::vec2(x, 0.0f),
                                           glm::vec2(1.0f, 1.0f),
                                           COLOR_RED,
                                           vertices1));
    }
    for (int i = 0; i <= NROWS; i++) {
        float y = i * (1080.0f / NROWS) - 5;
        this->Objects.push_back(GameObject(glm::vec2(0.0f, y),
                                           glm::vec2(1.0f, 1.0f),
                                           COLOR_RED,
                                           vertices2));
    }
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
