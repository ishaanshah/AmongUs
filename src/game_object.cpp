#include <glm/fwd.hpp>

#include "game_object.hpp"
#include "utils/resource_manager.hpp"
#include "../lib/prettyprint.hpp"

GameObject::GameObject(glm::vec2 Position, glm::vec2 Direction,
                       glm::vec3 Color, std::vector<float> Vertices) : 
                       Position(Position), Direction(Direction),
                       Color(Color), Vertices(Vertices) {
    // Configure VAO/VBO
    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*this->Vertices.size(),
                 this->Vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<glm::vec2> GameObject::GetBoundBox() {
    // TODO: Complete this function
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
    shader.SetVector3f("aColor", this->Color);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->Vertices.size() / 2);
    glBindVertexArray(0);
}
