#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "utils/shader.hpp"


// Holds all state information relevant to a character as loaded using FreeType
struct Char {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};


class TextRenderer {
public:
    // Holds a list of pre-compiled Characters
    std::map<char, Char> Characters; 
    // Shader used for text rendering
    Shader TextShader;

    TextRenderer(unsigned int width, unsigned int height);

    void Load(std::string font, unsigned int fontSize);

    void RenderText(std::string text, float x, float y,
                    float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    unsigned int VAO, VBO;
};

#endif 
