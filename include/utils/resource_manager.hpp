/* Headers for ResourceManager class */
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>

#include <glad/glad.h>

#include "utils/shader.hpp"

class ResourceManager {
    public:
        // Resource storage
        static std::map<std::string, Shader> Shaders;

        // Loads (and generates) a shader program from file loading vertex, fragment
        // (and geometry) shader's source code. If gShaderFile is not nullptr,
        // it also loads a geometry shader
        static Shader LoadShader(const char *vShaderFile, const char *fShaderFile,
                                 const char *gShaderFile, std::string name);

        // Retrieves a stored sader
        static Shader GetShader(std::string name);

        // Properly de-allocates all loaded resources
        static void Clear();
    private:
        // Private constructor, that is we do not want any actual resource manager objects.
        // Its members and functions should be publicly available (static).
        ResourceManager() { }

        // Loads and generates a shader from file
        static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
};

#endif
