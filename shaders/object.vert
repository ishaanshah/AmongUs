#version 330 core
layout (location = 0) in vec2 aPos; // The position variable has attribute position 0
layout (location = 1) in vec3 aColor; // The color variable has attribute position 1

out vec3 ourColor; // Output a color to the fragment shader

uniform mat4 model;
uniform mat4 projection;
uniform vec2 lightPos;
uniform int lightsOn;

void main() {
    gl_Position = projection * model * vec4(aPos, 0.0f, 1.0f);
    float distance = length(vec4(lightPos, 0.0f, 1.0f) - model*vec4(aPos, 0.0f, 1.0f));
    float attenuation = 1 / (1.0f + 0.0009f*distance + 0.00010f*distance*distance);
    if (lightsOn == 1) {
        attenuation = 1.0f;
    }
    ourColor = attenuation * aColor; // Set ourColor to the input color we got from the vertex data
}

