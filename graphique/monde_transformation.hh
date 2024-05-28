#pragma once

#include "math3D.hh"

// Pour passer du systeme de coordonnées local aux systeme coordonnées monde
class MondeTrans {
 private:
    float    _scal;
    Vecteur3f _pos;
    Vecteur3f _rot;

 public:
    MondeTrans();

    float getScale() const;
    Vecteur3f getPosition() const;
    Vecteur3f getRotation() const;
    Matrice4f getMatrice() const;
    Matrice4f getMatriceTransInverse() const;
    Matrice4f getMatriceRotInverse() const;
    void setScale(float scale);
    void setRotation(float x, float y, float z);
    void setRotation(const Vecteur3f  & v);
    void setPosition(float x, float y, float z);
    void setPosition(const Vecteur3f  & pos);

    void rotation(float x, float y, float z);
    Vecteur3f posMondeEnPosLocal(const Vecteur3f & posMonde) const;
    Vecteur3f dirMondeEnDirLocal(const Vecteur3f & dirMonde) const;

};

