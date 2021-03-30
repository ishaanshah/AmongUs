#include "constants.hpp"
#include "objects/tasks.hpp"

Task::Task(glm::vec2 Position, glm::vec2 Direction,
           std::vector<float> Vertices, glm::vec3 Color) :
           GameObject(Position, Direction, Vertices, false), Color(Color) {  }

std::vector<float> Task::GenerateVerts(glm::vec3 Color) {
    std::vector<float> character {
        -TASK_SIZE / 2.0f, TASK_SIZE / 2.0f, Color.r, Color.g, Color.b,
        -TASK_SIZE / 2.0f, -TASK_SIZE / 2.0f, Color.r, Color.g, Color.b,
        TASK_SIZE / 2.0f, TASK_SIZE / 2.0f, Color.r, Color.g, Color.b,

        -TASK_SIZE / 2.0f, -TASK_SIZE / 2.0f, Color.r, Color.g, Color.b,
        TASK_SIZE / 2.0f, TASK_SIZE / 2.0f, Color.r, Color.g, Color.b,
        TASK_SIZE / 2.0f, -TASK_SIZE / 2.0f, Color.r, Color.g, Color.b,
    };

    return character;
}

TaskVaporise::TaskVaporise(glm::vec2 Position, glm::vec2 Direction,
                           std::vector<float> Vertices, glm::vec3 Color) :
                           Task(Position, Direction, Vertices, Color),
                           Color(Color) {  }

void TaskVaporise::Hit(int &score, int &health, int &tasks, const bool lights,
                       GameObject *Imposter, std::vector<GameObject *> &coins,
                       std::vector<GameObject *> &bombs) {
    Imposter->IsVisible = false;
    tasks -= 1;
    this->IsVisible = false;
}

TaskPowerups::TaskPowerups(glm::vec2 Position, glm::vec2 Direction,
                           std::vector<float> Vertices, glm::vec3 Color) :
                           Task(Position, Direction, Vertices, Color),
                           Color(Color) {  }

void TaskPowerups::Hit(int &score, int &health, int &tasks, const bool lights,
                       GameObject *Imposter, std::vector<GameObject *> &coins,
                       std::vector<GameObject *> &bombs) {
    for (auto coin : coins) {
        coin->IsVisible = true;
    }
    for (auto bomb : bombs) {
        bomb->IsVisible = true;
    }
    tasks -= 1;
    this->IsVisible = false;
}
