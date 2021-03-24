#include "constants.hpp"
#include "game_object.hpp"
#include "maze/maze.hpp"

Maze::Maze() {
    // Initiate cells
    for (int i = 0; i < NCOLS; i++) {
        std::vector<Cell> temp;
        for (int j = 0; j < NROWS; j++) {
            temp.push_back(Cell({i, j}));
        }
        this->Cells.push_back(temp);
    }
}

std::vector<GameObject> Maze::GenerateMaze() {
    // TODO: Perform recursive backtracking

    std::vector<GameObject> maze;
    for (auto row : this->Cells) {
        for (auto cell : row) {
            std::vector<GameObject> cellWalls = cell.GenerateWalls();
            maze.insert(maze.end(), cellWalls.begin(), cellWalls.end());
        }
    }

    return maze;
}
