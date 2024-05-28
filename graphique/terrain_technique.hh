#pragma once
#include "technique.hh"
#include "math3D.hh"

class TerrainTechnique : public Technique {
private:
    GLuint _VPLoc;
    GLuint _hauteutMinLoc;
    GLuint _hauteurMaxLoc;
    GLuint _hauteurTex0Loc;
    GLuint _hauteurTex1Loc;
    GLuint _hauteurTex2Loc;
    GLuint _hauteurTex3Loc;
    GLuint _texUnit0Loc;
    GLuint _texUnit1Loc;
    GLuint _texUnit2Loc;
    GLuint _texUnit3Loc;
    GLuint _lumireDirInverseLoc;

public:

    TerrainTechnique();
    // TODO : supprimer virtual
    virtual bool init();
    void setVP(const Matrice4f & VP);
    void setHauteurMinMax(float min, float max);
    void setTextureHauteur(float hauteurTex0, float hauteurTex1, float hauteurTex2, float hauteurTex3);
    void setLumiereDir(const Vecteur3f& dir);
};


