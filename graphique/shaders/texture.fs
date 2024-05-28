#version 420

layout(location = 0) out vec4 FragColor;

uniform sampler2D gSampler;

in vec2 oTexCoord;

void main() {
    FragColor = texture(gSampler, oTexCoord.xy);
}
