#pragma once
#include "technique.hh"
#include "math3D.hh"

class TerrainTechnique : public Technique
{
public:

    TerrainTechnique();

    virtual bool init();

    void setVP(const Matrice4f & VP);

    void setMinMaxHeight(float Min, float Max);

    void setTextureHeights(float Tex0Height, float Tex1Height, float Tex2Height, float Tex3Height);

    void setLightDir(const Vecteur3f& Dir);

private:
    GLuint m_VPLoc = -1;
    GLuint m_minHeightLoc = -1;
    GLuint m_maxHeightLoc = -1;
    GLuint m_tex0HeightLoc = -1;
    GLuint m_tex1HeightLoc = -1;
    GLuint m_tex2HeightLoc = -1;
    GLuint m_tex3HeightLoc = -1;
    GLuint m_tex0UnitLoc = -1;
    GLuint m_tex1UnitLoc = -1;
    GLuint m_tex2UnitLoc = -1;
    GLuint m_tex3UnitLoc = -1;
    GLuint m_reversedLightDirLoc = -1;
};

