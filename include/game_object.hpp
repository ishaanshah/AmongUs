#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include "glm/fwd.hpp"

#include "utils/shader.hpp"

class GameObject {
    public:
        glm::vec2 Position, Direction;
        glm::vec3 Color;

        // Constructor
        GameObject(glm::vec2 Position, glm::vec2 Direction,
                   glm::vec3 Color, std::vector<float> Vertices);

        // Gets bounding box of the object
        std::vector<glm::vec2> GetBoundBox();

        // Render the object
        void Render();
    private:
        unsigned int VAO;
        std::vector<float> Vertices;
};

#endif
