#ifndef COIN_HPP
#define COIN_HPP

#include <vector>

#include <glm/glm.hpp>

#include "game_object.hpp"

class Coin : public GameObject {
    public:
        glm::vec3 Color;

        Coin(glm::vec2 Position, glm::vec2 Direction,
             std::vector<float> Vertices);

        static std::vector<float> GenerateVerts(); 

        void Hit(int &score, int &health, int &tasks, const bool lights,
                 GameObject *Imposter, std::vector<GameObject *> &coins,
                 std::vector<GameObject *> &bombs);
};

#endif
