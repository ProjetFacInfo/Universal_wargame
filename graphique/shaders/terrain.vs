#version 420

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTex;
layout (location = 2) in vec3 InNormal;

uniform mat4 gVP;
uniform float gHauteurMin;
uniform float gHauteutMax;

out vec4 oCouleur;
out vec2 oTex;
out vec3 oPosMonde;
out vec3 oNormal;

void main() {
    gl_Position = gVP * vec4(inPosition, 1.0);
    float delta = gHauteutMax - gHauteurMin;
    float ratioHauteur = (inPosition.y - gHauteurMin) / delta;
    float c = ratioHauteur * 0.8 + 0.2;
    oCouleur = vec4(c, c, c, 1.0);
    oTex = inTex;
    oPosMonde = inPosition;
    oNormal = InNormal;
}

/* TODO : supprimer */
/* layout (location = 0) in vec3 Position; */
/* layout (location = 1) in vec2 TexCoord; */
/* layout (location = 2) in vec3 InNormal; */
/*  */
/* uniform mat4 gVP; */
/* uniform float gMinHeight; */
/* uniform float gMaxHeight; */
/*  */
/* out vec4 Color; */
/* out vec2 Tex; */
/* out vec3 WorldPos; */
/* out vec3 Normal; */
/*  */
/* void main() */
/* { */
/*     gl_Position = gVP * vec4(Position, 1.0); */
/*  */
/*     float DeltaHeight = gMaxHeight - gMinHeight; */
/*  */
/*     float HeightRatio = (Position.y - gMinHeight) / DeltaHeight; */
/*  */
/*     float c = HeightRatio * 0.8 + 0.2; */
/*  */
/*     Color = vec4(c, c, c, 1.0); */
/*  */
/*     Tex = TexCoord; */
/*  */
/*     WorldPos = Position; */
/*  */
/*     Normal = InNormal; */
/* } */
