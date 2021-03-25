#include <glm/fwd.hpp>

#include "game_object.hpp"
#include "utils/resource_manager.hpp"

GameObject::GameObject(glm::vec2 Position, glm::vec2 Direction,
                       std::vector<float> Vertices, bool IsSolid) : 
                       Position(Position), Direction(Direction),
                       Vertices(Vertices), IsSolid(IsSolid) {
    // Configure VAO/VBO
    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*this->Vertices.size(),
                 this->Vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);

    // Coordinate data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    // Color data
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<glm::vec2> GameObject::GetBoundBox() {
    // TODO: Complete this function
}

std::vector<GameObject> GameObject::Move(enum Direction direction,
                                         const std::vector<GameObject> &hittables,
                                         float velocity) {
    std::vector<GameObject> hits;
    if (this->IsSolid) {
        return hits;
    }

    return hits;
}

// Renders the object
void GameObject::Render() {
    // Get shader
    Shader shader = ResourceManager::GetShader("object").Use();

    // Get transation matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(Position, 0.0f));

    // TODO: Figure out flip
    shader.SetMatrix4("model", model);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->Vertices.size() / 5);
    glBindVertexArray(0);
}
