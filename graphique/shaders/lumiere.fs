#version 420

const int MAX_LUMIERE_PONCTUEL = 2;
const int MAX_LUMIERE_PROJECTEUR = 2;
const float PI = 3.1415926535897932384626433832795;
const float LumiereContourIntesite = 2.0;

in vec2 oTexCoord;
in vec3 oNormal;
in vec3 oPosLocal;
in vec3 oPosMonde;
in vec4 oPosLumiereScene;

out vec4 FragColor;

struct LumiereBase {
    vec3 couleur;
    float intensiteAmbiante;
    float intensiteDiffuse;
};

struct LumiereDirectionnel {
    LumiereBase base;
    vec3 direction;
};

struct Attenuation {
    float constant;
    float linear;
    float exponentiel;
};

struct LumierePonctuel {
    LumiereBase base;
    vec3 posLocal;
    vec3 posMonde;
    Attenuation atten;
};

struct LumiereProjecteur {
    LumierePonctuel base;
    vec3 direction;
    float limite;
};

struct Materiau {
    vec3 couleurAmbiante;
    vec3 couleurDiffuse;
    vec3 couleurSpeculaire;
};

struct PBRMateriau {
    float rugosite;
    bool estMetalique;
    vec3 couleur;
};

uniform LumiereDirectionnel gLumiereDirectionnel;
uniform int gNbreLumierePonctuels;
uniform LumierePonctuel gLumierePonctuels[MAX_LUMIERE_PONCTUEL];
uniform int gNbreLumiereProjecteurs;
uniform LumiereProjecteur gLumiereProjecteurs[MAX_LUMIERE_PROJECTEUR];
uniform Materiau gMateriau;
layout(binding = 0) uniform sampler2D gSampler;
layout(binding = 1) uniform sampler2D gSamplerExposantSpeculaire;
layout(binding = 2) uniform sampler2D gOmbreCarte;
layout(binding = 3) uniform samplerCube gOmbreCubeCarte;
layout(binding = 4) uniform sampler3D gOmbreCarteDecalageTexture;
uniform int gOmbreCarteLargeur = 0;
uniform int gOmbreCarteHauteur = 0;
uniform int gOmbreTailFiltreCarte = 0;
uniform float gOmbreCarteDecalageTaiTexture;
uniform float gOmbreCarteDecalageTaiFiltre;
uniform float gOmbreCarteRandomRayon = 0.0;
uniform vec3 gCameraPosLocal;
uniform bool gLumiereContourActive = false;
uniform bool gExposantSpeculaireActive = false;
uniform bool gEstPBR = false;
uniform PBRMateriau gPBRMateriau;


// Physically Based Rendering (PBR) - Bidirectional Reflectance Distribution Function :
// Fonction qui donne la quantité de lumiere qui est réfléchie vers un spectateur étant
// donné un vecteur de direction de la lumière.
//
// diffuseBRDF = coeffDiffuse * fLambert / PI
// speculaireBRDF = coeffReflexionSpeculaire * fCookTorrance
//
// coeffDiffuse (Refraction) + coeffReflexionSpeculaire (Reflection) = 1
//
// fLambert = materiel couleur
//
// demi-vecteur = normalize(lumiere + vue)
//
// speculaireBRDF = (D * G * F) / (4 * dot(normal, lumiere) * dot(normal, vue))
//
// D : Normal Distribution Function - GGX
// 		(represente le nombre de microfacete dont la lumiere reflete vers la camera)
// G : Geometry Function - Schlick-GGX
// 		(appriximative microfacette auto ombrage)
// F : Fresnel Function
//    (calcule le coefficient de reflexion speculaire)

vec3 approximationSchlickFresnel(float prodScalVueDemiAngle) {
    // reflexion de Fresnel 0.04 pour les non métaux.
    vec3 reflexionFresnel = vec3(0.04);

    if (gPBRMateriau.estMetalique) {
        reflexionFresnel = gPBRMateriau.couleur;
    }

    // approximation de Schlick
    return (reflexionFresnel
        + (1.0 - reflexionFresnel) * pow(clamp(1.0 - prodScalVueDemiAngle, 0.0, 1.0), 5.0));

}


float geometrySmith(float produitScalaire) {
    float k = (gPBRMateriau.rugosite + 1.0) * (gPBRMateriau.rugosite + 1.0) / 8.0;
    float denominateur = produitScalaire * (1.0 - k) + k;
    return (produitScalaire / denominateur);
}


float ggxDistribution(float prodScalNormalDemiAngle) {
    float rugositeCarre = gPBRMateriau.rugosite * gPBRMateriau.rugosite;
    float denominateur = prodScalNormalDemiAngle * prodScalNormalDemiAngle * (rugositeCarre - 1.0) + 1.0;
    return (rugositeCarre / (PI * denominateur * denominateur));
}


vec3 BRDF(LumiereBase lumiere, vec3 posDir, bool estLumiereDir, vec3 normal) {
    vec3 lumiereIntensite = lumiere.couleur * lumiere.intensiteDiffuse;
    vec3 lumiereDir = vec3(0.0);

    if (estLumiereDir) {
        // pour les lumieres directionnelles, la direction est opposée à la direction de la lumiere
        lumiereDir = -posDir.xyz;
    } else {
        // pour les lumieres ponctuelles, la direction est de la surface vers la lumiere
        lumiereDir = posDir - oPosLocal;
        float distanceLumiereSurface = length(lumiereDir);
        lumiereDir = normalize(lumiereDir);
        lumiereIntensite /= (distanceLumiereSurface * distanceLumiereSurface);
    }

    vec3 vueDir = normalize(gCameraPosLocal - oPosLocal);
    vec3 demiAngle = normalize(vueDir + lumiereDir);
    float prodScalNormalDemiAngle = max(dot(normal,demiAngle), 0.0);
    float prodScalVueDemiAngle = max(dot(vueDir, demiAngle), 0.0);
    float prodScalNormalLumiere = max(dot(normal, lumiereDir), 0.0);
    float prodScalNormalVue = max(dot(normal, vueDir), 0.0);

    vec3 coeffReflexionSpeculaire = approximationSchlickFresnel(prodScalVueDemiAngle);
    vec3 coeffDiffuse = 1.0 - coeffReflexionSpeculaire;

    vec3 numerateur  = ggxDistribution(prodScalNormalDemiAngle) * coeffReflexionSpeculaire
                        * geometrySmith(prodScalNormalLumiere) * geometrySmith(prodScalNormalVue);
    float denominateur = 4.0 * prodScalNormalVue * prodScalNormalLumiere + 0.0001;
    vec3 speculaireBRDF = numerateur / denominateur;
    vec3 fLambert = vec3(0.0);

    if (!gPBRMateriau.estMetalique) {
        fLambert = gPBRMateriau.couleur;
    }

    vec3 diffuseBRDF = coeffDiffuse * fLambert / PI;
    return ((diffuseBRDF + speculaireBRDF) * lumiereIntensite * prodScalNormalLumiere);
}


vec3 calcPBRLumiereDirectionnel(vec3 normal) {
    return BRDF(gLumiereDirectionnel.base, gLumiereDirectionnel.direction, true, normal);
}


vec3 calcPBRLumierePonctuel(LumierePonctuel lumierePonctuel, vec3 normal) {
    return BRDF(lumierePonctuel.base, lumierePonctuel.posLocal, false, normal);
}


vec4 calcLumierePBR() {
    vec3 normal = normalize(oNormal);
    vec3 som = calcPBRLumiereDirectionnel(normal);
    for (int i = 0 ;i < gNbreLumierePonctuels ;i++) {
        som += calcPBRLumierePonctuel(gLumierePonctuels[i], normal);
    }

    // High Dynamic Range tonemapping
    som = som / (som + vec3(1.0));

    // correction Gamma
    return vec4(pow(som, vec3(1.0/2.2)), 1.0);
}

float calcLumiereContourFacteur(vec3 pixelVersCamera, vec3 normal) {
    float facteur = dot(pixelVersCamera, normal);
    facteur = 1.0 - facteur;
    facteur = max(0.0, facteur);
    facteur = pow(facteur, LumiereContourIntesite);
    return facteur;
}

float calcFacteurOmbrageLumierePonctuel(vec3 lumiereVersPixel) {
    float distance = length(lumiereVersPixel);
    lumiereVersPixel.y = -lumiereVersPixel.y;
    float sampledDistance = texture(gOmbreCubeCarte, lumiereVersPixel).r;
    float bias = 0.015;

    if (sampledDistance + bias < distance) {
        return 0.25;
    } else {
        return 1.0;
    }
}

vec3 calcCoordOmbre() {
    vec3 projCoords = oPosLumiereScene.xyz / oPosLumiereScene.w;
    vec3 coordOmbre = projCoords * 0.5 + vec3(0.5);
    return coordOmbre;
}

float calcFacteurOmbrageBasic(vec3 lumiereDir, vec3 normal) {
    vec3 coordOmbre = calcCoordOmbre();
    float profondeur = texture(gOmbreCarte, coordOmbre.xy).x;
    float facteurDiffuse = dot(normal, -lumiereDir);
    float bias = mix(0.001, 0.0, facteurDiffuse);
    if (profondeur + bias < coordOmbre.z)
        return 0.05;
    else
        return 1.0;
}


// Percentage Closer Filtering : permer de lisser les ombres générées par une carte
// d'ombre en effectuant un filtrage sur plss texels autour de la position de l'ombre.
float calcFacteurOmbragePCF(vec3 lumiereDir, vec3 normal) {
    if (gOmbreCarteLargeur == 0 || gOmbreCarteHauteur == 0) {
        return 1.0;
    }

    vec3 projCoords = oPosLumiereScene.xyz / oPosLumiereScene.w;
    vec3 coordOmbre = projCoords * 0.5 + vec3(0.5);
    float facteurDiffuse = dot(normal, -lumiereDir);
    float bias = mix(0.001, 0.0, facteurDiffuse);
    float texelLargeur = 1.0 / gOmbreCarteLargeur;
    float texelHauteur = 1.0 / gOmbreCarteHauteur;
    vec2 texelTail = vec2(texelLargeur, texelHauteur);
    float som = 0.0;
    int demiTailFiltreCarte = gOmbreTailFiltreCarte / 2;

    for (int y = -demiTailFiltreCarte ; y < -demiTailFiltreCarte + gOmbreTailFiltreCarte ; y++) {
        for (int x = -demiTailFiltreCarte ; x < -demiTailFiltreCarte + gOmbreTailFiltreCarte ; x++) {
            vec2 decalage = vec2(x, y) * texelTail;
            float profondeur = texture(gOmbreCarte, coordOmbre.xy + decalage).x;

            if (profondeur + bias < coordOmbre.z) {
                som += 0.0;
            } else {
                som += 1.0;
            }
       }
   }

   return (som / float(pow(gOmbreTailFiltreCarte, 2)));
}


float calcFactOmbreAvecSampleAlea(vec3 lumiereDir, vec3 normal) {
    ivec3 decalageCoord;
    vec2 f = mod(gl_FragCoord.xy, vec2(gOmbreCarteDecalageTaiTexture));
    decalageCoord.yz = ivec2(f);
    float som = 0.0;
    int samplesDiv2 = int(gOmbreCarteDecalageTaiFiltre * gOmbreCarteDecalageTaiFiltre / 2.0);
    vec3 coordOmbre = calcCoordOmbre();
    vec4 coordOmbreAjuste = vec4(coordOmbre, 1.0);
    float texelLargeur = 1.0 / gOmbreCarteLargeur;
    float texelHauteur = 1.0 / gOmbreCarteHauteur;
    vec2 texelTail = vec2(texelLargeur, texelHauteur);
    float facteurDiffuse = dot(normal, -lumiereDir);
    float bias = mix(0.001, 0.0, facteurDiffuse);
    float profondeur = 0.0;

    for (int i = 0 ; i < 4 ; i++) {
        decalageCoord.x = i;
        vec4 decalages = texelFetch(gOmbreCarteDecalageTexture, decalageCoord, 0) * gOmbreCarteRandomRayon;
        coordOmbreAjuste.xy = coordOmbre.xy + decalages.rg * texelTail;
        profondeur = texture(gOmbreCarte, coordOmbreAjuste.xy).x;
        if (profondeur + bias < coordOmbre.z) {
           som += 0.0;
        } else {
           som += 1.0;
        }

        coordOmbreAjuste.xy = coordOmbre.xy + decalages.ba * texelTail;
        profondeur = texture(gOmbreCarte, coordOmbreAjuste.xy).x;
        if (profondeur + bias < coordOmbre.z) {
           som += 0.0;
        } else {
           som += 1.0;
        }
    }

    float ombre = som / 8.0;

    if (ombre != 0.0 && ombre != 1.0) {
        for (int i = 4 ; i < samplesDiv2 ; i++) {
            decalageCoord.x = i;
            vec4 decalages = texelFetch(gOmbreCarteDecalageTexture, decalageCoord, 0) * gOmbreCarteRandomRayon;
            coordOmbreAjuste.xy = coordOmbre.xy + decalages.rg * texelTail;
            profondeur = texture(gOmbreCarte, coordOmbreAjuste.xy).x;
            if (profondeur + bias < coordOmbre.z) {
               som += 0.0;
            } else {
               som += 1.0;
            }

            coordOmbreAjuste.xy = coordOmbre.xy + decalages.ba * texelTail;
            profondeur = texture(gOmbreCarte, coordOmbreAjuste.xy).x;
            if (profondeur + bias < coordOmbre.z) {
               som += 0.0;
            } else {
               som += 1.0;
            }
        }

        ombre = som / float(samplesDiv2 * 2.0);
    }
    return ombre;
}


float calcFacteurOmbrage(vec3 lumiereDir, vec3 normal) {
    float facteur = 0.0;

    if (gOmbreCarteRandomRayon > 0.0) {
        facteur = calcFactOmbreAvecSampleAlea(lumiereDir, normal);
    } else if (gOmbreTailFiltreCarte > 0){
        facteur = calcFacteurOmbragePCF(lumiereDir, normal);
    } else {
        facteur = calcFacteurOmbrageBasic(lumiereDir, normal);
    }

    return facteur;
}

// Lumiere directionelle :
//
// Loi en cosinus de Lambert : "l'intensité de la lumiere depend du cos de l'angle
// entre le vecteur normal à la surface et le vecteur de la lumiere."
//
// produit_scalaire(u, v) = |u| * |v| * cos(theta), avec theta l'angle entre u et v
// si |u| = 1 et |v| = 1, alors produit_scalaire(u, v) = cos(theta).
//
// normal du sommet : la moyenne des normals des triangle qui composent le sommet
// Pour interpoler l'intesité de la lumiere sur les surfaces entre deux sommets

// Source de lumiere projecteur :
//
// On a l'intervale [X - 1], et on veut passer à l'intervale [0 - 1]
// on cherche une transformation affine, donc cela revient au meme
// qu'une equation d'une droite du type f(x) = ax + b.
//
// On sait que :
// f(X) : aX + b = 0
// f(1) : a * 1 + b = 1
// ...
// f(X1) = (X1 - X) / (1 - X)

vec4 calcLumiereInterne
(LumiereBase lumiere, vec3 lumiereDir, vec3 normal, float facteurOmbrage) {
    vec4 couleurAmbiante = vec4(lumiere.couleur, 1.0f) * lumiere.intensiteAmbiante * vec4(gMateriau.couleurAmbiante, 1.0f);
    float facteurDiffuse = dot(normal, -lumiereDir);
    vec4 couleurDiffuse = vec4(0, 0, 0, 0);
    vec4 couleurSpeculaire = vec4(0, 0, 0, 0);
    vec4 couleurContour = vec4(0, 0, 0, 0);

    if (facteurDiffuse > 0) {
        couleurDiffuse = vec4(lumiere.couleur, 1.0f) * lumiere.intensiteDiffuse
                            * vec4(gMateriau.couleurDiffuse, 1.0f) * facteurDiffuse;

        vec3 pixelVersCamera = normalize(gCameraPosLocal - oPosLocal);
        vec3 lumiereReflet = normalize(reflect(lumiereDir, normal));
        float facteurSpeculaire = dot(pixelVersCamera, lumiereReflet);

        if (facteurSpeculaire > 0) {
            float ExposantSpeculaire = 128.0;

            if (gExposantSpeculaireActive) {
                ExposantSpeculaire = texture(gSamplerExposantSpeculaire, oTexCoord).r * 255.0;
            }

            facteurSpeculaire = pow(facteurSpeculaire, ExposantSpeculaire);
            couleurSpeculaire = vec4(lumiere.couleur, 1.0f) * lumiere.intensiteDiffuse
                                * vec4(gMateriau.couleurSpeculaire, 1.0f) * facteurSpeculaire;
        }

        if (gLumiereContourActive) {
           float facteur = calcLumiereContourFacteur(pixelVersCamera, normal);
           couleurContour = couleurDiffuse * facteur;
        }
    }

    return (couleurAmbiante + facteurOmbrage * (couleurDiffuse + couleurSpeculaire + couleurContour));
}


vec4 calcLumiereDirectionnel(vec3 normal) {
    float facteurOmbrage = calcFacteurOmbrage(gLumiereDirectionnel.direction, normal);
    return calcLumiereInterne(gLumiereDirectionnel.base, gLumiereDirectionnel.direction, normal, facteurOmbrage);
}


vec4 calcLumierePonctuel(LumierePonctuel lumierePonctuel, vec3 normal, bool estLumiereProj) {
    vec3 lumiereDirMonde = oPosMonde - lumierePonctuel.posMonde;
    float facteurOmbrage = 0.0;

    if (estLumiereProj) {
        facteurOmbrage = calcFacteurOmbrage(lumiereDirMonde, normal);
    } else {
        facteurOmbrage = calcFacteurOmbrageLumierePonctuel(lumiereDirMonde);
    }

    vec3 lumiereDirLocal = oPosLocal - lumierePonctuel.posLocal;
    float distance = length(lumiereDirLocal);
    lumiereDirLocal = normalize(lumiereDirLocal);
    vec4 couleur = calcLumiereInterne(lumierePonctuel.base, lumiereDirLocal, normal, facteurOmbrage);
    float attenuation =  lumierePonctuel.atten.constant + lumierePonctuel.atten.linear * distance
                        + lumierePonctuel.atten.exponentiel * distance * distance;

    return couleur / attenuation;
}


vec4 calcLumiereProjecteur(LumiereProjecteur lumiereProj, vec3 normal) {
    vec3 lumiereVersPixel = normalize(oPosLocal - lumiereProj.base.posLocal);
    float projFacteur = dot(lumiereVersPixel, lumiereProj.direction);

    if (projFacteur > lumiereProj.limite) {
        vec4 couleur = calcLumierePonctuel(lumiereProj.base, normal, true);
        // f(X1) = (X1 - X) / (1 - X)
        float lumiereProjIntensite = (projFacteur - lumiereProj.limite)/(1.0 - lumiereProj.limite);
        return couleur * lumiereProjIntensite;
    }

    return vec4(0,0,0,0);
}

vec4 calcLumiereDePhong() {
    vec3 normal = normalize(oNormal);
    vec4 som = calcLumiereDirectionnel(normal);

    for (int i = 0 ;i < gNbreLumierePonctuels ;i++) {
        som += calcLumierePonctuel(gLumierePonctuels[i], normal, false);
    }

    for (int i = 0 ;i < gNbreLumiereProjecteurs ;i++) {
        som += calcLumiereProjecteur(gLumiereProjecteurs[i], normal);
    }

    return texture(gSampler, oTexCoord.xy) * som;
}



void main() {
    if (gEstPBR) {
        FragColor = calcLumierePBR();
    } else {
        FragColor = calcLumiereDePhong();
    }
}
