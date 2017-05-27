#version 330 core

uniform mat4 modelViewProjectionMatrix;

in vec2 position;

void main() {
    gl_Position = modelViewProjectionMatrix * vec4(position, 0.0f, 1.0f);
}