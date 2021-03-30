#include "constants.hpp"
#include "objects/character.hpp"

Character::Character(glm::vec2 Position, glm::vec2 Direction,
                     std::vector<float> Vertices, glm::vec3 Color) :
                     GameObject(Position, Direction, Vertices, false), Color(Color) {  }

std::vector<float> Character::GenerateVerts(glm::vec3 Color) {
    std::vector<float> character {
        0.0f, 0.0f, Color.r, Color.g, Color.b,
        CHARACTER_SIZE, 0.0f, Color.r, Color.g, Color.b,
        CHARACTER_SIZE, CHARACTER_SIZE / 1.3f, Color.r, Color.g, Color.b,

        0.0f, 0.0f, Color.r, Color.g, Color.b,
        0.0f, (float)CHARACTER_SIZE / 1.3f, Color.r, Color.g, Color.b,
        CHARACTER_SIZE, CHARACTER_SIZE / 1.3f, Color.r, Color.g, Color.b,
    };

    float angle = glm::radians(360.0f / CIRCLE_RES);
    float center = (float)CHARACTER_SIZE / 2;
    for (int i = 0; i < CIRCLE_RES / 2; i++) {
        std::vector<float> triangle {
            center, 0.0f, Color.r, Color.g, Color.b,

            center + center*cosf(angle*i), -center*sinf(angle*i),
            Color.r, Color.g, Color.b,

            center + center*cosf(angle*(i+1)), -center*sinf(angle*(i+1)),
            Color.r, Color.g, Color.b
        };
        character.insert(character.end(), triangle.begin(), triangle.end());
    }

    std::vector<float> visor {
        CHARACTER_SIZE / 2.5f, 0.0f, COLOR_CYAN.r, COLOR_CYAN.g, COLOR_CYAN.b,
        CHARACTER_SIZE / 1.1f, 0.0f, COLOR_CYAN.r, COLOR_CYAN.g, COLOR_CYAN.b,
        CHARACTER_SIZE / 1.1f, -CHARACTER_SIZE / 3.6f, COLOR_CYAN.r, COLOR_CYAN.g, COLOR_CYAN.b,

        CHARACTER_SIZE / 2.5f, 0.0f, COLOR_CYAN.r, COLOR_CYAN.g, COLOR_CYAN.b,
        CHARACTER_SIZE / 2.5f, -CHARACTER_SIZE / 3.6f, COLOR_CYAN.r, COLOR_CYAN.g, COLOR_CYAN.b,
        CHARACTER_SIZE / 1.1f, -CHARACTER_SIZE / 3.6f, COLOR_CYAN.r, COLOR_CYAN.g, COLOR_CYAN.b,

    };

    character.insert(character.end(), visor.begin(), visor.end());

    return character;
}

void Character::Hit(int &score, int &health, int &tasks, const bool lights,
                    GameObject *Imposter, std::vector<GameObject *> &coins,
                    std::vector<GameObject *> &bombs) {
    health = 0;
}
