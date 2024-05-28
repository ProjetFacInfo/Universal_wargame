#version 420

layout(location = 0) out vec4 FragColor;

in vec4 oCouleur;
in vec2 oTex;
in vec3 oPosMonde;
in vec3 oNormal;

uniform sampler2D gTextureHauteur0;
uniform sampler2D gTextureHauteur1;
uniform sampler2D gTextureHauteur2;
uniform sampler2D gTextureHauteur3;

uniform float gHauteur0 = -2.0;
uniform float gHauteur1 = 0.0;
uniform float gHauteur2 = 50.0;
uniform float gHauteur3 = 80.0;

uniform vec3 gLumiereDirInverse;

vec4 calcTexCouleur() {
    vec4 texCouleur;
    float delta, facteur;
    float hauteur = oPosMonde.y;

    if (hauteur < gHauteur0) {
       texCouleur = texture(gTextureHauteur0, oTex);
    } else if (hauteur < gHauteur1) {
       vec4 Color0 = texture(gTextureHauteur0, oTex);
       vec4 Color1 = texture(gTextureHauteur1, oTex);
       delta = gHauteur1 - gHauteur0;
       facteur = (hauteur - gHauteur0) / delta;
       texCouleur = mix(Color0, Color1, facteur);
    } else if (hauteur < gHauteur2) {
       vec4 Color0 = texture(gTextureHauteur1, oTex);
       vec4 Color1 = texture(gTextureHauteur2, oTex);
       delta = gHauteur2 - gHauteur1;
       facteur = (hauteur - gHauteur1) / delta;
       texCouleur = mix(Color0, Color1, facteur);
    } else if (hauteur < gHauteur3) {
       vec4 Color0 = texture(gTextureHauteur2, oTex);
       vec4 Color1 = texture(gTextureHauteur3, oTex);
       delta = gHauteur3 - gHauteur2;
       facteur = (hauteur - gHauteur2) / delta;
       texCouleur = mix(Color0, Color1, facteur);
    } else {
       texCouleur = texture(gTextureHauteur3, oTex);
    }

    return texCouleur;
}


void main() {
    vec4 texCouleur = calcTexCouleur();
    vec3 normal = normalize(oNormal);
    float diffuse = dot(normal, gLumiereDirInverse);
    diffuse = max(0.3f, diffuse);
    FragColor = oCouleur * texCouleur * diffuse;
}


/* #version 420 */
/*  */
/* layout(location = 0) out vec4 FragColor; */
/*  */
/* in vec4 Color; */
/* in vec2 Tex; */
/* in vec3 WorldPos; */
/* in vec3 Normal; */
/*  */
/* uniform sampler2D gTextureHeight0; */
/* uniform sampler2D gTextureHeight1; */
/* uniform sampler2D gTextureHeight2; */
/* uniform sampler2D gTextureHeight3; */
/*  */
/* uniform float gHeight0 = -2.0; */
/* uniform float gHeight1 = 0.0; */
/* uniform float gHeight2 = 50.0; */
/* uniform float gHeight3 = 80.0; */
/*  */
/* uniform vec3 gReversedLightDir; */
/*  */
/* vec4 CalcTexColor() */
/* { */
/*     vec4 TexColor; */
/*  */
/*     float Height = WorldPos.y; */
/*  */
/*     if (Height < gHeight0) { */
/*        TexColor = texture(gTextureHeight0, Tex); */
/*     } else if (Height < gHeight1) { */
/*        vec4 Color0 = texture(gTextureHeight0, Tex); */
/*        vec4 Color1 = texture(gTextureHeight1, Tex); */
/*        float Delta = gHeight1 - gHeight0; */
/*        float Factor = (Height - gHeight0) / Delta; */
/*        TexColor = mix(Color0, Color1, Factor); */
/*     } else if (Height < gHeight2) { */
/*        vec4 Color0 = texture(gTextureHeight1, Tex); */
/*        vec4 Color1 = texture(gTextureHeight2, Tex); */
/*        float Delta = gHeight2 - gHeight1; */
/*        float Factor = (Height - gHeight1) / Delta; */
/*        TexColor = mix(Color0, Color1, Factor); */
/*     } else if (Height < gHeight3) { */
/*        vec4 Color0 = texture(gTextureHeight2, Tex); */
/*        vec4 Color1 = texture(gTextureHeight3, Tex); */
/*        float Delta = gHeight3 - gHeight2; */
/*        float Factor = (Height - gHeight2) / Delta; */
/*        TexColor = mix(Color0, Color1, Factor); */
/*     } else { */
/*        TexColor = texture(gTextureHeight3, Tex); */
/*     } */
/*  */
/*     return TexColor; */
/* } */
/*  */
/*  */
/* void main() */
/* { */
/*     vec4 TexColor = CalcTexColor(); */
/*  */
/*     vec3 Normal_ = normalize(Normal); */
/*  */
/*     float Diffuse = dot(Normal_, gReversedLightDir); */
/*  */
/*     Diffuse = max(0.3f, Diffuse); */
/*  */
/*     FragColor = Color * TexColor * Diffuse; */
/* } */
