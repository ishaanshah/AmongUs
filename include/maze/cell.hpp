#ifndef CELL_HPP
#define CELL_HPP

#include <vector>

#include <glm/glm.hpp>

#include "game_object.hpp"

class Cell {
    public:
        std::pair<int, int> Position;
        bool Visited;
        std::vector<bool> Walls;

        Cell(std::pair<int, int> Position);

        std::vector<Cell> GetNeigbours();
        std::vector<GameObject> GenerateWalls();
};

#endif
