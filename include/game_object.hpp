#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "utils/shader.hpp"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class GameObject {
    public:
        bool IsSolid, IsVisible;
        glm::vec2 Position, Direction;

        // Constructor
        GameObject(glm::vec2 Position, glm::vec2 Direction,
                   std::vector<float> Vertices, bool IsSolid,
                   bool IsVisible = true);

        // Gets bounding box of the object
        std::pair<glm::vec2, glm::vec2> GetBoundBox();

        // Move the object, returns a list of objects which have been hit
        std::vector<GameObject *> Move(enum Direction direction,
                                       const std::vector<GameObject *> &hittables,
                                       float velocity);

        // Render the object
        void Render();

        glm::mat4 GetModelMatrix();

        // Implementation to be done by child classes
        virtual void Hit(int &score, int &health, int &tasks, const bool lights,
                         GameObject *Imposter, std::vector<GameObject *> &coins,
                         std::vector<GameObject *> &bombs) {  };
    private:
        unsigned int VAO;
        std::vector<float> Vertices;
};

#endif
