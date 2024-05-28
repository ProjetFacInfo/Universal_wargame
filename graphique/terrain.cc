
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <string>
#include <fstream>
#include <iostream>
#include <string>

#include "terrain.hh"
#include "GLTerrainTextureUnit.hh"
#include "logiciel_tiers/stb_image_write.h"

Terrain::Terrain()
   :_tailleTerrain(0), _mondeEchelle(1.0f),
      _pTextures{0}, _textureEchelle(1.0f),
      _hauteurMin(0.0f), _hauteurMax(0.0f) {}

Terrain::~Terrain() {
    effacer();
}


void Terrain::effacer() {
    _carteHauteur.effacer();
    _triangleList.effacer();
}



void Terrain::initTerrain(float mondeEchelle, float textureEchelle, const std::vector<std::string>& textureNomFic)
{
    if (!_terrainTech.init()) {
        printf("erreur initialisation tech\n");
        exit(0);
    }

    if (textureNomFic.size() != nbreElmDansTab(_pTextures)) {
      printf("%s:%d - nombre de textures fourni (%d) n'est pas égale au taille du tableau de texture (%d)\n", __FILE__, __LINE__, (int)textureNomFic.size(), (int)nbreElmDansTab(_pTextures));
        exit(0);
    }

    _mondeEchelle = mondeEchelle;
    _textureEchelle = textureEchelle;

    for (int i = 0 ; i < nbreElmDansTab(_pTextures) ; i++) {
        _pTextures[i] = new Texture(GL_TEXTURE_2D);
        _pTextures[i]->charger(textureNomFic[i]);
    }
}


float Terrain::getHauteurInterpoler(float x, float z) const {
    float hauteur = getHauteur((int)x, (int)z);
    if (((int)x + 1 >= _tailleTerrain) ||  ((int)z + 1 >= _tailleTerrain)) {
        return hauteur;
    }

    float hauteurXsuiv = getHauteur((int)x + 1, (int)z);
    float ratioX = x - floorf(x);
    float hauteurInterpolerX = (float)(hauteurXsuiv - hauteur) * ratioX + (float)hauteur;
    float NextZHeight = getHauteur((int)x, (int)z + 1);
    float ratioZ = z - floorf(z);
    float hauteurInterpolerZ = (float)(NextZHeight - hauteur) * ratioZ + (float)hauteur;
    return (hauteurInterpolerX + hauteurInterpolerZ) / 2.0f;
}

float Terrain::getHauteurInterpolerBaryCentrique(float x, float z) const { int coordX = (int)x;
    int coordZ = (int)z;

    float pos = getHauteur(coordX, coordZ);

    if (
           (coordX + 1 >= _tailleTerrain)
        || (coordZ + 1 >= _tailleTerrain)
        || (coordX < 0)
        || (coordZ < 0)
        ) {
        return pos;
    }


    float hauteur;

    if (x <= (1 - z)) {
        hauteur = baryCentriqueCoord(
                    Vecteur3f(0, getHauteur(coordX, coordZ), 0)
                    , Vecteur3f(1, getHauteur(coordX, coordZ + 1), 0)
                    , Vecteur3f(1, getHauteur(coordX + 1, coordZ + 1), 1)
                    , Vecteur2f(coordX, coordZ)
                    );
    } else {
        hauteur = baryCentriqueCoord(
                    Vecteur3f(0, getHauteur(coordX, coordZ), 0)
                    , Vecteur3f(1, getHauteur(coordX + 1, coordZ + 1), 1)
                    , Vecteur3f(0, getHauteur(coordX + 1, coordZ), 1)
                    , Vecteur2f(coordX, coordZ)
                    );
    }
    return hauteur;
}

float Terrain::getHauteurMonde(float x, float z) const {
    float hauteurCarteX = x / _mondeEchelle;
    float hauteurCarteZ = z / _mondeEchelle;

    return getHauteurInterpoler(hauteurCarteX, hauteurCarteZ);
    // return getHauteurInterpolerBaryCentrique(hauteurCarteX, hauteurCarteZ);
}

Vecteur3f Terrain::constrainPosToTerrain(const Vecteur3f& Pos) {
    Vecteur3f NewPos = Pos;

    if (Pos.x < 0.0f) {
        NewPos.x = 0.0f;
    }

    if (Pos.z < 0.0f) {
        NewPos.z = 0.0f;
    }

    if (Pos.x >= (getTailleMonde() - 1.0f)) {
        NewPos.x = getTailleMonde() - 2.0f;
    }

    if (Pos.z >= (getTailleMonde() - 1.0f)) {
        NewPos.z = getTailleMonde() - 2.0f;
    }

    NewPos.y = getHauteurMonde(Pos.x, Pos.z);
    NewPos.y += 10.0f;

    return NewPos;
}

void Terrain::creerCarte(const char * pFileName, int size, float hauteurMin, float hauteurMax) {
    _tailleTerrain = size ;
    setHauteurMinMax(hauteurMin, hauteurMax);
    chargerCarte(pFileName, _tailleTerrain);
    _carteHauteur.normaliser(hauteurMin, hauteurMax);
    _triangleList.creerTriangleList(_tailleTerrain, _tailleTerrain, this);
    // std::cout<<"ok"<<std::endl;
}

void Terrain::chargerCarte(const char* pFilename, int size) {
    std::ifstream fic(pFilename);

    float * data = (float * )malloc(size * size * sizeof(float));
    int ind(0);
    if(not fic)	{
        std::cout<<"ERREUR,Impossible d'ouvrir le fichier."<<std::endl;
    } else{
        std::string mot;
        float hauteur;

        while(fic >> mot){
            hauteur = std::stof(mot);
            data[ind++] = hauteur;
        }
    }
    std::cout << "Terrain size : " << size << std::endl;
    _carteHauteur.initTableau2D(size, size, data);
}

// TODO : supprimer
// void Terrain::LoadFromFile(const char* pFilename)
// {
//     LoadhauteurCarteFile(pFilename);
//
//     _triangleList.creerTriangleList(_tailleTerrain, _tailleTerrain, this);
// }
//
//
// void Terrain::LoadhauteurCarteFile(const char* pFilename)
// {
//     int FileSize = 0;
//     unsigned char* p = (unsigned char*)ReadBinaryFile(pFilename, FileSize);
//
//     if (FileSize % sizeof(float) != 0) {
//         printf("%s:%d - '%s' does not contain an whole number of floats (size %d)\n", __FILE__, __LINE__, pFilename, FileSize);
//         exit(0);
//     }
//
//     _tailleTerrain = (int)sqrtf((float)FileSize / (float)sizeof(float));
//
//     printf("Terrain size %d\n", _tailleTerrain);
//
//     if ((_tailleTerrain * _tailleTerrain) != (FileSize / sizeof(float))) {
//         printf("%s:%d - '%s' does not contain a square height map - size %d\n", __FILE__, __LINE__, pFilename, FileSize);
//         exit(0);
//     }
//
//     _carteHauteur.initTableau2D(_tailleTerrain, _tailleTerrain, (float*)p);
// }


void Terrain::saveDansFic(const char* pFilename) {
    unsigned char* p = (unsigned char*)malloc(_tailleTerrain * _tailleTerrain);
    float* src = _carteHauteur.getBaseAddr();
    float delta = _hauteurMax - _hauteurMin;

    for (int i = 0; i < _tailleTerrain * _tailleTerrain; i++) {
        float f = (src[i] - _hauteurMin) / delta;
        p[i] = (unsigned char)(f * 255.0f);
    }

    std::ofstream file;
    file.open(pFilename);

    for (int i = 0; i < _tailleTerrain; ++i) {
        for (int j = 0; j < _tailleTerrain; ++j) {
            file << _carteHauteur.at(i,j) << " ";
        }
        file << "\n";
    }

    file.close();
    free(p);
}


void Terrain::render(const Camera& camera) {
    Matrice4f VP = camera.getVueProjMat();
    _terrainTech.activeShaderProgram();
    _terrainTech.setVP(VP);

    for (size_t i = 0; i < nbreElmDansTab(_pTextures); i++) {
        if (_pTextures[i]) {
            _pTextures[i]->attacher(COULEUR_TEXTURE_UNIT_0 + i);
        }
    }

    _terrainTech.setLumiereDir(_lumiereDir);
    _triangleList.render();
}


void Terrain::setHauteurMinMax(float hauteurMin, float hauteurMax) {
    _hauteurMin = hauteurMin;
    _hauteurMax = hauteurMax;
    _terrainTech.activeShaderProgram();
    _terrainTech.setHauteurMinMax(hauteurMin, hauteurMax);
}


void Terrain::setTextureHauteur(float hauteurTex0, float hauteurTex1, float hauteurTex2, float hauteurTex3) {
    _terrainTech.setTextureHauteur(hauteurTex0, hauteurTex1, hauteurTex2, hauteurTex3);
}

void Terrain::creerCarteDiamantCarre(int tailleTerrain, float chaos, float hauteurMin, float hauteurMax) {
    if (chaos < 0.0f) {
        printf("%s: chaos > 0 ! - %f\n", __FUNCTION__, chaos);
        exit(0);
    }

    _tailleTerrain = tailleTerrain;
    setHauteurMinMax(hauteurMin, hauteurMax);
    std::cout << "Terrain size : " << tailleTerrain << std::endl;
    _carteHauteur.initTableau2D(tailleTerrain, tailleTerrain, 0.0f);

    int tailRect = _tailleTerrain;
    float hauteurCourant = (float)tailRect / 2.0f;
    float HeightReduce = pow(2.0f, -chaos);

    while (tailRect > 0) {

        diamant(tailRect, hauteurCourant);

        carre(tailRect, hauteurCourant);

        tailRect /= 2;
        hauteurCourant *= HeightReduce;
    }

    _carteHauteur.normaliser(hauteurMin, hauteurMax);

    _triangleList.creerTriangleList(_tailleTerrain, _tailleTerrain, this);
    // _carteHauteur.print();
}

void Terrain::diamant(int tailRect, float hauteurCourant) {
    int tailDemiRect = tailRect / 2;

    // x,y represente le coin superieur gauche de chaque sous-rectangle
    // xSuiv, ySuiv represente le coin inferieur droite de chaque sous-rectangle
    for (int y = 0 ; y < _tailleTerrain ; y += tailRect) {
        for (int x = 0 ; x < _tailleTerrain ; x += tailRect) {
            int xSuiv = (x + tailRect) % _tailleTerrain;
            int ySuiv = (y + tailRect) % _tailleTerrain;

            if (xSuiv < x) {
                xSuiv = _tailleTerrain - 1;
            }

            if (ySuiv < y) {
                ySuiv = _tailleTerrain - 1;
            }

            // Les 4 coins du sous-rectangle
            float hautGauche     = _carteHauteur.get(x, y);
            float hautDroite    = _carteHauteur.get(xSuiv, y);
            float basGauche  = _carteHauteur.get(x, ySuiv);
            float basDroite = _carteHauteur.get(xSuiv, ySuiv);
            int xMedian = (x + tailDemiRect) % _tailleTerrain;
            int yMedian = (y + tailDemiRect) % _tailleTerrain;
            float valAlea = plageFloattantAleatoire(hauteurCourant, -hauteurCourant);
            float MidPoint = (hautGauche + hautDroite + basGauche + basDroite) / 4.0f;

            _carteHauteur.set(xMedian, yMedian, MidPoint + valAlea);
        }
    }
}


void Terrain::carre(int tailRect, float hauteurCourant) {
    int tailDemiRect = tailRect / 2;

    for (int y = 0 ; y < _tailleTerrain ; y += tailRect) {
        for (int x = 0 ; x < _tailleTerrain ; x += tailRect) {
            int xSuiv = (x + tailRect) % _tailleTerrain;
            int ySuiv = (y + tailRect) % _tailleTerrain;

            if (xSuiv < x) {
                xSuiv = _tailleTerrain - 1;
            }

            if (ySuiv < y) {
                ySuiv = _tailleTerrain - 1;
            }

            int xMedian = (x + tailDemiRect) % _tailleTerrain;
            int yMedian = (y + tailDemiRect) % _tailleTerrain;
            int xMedianPrec = (x - tailDemiRect + _tailleTerrain) % _tailleTerrain;
            int yMedianPrec = (y - tailDemiRect + _tailleTerrain) % _tailleTerrain;
            float hautGaucheCourant  = _carteHauteur.get(x, y);
            float hautDroiteCourant = _carteHauteur.get(xSuiv, y);
            float centreCourant   = _carteHauteur.get(xMedian, yMedian);
            float centreYprec = _carteHauteur.get(xMedian, yMedianPrec);
            float basGaucheCourant  = _carteHauteur.get(x, ySuiv);
            float centreXprec = _carteHauteur.get(xMedianPrec, yMedian);
            float gaucheMedian = (hautGaucheCourant + centreCourant + basGaucheCourant + centreXprec) / 4.0f + plageFloattantAleatoire(-hauteurCourant, hauteurCourant);
            float hautMedian  = (hautGaucheCourant + centreCourant + hautDroiteCourant + centreYprec) / 4.0f + plageFloattantAleatoire(-hauteurCourant, hauteurCourant);

            _carteHauteur.set(xMedian, y, hautMedian);
            _carteHauteur.set(x, yMedian, gaucheMedian);
        }
    }
}

