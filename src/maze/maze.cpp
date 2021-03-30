#include "constants.hpp"
#include "game_object.hpp"
#include "maze/maze.hpp"
#include "objects/character.hpp"

#include <cstdlib>
#include <list>

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
    for (int i = 0; i < NCOLS; i++) {
        for (int j = 0; j < NROWS-1; j++) {
            if (rand() % 100 < 20) {
                this->Cells[i][j].Walls[3] = false;
                this->Cells[i][j+1].Walls[1] = false;
            }
        }
    }
    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLS-1; j++) {
            if (rand() % 100 < 20) {
                this->Cells[j][i].Walls[2] = false;
                this->Cells[j+1][i].Walls[0] = false;
            }
        }
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

Direction Maze::GetNextMove(Character *Player, Character *Imposter) {
    float cellSizeX = (float)WIDTH / NCOLS;
    float cellSizeY = (float)HEIGHT / NROWS;

    // Get start and end cells
    std::pair<glm::vec2, glm::vec2> box = Imposter->GetBoundBox();
    glm::vec2 imposterCenter = box.first + (box.second / 2.0f);
    Cell *imposterCell = &this->Cells[imposterCenter.x/cellSizeX][imposterCenter.y/cellSizeY];

    float cellXCenter = cellSizeX*((float)imposterCell->Position.first + 0.5f);
    float cellYCenter = cellSizeY*((float)imposterCell->Position.second + 0.5f);
    if (fabs(imposterCenter.x - cellXCenter) > 10.0f ||
        fabs(imposterCenter.y - cellYCenter) > 10.0f) {
        return CONT;
    }

    box = Player->GetBoundBox();
    glm::vec2 playerCenter = box.first + (box.second / 2.0f);
    Cell *playerCell = &this->Cells[playerCenter.x/cellSizeX][playerCenter.y/cellSizeY];

    if (playerCell == imposterCell) {
        return STAY;
    }

    std::list<Cell *> queue;
    queue.push_back(imposterCell);

    std::vector<std::vector<bool> > visited (
        NCOLS, std::vector<bool>(NROWS, false)
    );
    std::vector<std::vector<Cell *> > parent(
        NCOLS, std::vector<Cell *>(NROWS, nullptr)
    );

    visited[imposterCell->Position.first][imposterCell->Position.second] = true;

    bool found = false;
    // std::cout << imposterCell->Walls << "\n";
    while(!queue.empty() && !found) {
        Cell *cell = queue.front();
        queue.pop_front();

        std::vector<glm::vec4> neighbours = cell->GetNeighbours();
        for (auto &neighbour : neighbours) {
            if (!cell->Walls[neighbour.z] && !visited[neighbour.x][neighbour.y]) {
                visited[neighbour.x][neighbour.y] = true;
                queue.push_back(&this->Cells[neighbour.x][neighbour.y]);
                parent[neighbour.x][neighbour.y] = cell; }
        }
    }

    Cell *currCell = playerCell;
    Cell *parCell = parent[currCell->Position.first][currCell->Position.second];
    while(parCell != imposterCell) {
        currCell = parCell;
        parCell = parent[currCell->Position.first][currCell->Position.second];
    }

    std::vector<glm::vec4> neighbours = imposterCell->GetNeighbours();
    for (auto &neighbour : neighbours) {
        if (&this->Cells[neighbour.x][neighbour.y] == currCell) {
            switch ((int)neighbour.z) {
                case 0:
                    return LEFT;
                case 1:
                    return UP;
                case 2:
                    return RIGHT;
                case 3:
                    return DOWN;
            }
        }
    }
    return STAY;
}
