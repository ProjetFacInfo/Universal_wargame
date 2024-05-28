#include "monde_transformation.hh"

MondeTrans::MondeTrans()
    :_scal(1.0f), _rot(Vecteur3f(0.0f,0.0f,0.0f)), _pos(Vecteur3f(0.0f, 0.0f, 0.0f)) {}

float MondeTrans::getScale() const {
    return _scal;
}

Vecteur3f MondeTrans::getPosition() const {
    return _pos;
}

Vecteur3f MondeTrans::getRotation() const {
    return _rot;
}

void MondeTrans::setScale(float scale) {
    _scal = scale;
}

void MondeTrans::setRotation(float x, float y, float z) {
    _rot.x = x;
    _rot.y = y;
    _rot.z = z;
}


void MondeTrans::setPosition(float x, float y, float z) {
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
}


void MondeTrans::setPosition(const Vecteur3f& pos) {
    _pos = pos;
}


void MondeTrans::rotation(float x, float y, float z) {
    _rot.x += x;
    _rot.y += y;
    _rot.z += z;
}


Matrice4f MondeTrans::getMatrice() const {
    Matrice4f scale;
    scale.scaleTransform(_scal);

    Matrice4f rotation;
    rotation.rotationTransform(_rot.x, _rot.y, _rot.z);

    Matrice4f translation;
    translation.translationTransform(_pos.x, _pos.y, _pos.z);

    return translation * rotation * scale;
}

Matrice4f MondeTrans::getMatriceTransInverse() const {
    Matrice4f translationInverse;
    translationInverse.translationTransform(_pos.opposer());
    return translationInverse;
}


Matrice4f MondeTrans::getMatriceRotInverse() const {
    Matrice4f rotationInverse;
    rotationInverse.rotationTransformZYX(- _rot.x, - _rot.y, - _rot.z);
    return rotationInverse;
}

Vecteur3f MondeTrans::posMondeEnPosLocal(const Vecteur3f & pos) const {
    Matrice4f translationInverse = getMatriceTransInverse();
    Matrice4f rotationInverse = getMatriceRotInverse();
    Matrice4f transMondeEnLocal = rotationInverse * translationInverse;
    Vecteur4f pos4f = Vecteur4f(pos, 1.0f);
    Vecteur4f LocalPos4f = transMondeEnLocal * pos4f;

    return Vecteur3f(LocalPos4f);
}


Vecteur3f MondeTrans::dirMondeEnDirLocal(const Vecteur3f & directionMonde) const {
    Matrice3f monde(getMatrice());
    Matrice3f mondeEnLocal = monde.transposer();
    Vecteur3f directionLocal = mondeEnLocal * directionMonde;

    return directionLocal.normaliser();
}
