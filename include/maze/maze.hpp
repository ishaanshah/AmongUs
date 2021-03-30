#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>

#include "game_object.hpp"
#include "maze/cell.hpp"
#include "objects/character.hpp"

class Maze {
    public:
        std::vector<std::vector<Cell> > Cells;

        Maze();

        std::vector<GameObject> GenerateMaze();

        void RandomDFS(Cell &cell);

        Direction GetNextMove(Character *Player, Character *Imposter);
};

#endif
