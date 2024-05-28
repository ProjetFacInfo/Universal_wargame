#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 gMVP = mat4(1.0);

out vec2 oTexCoord;

void main() {
    gl_Position = gMVP * vec4(position, 1.0);
    oTexCoord = texCoord;
}
