#pragma once

#include "math3D.hh"
#include "texture.hh"

// Physically Based Rendering mateaux
struct PBRMateriau {
    PBRMateriau()
        :couleur(Vecteur3f(0.0f, 0.0f, 0.0f)), rugosite(0.0f), estMetalique(false) {}

    Vecteur3f couleur;
    float rugosite;
    bool estMetalique;
};


struct Materiau {
    Materiau()
        :  couleurAmbiante(Vecteur3f(0.0f, 0.0f, 0.0f))
         , couleurDiffuse(Vecteur3f(0.0f, 0.0f, 0.0f))
         , couleurSpeculaire(Vecteur3f(0.0f, 0.0f, 0.0f))
         , pDiffuse(nullptr), pExposantSpeculaire(nullptr) {}

    Vecteur3f couleurAmbiante;
    Vecteur3f couleurDiffuse;
    Vecteur3f couleurSpeculaire;

    PBRMateriau PBRmateriau;

    Texture * pDiffuse;
    Texture * pExposantSpeculaire;
};
