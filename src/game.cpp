/* Source for class which stores all the information about the game */

#include <GLFW/glfw3.h>
#include <string>
#include <sstream>

#include "constants.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "maze/maze.hpp"
#include "objects/character.hpp"
#include "utils/resource_manager.hpp"
#include "utils/text_renderer.hpp"

Game::Game(unsigned int width, unsigned int height) :
           State(GAME_ACTIVE), Keys(), Width(width), Height(height),
           Score(0), Health(100), Time(TIME_LIMIT) {  }

void Game::Init() {
    // Initialize text render
    this->Text = new TextRenderer(this->Width, this->Height);

    // Load glyphs
    this->Text->Load("../fonts/myosevka.ttf", FONT_SIZE);

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
    // Create hittable object list
    std::vector<GameObject *> hittables;
    for (int i = 0; i < this->Walls.size(); i++) {
        hittables.push_back(&this->Walls[i]);
    }
    hittables.push_back(this->Imposter);

    // Process input
    std::vector<GameObject *> hitList;
    if (this->State == GAME_ACTIVE) {
        float velocity = CHARACTER_VELOCITY * dt;
        std::vector<GameObject *> temp;
        if (this->Keys[GLFW_KEY_D]) {
            temp = this->Player->Move(RIGHT, hittables, velocity);
            hitList.insert(hitList.end(), temp.begin(), temp.end());
        }
        if (this->Keys[GLFW_KEY_A]) {
            temp.clear();
            hitList = this->Player->Move(LEFT, hittables, velocity);
            hitList.insert(hitList.end(), temp.begin(), temp.end());
        }
        if (this->Keys[GLFW_KEY_W]) {
            temp.clear();
            hitList = this->Player->Move(UP, hittables, velocity);
            hitList.insert(hitList.end(), temp.begin(), temp.end());
        }
        if (this->Keys[GLFW_KEY_S]) {
            temp.clear();
            hitList = this->Player->Move(DOWN, hittables, velocity);
            hitList.insert(hitList.end(), temp.begin(), temp.end());
        }
    }

    // Process hits
    for (int i = 0; i < hitList.size(); i++) {
        hitList[i]->Hit(this->Score, this->Health);
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
    for (auto wall: this->Walls) {
        wall.Render();
    }
    this->Player->Render();
    this->Imposter->Render();


    // Print time
    std::ostringstream buffer;
    buffer << "Time left: " << (int)this->Time;
    this->Text->RenderText(buffer.str(), 5.0f, 5.0f, 1.0f, COLOR_WHITE);

    // Print score
    buffer.str("");
    buffer << "Score: " << this->Score;
    this->Text->RenderText(buffer.str(), 5.0f, 5 + FONT_SIZE+5, 1.0f, COLOR_WHITE);

    // Print health
    buffer.str("");
    buffer << "Health: " << this->Health;
    this->Text->RenderText(buffer.str(), 5.0f, 5 + 2*(FONT_SIZE+5), 1.0f, COLOR_WHITE);
}
