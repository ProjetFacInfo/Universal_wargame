#pragma once
#include "technique.hh"
#include "math3D.hh"

class TextureTechnique : public Technique {
private:
    GLuint _MVPLoc;
    GLuint _samplerLoc;

public:
    TextureTechnique();
    virtual bool init();
    void setMVP(const Matrice4f & MVP);
    void setTextureUnit(uint textureUnit);
};
