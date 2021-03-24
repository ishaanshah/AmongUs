#include "constants.hpp"
#include "game_object.hpp"
#include "maze/cell.hpp"


Cell::Cell(std::pair<int, int> Position) : Position(Position),
                                           Visited(false),
                                           Walls({true, true, true, true}) { }

std::vector<Cell> Cell::GetNeigbours() {

}

std::vector<GameObject> Cell::GenerateWalls() {
    std::vector<GameObject> walls;

    float cellSizeX = (float)WIDTH / NCOLS;
    float cellSizeY = (float)HEIGHT / NROWS;

    std::vector<float> vertsVertical {
        0.0f, 0.0f,
        WALL_SIZE, 0.0f,
        WALL_SIZE, cellSizeY + WALL_SIZE,

        0.0f, 0.0f,
        0.0f, cellSizeY + WALL_SIZE,
        WALL_SIZE, cellSizeY + WALL_SIZE
    };
    std::vector<float> vertsHorizontal {
        0.0f, 0.0f,
        cellSizeX + WALL_SIZE, 0.0f,
        cellSizeX + WALL_SIZE, WALL_SIZE,

        0.0f, 0.0f,
        0.0f, WALL_SIZE,
        cellSizeX + WALL_SIZE, WALL_SIZE
    };

    // Left wall
    if (this->Walls[0]) {
        float x = this->Position.first * cellSizeX - ((float)WALL_SIZE / 2);
        float y = this->Position.second * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   COLOR_RED,
                                   vertsVertical));
    }

    // Right wall
    if (this->Walls[2]) {
        float x = (this->Position.first + 1) * cellSizeX - ((float)WALL_SIZE / 2);
        float y = this->Position.second * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   COLOR_RED,
                                   vertsVertical));
    }

    // Top wall
    if (this->Walls[1]) {
        float x = this->Position.first * cellSizeX - ((float)WALL_SIZE / 2);
        float y = this->Position.second * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   COLOR_RED,
                                   vertsHorizontal));
    }

    // Bottom wall
    if (this->Walls[3]) {
        float x = this->Position.first * cellSizeX - ((float)WALL_SIZE / 2);
        float y = (this->Position.second + 1) * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   COLOR_RED,
                                   vertsHorizontal));
    }

    return walls;
}
