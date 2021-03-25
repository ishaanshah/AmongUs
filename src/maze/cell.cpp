#include "constants.hpp"
#include "game_object.hpp"
#include "maze/cell.hpp"


Cell::Cell(std::pair<int, int> Position) : Position(Position),
                                           Visited(false),
                                           Walls({true, true, true, true}) { }

std::vector<glm::vec4> Cell::GetNeighbours() {
    std::vector<glm::vec4> neighbours;

    // Left neighbour
    if (this->Position.first != 0) {
        neighbours.push_back(glm::vec4(this->Position.first-1,
                                       this->Position.second,
                                       0, 2));
    }

    // Right neighbour
    if (this->Position.first != NCOLS-1) {
        neighbours.push_back(glm::vec4(this->Position.first+1,
                                       this->Position.second,
                                       2, 0));
    }

    // Top neighbour
    if (this->Position.second != 0) {
        neighbours.push_back(glm::vec4(this->Position.first,
                                       this->Position.second-1,
                                       1, 3));
    }

    // Bottom neighbour
    if (this->Position.second != NROWS-1) {
        neighbours.push_back(glm::vec4(this->Position.first,
                                       this->Position.second+1,
                                       3, 1));
    }

    return neighbours;
}

std::vector<GameObject> Cell::GenerateWalls() {
    std::vector<GameObject> walls;

    float cellSizeX = (float)WIDTH / NCOLS;
    float cellSizeY = (float)HEIGHT / NROWS;

    std::vector<float> vertsVertical {
        0.0f, 0.0f, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        WALL_SIZE, 0.0f, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        WALL_SIZE, cellSizeY + WALL_SIZE, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,

        0.0f, 0.0f, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        0.0f, cellSizeY + WALL_SIZE, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        WALL_SIZE, cellSizeY + WALL_SIZE, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b
    };
    std::vector<float> vertsHorizontal {
        0.0f, 0.0f, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        cellSizeX + WALL_SIZE, 0.0f, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        cellSizeX + WALL_SIZE, WALL_SIZE, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,

        0.0f, 0.0f, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        0.0f, WALL_SIZE, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b,
        cellSizeX + WALL_SIZE, WALL_SIZE, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b
    };

    // Left wall
    if (this->Walls[0]) {
        float x = this->Position.first * cellSizeX - ((float)WALL_SIZE / 2);
        float y = this->Position.second * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   vertsVertical,
                                   true));
    }

    // Right wall
    if (this->Walls[2]) {
        float x = (this->Position.first + 1) * cellSizeX - ((float)WALL_SIZE / 2);
        float y = this->Position.second * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   vertsVertical,
                                   true));
    }

    // Top wall
    if (this->Walls[1]) {
        float x = this->Position.first * cellSizeX - ((float)WALL_SIZE / 2);
        float y = this->Position.second * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   vertsHorizontal,
                                   true));
    }

    // Bottom wall
    if (this->Walls[3]) {
        float x = this->Position.first * cellSizeX - ((float)WALL_SIZE / 2);
        float y = (this->Position.second + 1) * cellSizeY - ((float)WALL_SIZE / 2);
        walls.push_back(GameObject(glm::vec2(x, y),
                                   glm::vec2(1.0f, 1.0f),
                                   vertsHorizontal,
                                   true));
    }

    return walls;
}
