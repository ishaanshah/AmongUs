#ifndef BOMB_HPP
#define BOMB_HPP

#include <vector>

#include <glm/glm.hpp>

#include "game_object.hpp"

class Bomb : public GameObject {
    public:
        glm::vec3 Color;

        Bomb(glm::vec2 Position, glm::vec2 Direction,
             std::vector<float> Vertices);

        static std::vector<float> GenerateVerts(); 

        void Hit(int &score, int &health, int &tasks, const bool lights,
                 GameObject *Imposter, std::vector<GameObject *> &coins,
                 std::vector<GameObject *> &bombs);

};

#endif
