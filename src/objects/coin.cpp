#include "constants.hpp"
#include "objects/coin.hpp"

Coin::Coin(glm::vec2 Position, glm::vec2 Direction,
                     std::vector<float> Vertices) :
                     GameObject(Position, Direction, Vertices, false, false),
                     Color(COLOR_YELLOW) {  }

std::vector<float> Coin::GenerateVerts() {
    const glm::vec3 color = COLOR_YELLOW;

    std::vector<float> coin;

    float radius = COIN_SIZE / 2.0f;
    float angle = glm::radians(360.0f / CIRCLE_RES);
    for (int i = 0; i < CIRCLE_RES; i++) {
        std::vector<float> triangle {
            0.0f, 0.0f, color.r, color.g, color.b,
            radius*cosf(angle*i), -radius*sinf(angle*i),
            color.r, color.g, color.b,

            radius*cosf(angle*(i+1)), -radius*sinf(angle*(i+1)),
            color.r, color.g, color.b
        };
        coin.insert(coin.end(), triangle.begin(), triangle.end());
    }

    return coin;
}

void Coin::Hit(int &score, int &health, int &tasks, const bool lights,
               GameObject *Imposter, std::vector<GameObject *> &coins,
               std::vector<GameObject *> &bombs) {
    score += lights ? 10 : 20;
    this->IsVisible = false;
}
