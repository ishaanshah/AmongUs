#include <vector>

#include "game_object.hpp"
#include "maze/cell.hpp"

class Maze {
    public:
        int nrows, ncols;
        std::vector<std::vector<Cell> > Cells;

        Maze();

        std::vector<GameObject> GenerateMaze();
};
