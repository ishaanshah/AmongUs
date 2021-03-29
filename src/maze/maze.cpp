#include "constants.hpp"
#include "game_object.hpp"
#include "maze/maze.hpp"

#include <cstdlib>

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
    // Run recursive backtracking algorithm
    RandomDFS(this->Cells[0][0]);

    // TODO: Randomly remove some walls to create cycles
    for (auto &row : this->Cells) {
        for (auto &cell : row) {
            if (rand() % 100 < 50) {
                for (auto wall : cell.Walls) {
                    if (wall && rand() % 100 < 80) {
                        wall = false;
                    }
                }
            }
        }
    }

    // Re-add wals to to edge of the screens
    for (int i = 0; i < NCOLS; i++) {
        this->Cells[i][0].Walls[1] = true;
        this->Cells[i][NROWS-1].Walls[3] = true;
    }
    for (int i = 0; i < NROWS; i++) {
        this->Cells[0][i].Walls[0] = true;
        this->Cells[NCOLS-1][i].Walls[2] = true;
    }

    // Remove bottom right walls (Make it the exit)
    this->Cells[NCOLS-1][NROWS-1].Walls[2] = false;
    this->Cells[NCOLS-1][NROWS-1].Walls[3] = false;

    // Generate the walls
    std::vector<GameObject> maze;
    for (auto &row : this->Cells) {
        for (auto &cell : row) {
            std::vector<GameObject> cellWalls = cell.GenerateWalls();
            maze.insert(maze.end(), cellWalls.begin(), cellWalls.end());
        }
    }

    return maze;
}

void Maze::RandomDFS(Cell &cell) {
    cell.Visited = true;
    std::vector<glm::vec4> neighbours = cell.GetNeighbours();

    std::vector<glm::vec4> chooseFrom;
    int x = cell.Position.first;
    int y = cell.Position.second;
    while (true) {
        chooseFrom.clear();

        // Check which neighbours are unvisited
        for (auto neighbour : neighbours) {
            if (!this->Cells[neighbour.x][neighbour.y].Visited) {
                chooseFrom.push_back(neighbour);
            }
        }

        if (chooseFrom.size() == 0) {
            break;
        }

        // CHoose a random neighbour
        int idx = rand() % chooseFrom.size();
        Cell &nextCell = this->Cells[chooseFrom[idx].x][chooseFrom[idx].y];

        // Remove walls in between
        cell.Walls[chooseFrom[idx].z] = false;
        nextCell.Walls[chooseFrom[idx].w] = false;

        RandomDFS(nextCell);
    }
}
