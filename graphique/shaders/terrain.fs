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
uniform sampler2D gTextureHauteur4;
uniform sampler2D gTextureHauteur5;

uniform float gHauteur0 = -2.0f;
uniform float gHauteur1 = -1.0f;
uniform float gHauteur2 = 0.0f;
uniform float gHauteur3 = 50.0f;
uniform float gHauteur4 = 80.0f;
uniform float gHauteur5 = 200.0f;

uniform vec3 gLumiereDirInverse;

vec4 calcTexCouleur() {
    vec4 texCouleur, couleur0, couleur1;
    float delta, facteur;
    float hauteur = oPosMonde.y;

    if (hauteur < gHauteur0) {
       texCouleur = texture(gTextureHauteur0, oTex);
    } else if (hauteur < gHauteur1) {
       couleur0 = texture(gTextureHauteur0, oTex);
       couleur1 = texture(gTextureHauteur1, oTex);
       delta = gHauteur1 - gHauteur0;
       facteur = (hauteur - gHauteur0) / delta;
       texCouleur = mix(couleur0, couleur1, facteur);
    } else if (hauteur < gHauteur2) {
       couleur0 = texture(gTextureHauteur1, oTex);
       couleur1 = texture(gTextureHauteur2, oTex);
       delta = gHauteur2 - gHauteur1;
       facteur = (hauteur - gHauteur1) / delta;
       texCouleur = mix(couleur0, couleur1, facteur);
    } else if (hauteur < gHauteur3) {
       couleur0 = texture(gTextureHauteur2, oTex);
       couleur1 = texture(gTextureHauteur3, oTex);
       delta = gHauteur3 - gHauteur2;
       facteur = (hauteur - gHauteur2) / delta;
       texCouleur = mix(couleur0, couleur1, facteur);
    } else if (hauteur < gHauteur4) {
       couleur0 = texture(gTextureHauteur3, oTex);
       couleur1 = texture(gTextureHauteur4, oTex);
       delta = gHauteur4 - gHauteur3;
       facteur = (hauteur - gHauteur3) / delta;
       texCouleur = mix(couleur0, couleur1, facteur);
    } else if (hauteur < gHauteur5) {
       couleur0 = texture(gTextureHauteur4, oTex);
       couleur1 = texture(gTextureHauteur5, oTex);
       delta = gHauteur5 - gHauteur4;
       facteur = (hauteur - gHauteur4) / delta;
       texCouleur = mix(couleur0, couleur1, facteur);
    } else {
       texCouleur = texture(gTextureHauteur5, oTex);
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
