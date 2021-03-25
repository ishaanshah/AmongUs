#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>

#include <glm/glm.hpp>

#include "game_object.hpp"

class Character : public GameObject {
    public:
        glm::vec3 Color;

        Character(glm::vec2 Position, glm::vec2 Direction,
                  std::vector<float> Vertices, glm::vec3 Color);

        static std::vector<float> generateVerts(glm::vec3 Color); 
};

#endif
