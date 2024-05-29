#pragma once

#include "math3D.hh"
#include "materiau.hh"
#include "technique.hh"
#include "materiau.hh"
#include "monde_transformation.hh"


struct LumiereBase {
    Vecteur3f couleur;
    float intensiteAmbiante;
    float intensiteDiffuse;

    LumiereBase();
    bool estZero();
};


struct LumiereDirectionnel : public LumiereBase {
    Vecteur3f directionLocal;
    Vecteur3f directionMonde;

    LumiereDirectionnel();
    const Vecteur3f& getDirectionLocal() const;
    void calcDirectionLocal(const MondeTrans& mondeTransform);
};

struct Attenuation {
    float constant;
    float linear;
    float exponentiel;
    Attenuation();
};


struct LumierePonctuel: public LumiereBase {
    Vecteur3f posLocal;
    Vecteur3f posMonde;
    Attenuation atten;

    LumierePonctuel();
    void calcPosLocal(const MondeTrans& mondeTransform);
    const Vecteur3f& getPosLocal() const;

};


struct LumiereProjecteur : public LumierePonctuel {
    Vecteur3f directionLocal;
    Vecteur3f directionMonde;
    float limite;

    LumiereProjecteur();
    void calcDirEtPosLocal(const MondeTrans& mondeTransform);
    const Vecteur3f& getDirectionLocal() const;
};


struct LumierePBR {
    Vecteur4f posDir;   // w = 1 -> position, w = 0 -> direction
    Vecteur3f intesite;
};


class LumiereTechnique : public Technique {
public:
    static const unsigned int MAX_LUMIERE_PONCTUEL = 2;
    static const unsigned int MAX_LUMIERE_PROJECTEUR = 2;

private:

    GLuint MVPLoc;
    GLuint matMondeLoc;
    GLuint matVueLoc;
    GLuint lumiereMVPLoc;
    GLuint samplerLoc;
    GLuint ombreCarteLoc;
    GLuint ombreCubeCarteLoc;
    GLuint ombreCarteLargeurLoc;
    GLuint ombreCarteHauteurLoc;
    GLuint ombreCartetaiFiltreLoc;
    GLuint ombreCarteDecalageTextureLoc;
    GLuint ombreCarteDecalageTaiTextureLoc;
    GLuint ombreCarteDecalageTaiFiltreLoc;
    GLuint ombreCarteRandomLoc;
    GLuint samplerExposantSpeculaire;
    GLuint cameraLocalPosLoc;
    GLuint cameraMondePosLoc;
    GLuint nbreLumierePonctuelLoc;
    GLuint nbreLumiereProjecteursLoc;
    GLuint lumiereContourActive;           // Rim light
    GLuint exposantSpeculaireActive;
    GLuint estPBRLoc;
    GLuint clipPlanLoc;

    struct {
        GLuint couleurAmbiante;
        GLuint couleurDiffuse;
        GLuint couleurSpeculaire;
    } materiauLoc;

    struct {
        GLuint couleur;
        GLuint intensiteAmbiante;
        GLuint direction;
        GLuint intensiteDiffuse;
    } LumiereDirLoc;

    struct {
        GLuint couleur;
        GLuint intensiteAmbiante;
        GLuint localPos;
        GLuint mondePos;
        GLuint intensiteDiffuse;

        struct
        {
            GLuint constant;
            GLuint linear;
            GLuint exponentiel;
        } atten;
    } LumierePonctuelLoc[MAX_LUMIERE_PONCTUEL];

    struct {
        GLuint couleur;
        GLuint intensiteAmbiante;
        GLuint intensiteDiffuse;
        GLuint Position;
        GLuint direction;
        GLuint limite;
        struct {
            GLuint constant;
            GLuint linear;
            GLuint exponentiel;
        } atten;
    } LumiereProjecteurLoc[MAX_LUMIERE_PROJECTEUR];

    struct {
        GLuint rugosite;
        GLuint estMetalique;
        GLuint couleur;
    } PBRMateriauLoc;

public:
    LumiereTechnique();

    bool init();
    bool initInterne();
    void setMVP(const Matrice4f& MVP);
    void setMatMonde(const Matrice4f& monde);
    void setMatVue(const Matrice4f& matVue);
    void setLumiereMVP(const Matrice4f& lumiereMVP);
    void setTextureUnit(uint textureUnit);
    void setOmbreTextureUnitCarte(uint textureUnit);
    void setOmbreCubeTextureUnitCarte(uint textureUnit);
    void setOmbreTailCarte(uint largeur, uint hauteur);
    void setOmbreTailFiltreCarte(uint size);
    void setOmbreDecalageTextureUnitCarte(uint textureUnit);
    void setOmbreDecalageTextureParamCarte(float taiTexture, float taiFiltre, float rayon);
    void setSpecularExponentTextureUnit(uint textureUnit);
    void setLumiereDirectionnel(const LumiereDirectionnel& dirLumiere, bool avecDirection = true);
    void setLumierePonctuels(uint nbreLumiere, const LumierePonctuel* pLumieres, bool avecPos = true);
    void setLumiereProjecteurs(uint nbreLumiere, const LumiereProjecteur* pLumieres, bool avecPosEtDir = true);
    void updateDirLumiereDirection(const LumiereDirectionnel& dirLumiere);
    void updateLumierePonctuelPos(uint nbreLumiere, const LumierePonctuel* pLumieres);
    void updateLumiereProjecteurPosDir(uint nbreLumiere, const LumiereProjecteur* pLumieres);
    void setCameraLocalPos(const Vecteur3f& cameraLocalPos);
    void setCameraMondePos(const Vecteur3f& cameraMondePos);
    void setMateriau(const Materiau& materiau);
    void controlLumiereContour(bool estActive);
    void controlExposantSpeculaire(bool estActive);
    void setPBR(bool estPBR);
    void setPBRmateriau(const PBRMateriau& materiau);
    void setClipPlan(const Vecteur3f& normal, const Vecteur3f& pointDansLePlan);

};
