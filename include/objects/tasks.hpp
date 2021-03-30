#ifndef TASK_HPP
#define TASK_HPP

#include <vector>

#include <glm/glm.hpp>

#include "game_object.hpp"

class Task : public GameObject {
    public:
        glm::vec3 Color;

        Task(glm::vec2 Position, glm::vec2 Direction,
             std::vector<float> Vertices, glm::vec3 Color);

        static std::vector<float> GenerateVerts(glm::vec3 Color); 
};

class TaskVaporise : public Task {
    public:
        glm::vec3 Color;

        TaskVaporise(glm::vec2 Position, glm::vec2 Direction,
                     std::vector<float> Vertices, glm::vec3 Color);

        void Hit(int &score, int &health, int &tasks, const bool lights,
                 GameObject *Imposter, std::vector<GameObject *> &coins,
                 std::vector<GameObject *> &bombs);
};

class TaskPowerups: public Task {
    public:
        glm::vec3 Color;

        TaskPowerups(glm::vec2 Position, glm::vec2 Direction,
                     std::vector<float> Vertices, glm::vec3 Color);

        void Hit(int &score, int &health, int &tasks, const bool lights,
                 GameObject *Imposter, std::vector<GameObject *> &coins,
                 std::vector<GameObject *> &bombs);
};

#endif
