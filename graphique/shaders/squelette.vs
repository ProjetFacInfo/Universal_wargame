#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in ivec4 osID;
layout (location = 4) in vec4 poids;

const int MAX_OS = 200;

uniform mat4 gMVP;
uniform mat4 gOs[MAX_OS];
uniform mat4 gMonde;
uniform mat4 gLumiereMVP;
uniform vec4 gClipPlan;

out vec2 oTexCoord;
out vec3 oNormal;
out vec3 oPosLocal;
out vec3 oPosMonde;
out vec4 oPosLumiereScene;

void main() {
    mat4 osTransform = gOs[osID[0]] * poids[0];
    osTransform     += gOs[osID[1]] * poids[1];
    osTransform     += gOs[osID[2]] * poids[2];
    osTransform     += gOs[osID[3]] * poids[3];

    vec4 osPosLocal = osTransform * vec4(position, 1.0);
    gl_Position = gMVP * osPosLocal;
    oTexCoord = texCoord;
    oNormal = normal;
    oPosLocal = osPosLocal.xyz;
    oPosMonde = (gMonde * osPosLocal).xyz;
    oPosLumiereScene = gLumiereMVP * vec4(position, 1.0);
    gl_ClipDistance[0] = dot(vec4(position, 1.0), gClipPlan);
}
