#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 gMVP;
uniform mat4 gLumiereMVP;
uniform mat4 gMonde;
uniform vec4 gClipPlan;

out vec2 oTexCoord;
out vec3 oNormal;
out vec3 oPosLocal;
out vec3 oPosMonde;
out vec4 oPosLumiereScene;

void main() {
    vec4 pos4 = vec4(position, 1.0);
    gl_Position = gMVP * pos4;
    oTexCoord = texCoord;
    oNormal = normal;
    oPosLocal = position;
    oPosMonde = (gMonde * pos4).xyz;
    oPosLumiereScene = gLumiereMVP * pos4;

    gl_ClipDistance[0] = dot(vec4(position, 1.0), gClipPlan);
}
