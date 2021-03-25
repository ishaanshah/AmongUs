#version 330 core
layout (location = 0) in vec2 aPos; // The position variable has attribute position 0
layout (location = 1) in vec3 aColor; // The color variable has attribute position 1

out vec3 ourColor; // Output a color to the fragment shader

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(aPos, 0.0f, 1.0f);
    ourColor = aColor; // Set ourColor to the input color we got from the vertex data
}

