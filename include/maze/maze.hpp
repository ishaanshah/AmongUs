#include <vector>

#include "game_object.hpp"
#include "maze/cell.hpp"

class Maze {
    public:
        std::vector<std::vector<Cell> > Cells;

        Maze();

        std::vector<GameObject> GenerateMaze();
        void RandomDFS(Cell &cell);
};
