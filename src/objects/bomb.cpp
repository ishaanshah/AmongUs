#include "constants.hpp"
#include "objects/bomb.hpp"

Bomb::Bomb(glm::vec2 Position, glm::vec2 Direction,
                     std::vector<float> Vertices) :
                     GameObject(Position, Direction, Vertices, false, false),
                     Color(COLOR_GREY) {  }

std::vector<float> Bomb::GenerateVerts() {
    const glm::vec3 color = COLOR_GREY;

    std::vector<float> bomb;

    float radius = BOMB_SIZE / 2.0f;
    float angle = glm::radians(360.0f / CIRCLE_RES);
    for (int i = 0; i < CIRCLE_RES; i++) {
        std::vector<float> triangle {
            0.0f, 0.0f, color.r, color.g, color.b,
            radius*cosf(angle*i), -radius*sinf(angle*i),
            color.r, color.g, color.b,

            radius*cosf(angle*(i+1)), -radius*sinf(angle*(i+1)),
            color.r, color.g, color.b
        };
        bomb.insert(bomb.end(), triangle.begin(), triangle.end());
    }

    return bomb;
}

void Bomb::Hit(int &score, int &health, int &tasks, const bool lights,
               GameObject *Imposter, std::vector<GameObject *> &coins,
               std::vector<GameObject *> &bombs) {
    health -= 10;
    this->IsVisible = false;
}
