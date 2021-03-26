#include <glm/fwd.hpp>

#include "game_object.hpp"
#include "utils/resource_manager.hpp"

GameObject::GameObject(glm::vec2 Position, glm::vec2 Direction,
                       std::vector<float> Vertices, bool IsSolid) : 
                       Position(Position), Direction(Direction),
                       Vertices(Vertices), IsSolid(IsSolid), IsVisible(true) {
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

std::pair<glm::vec2, glm::vec2> GameObject::GetBoundBox() {
    float minX = 1e10;
    float minY = 1e10;
    float maxX = -1e10;
    float maxY = -1e10;

    glm::mat4 model = GetModelMatrix();
    for (int i = 0; i < this->Vertices.size() / 5; i++) {
        glm::vec4 vertex = glm::vec4(this->Vertices[i*5],  this->Vertices[i*5+1],
                                     0.0f, 1.0f);
        vertex = model * vertex;
        minX = std::min(vertex.x, minX);
        minY = std::min(vertex.y, minY);

        maxX = std::max(vertex.x, maxX);
        maxY = std::max(vertex.y, maxY);
    }

    return std::make_pair(glm::vec2(minX, minY), glm::vec2(maxX-minX, maxY-minY));
}

std::vector<GameObject *> GameObject::Move(enum Direction direction,
                                         const std::vector<GameObject> &hittables,
                                         float velocity) {
    std::vector<GameObject *> hits;

    glm::vec2 oldPosition(this->Position);
    if (direction == LEFT) {
        this->Position.x -= velocity;
    }
    if (direction == RIGHT) {
        this->Position.x += velocity;
    }
    if (direction == UP) {
        this->Position.y -= velocity;
    }
    if (direction == DOWN) {
        this->Position.y += velocity;
    }

    // TODO: Check collisions
    bool commitMove = true;
    std::pair<glm::vec2, glm::vec2> selfBox = GetBoundBox();
    for (auto hittable: hittables) {
        std::pair<glm::vec2, glm::vec2> hittableBox = hittable.GetBoundBox();

        // Collision along X-Axis
        bool collisionX = (hittableBox.first.x + hittableBox.second.x >= selfBox.first.x && 
                           selfBox.first.x + selfBox.second.x >= hittableBox.first.x);

        // Collision along Y-Axis
        bool collisionY = (hittableBox.first.y + hittableBox.second.y >= selfBox.first.y && 
                           selfBox.first.y + selfBox.second.y >= hittableBox.first.y);

        // Collision only if on both axes
        bool collision = collisionX && collisionY;
        if (collision && !hittable.IsSolid) {
            hits.push_back(&hittable);
        }
        commitMove = commitMove && !(collision && hittable.IsSolid);
    }
    if (!commitMove) {
        this->Position = oldPosition;
    }

    return hits;
}

// Renders the object
void GameObject::Render() {
    if (!IsVisible) {
        return;
    }

    // Get shader
    Shader shader = ResourceManager::GetShader("object").Use();

    // Get transation matrix
    glm::mat4 model = GetModelMatrix();

    // TODO: Figure out flip
    shader.SetMatrix4("model", model);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->Vertices.size() / 5);
    glBindVertexArray(0);
}

glm::mat4 GameObject::GetModelMatrix() {
    // Get translation matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->Position, 0.0f));

    return model;
}
