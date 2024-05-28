#pragma once

#include "types.hh"
#include "util.hh"


#include <assimp/vector3.h>
#include <assimp/matrix3x3.h>
#include <assimp/matrix4x4.h>


struct Position {
    int x;
    int y;
};

// Perspective projection info
struct PersProjInfo {
    float CDV; 			// Champ De Vue
    float largeur;
    float hauteur;
    float zProche;
    float zLoin;
};


// orthographique projection info : 3D -> 2D
struct OrthoProjInfo {
    float gauche;
    float bas;
    float droite;
    float haut;
    float largeur;
    float hauteur;
    float zProche;
    float zLoin;
};

// Vecteur bidimentionnel de floatant
struct Vecteur2f {
    union {
        float x;
        float u;
    };

    union {
        float y;
        float v;
    };

    Vecteur2f() = default;
    Vecteur2f(float x, float y);

    float longueur() const;
    Vecteur2f & normaliser();
    Vecteur2f operator*(float f);
};


// Vecteur tridimentionnel de floatant
struct Vecteur4f;
struct Vecteur3f {
  union {
    float x;
    float r;
  };

  union {
    float y;
    float g;
  };

  union {
    float z;
    float b;
  };

	Vecteur3f() = default;
	Vecteur3f(float f);
	Vecteur3f(float x, float y, float z);
	Vecteur3f(const Vecteur3f & v);
  Vecteur3f(const Vecteur4f & v);

  float longueur() const;
  float distance(const Vecteur3f & v) const;
  Vecteur3f opposer() const;
  bool estZero() const;
  float produitScalaire(const Vecteur3f & v) const;
  Vecteur3f produitVectoriel(const Vecteur3f & v) const;
  Vecteur3f & normaliser();
  void rotation(float angle, const Vecteur3f & axe);
  void print() const;

  Vecteur3f & operator+=(const Vecteur3f & v);
  Vecteur3f & operator-=(const Vecteur3f & v);
  Vecteur3f & operator*=(float f);
  bool operator==(const Vecteur3f & v);
  bool operator!=(const Vecteur3f & v);

};

Vecteur3f operator+(const Vecteur3f & g, const Vecteur3f & d);
Vecteur3f operator-(const Vecteur3f & g, const Vecteur3f & d);
Vecteur3f operator*(const Vecteur3f & g, float f);
Vecteur3f operator/(const Vecteur3f & g, float f);


// Vecteur quadubledimentionnel de floatant
struct Vecteur4f {
  float x;
  float y;
  float z;
  float w;

  Vecteur4f() = default;

  Vecteur4f(float x, float y, float z, float w);
  Vecteur4f(const Vecteur4f & v);
  Vecteur4f(const Vecteur3f & v, float w);
  Vecteur3f vec4fEnVec3f() const;
  float longueur() const;
  Vecteur4f & normaliser();
  float produitScalaire(const Vecteur4f& v) const;

  Vecteur4f & operator+=(const Vecteur4f & v);
  Vecteur4f & operator-=(const Vecteur4f & v);
  Vecteur4f & operator*=(float f);
  bool operator==(const Vecteur4f& v);
  bool operator!=(const Vecteur4f & v);

};

Vecteur4f operator+(const Vecteur4f & g, const Vecteur4f & d);
Vecteur4f operator-(const Vecteur4f & g, const Vecteur4f & d);
Vecteur4f operator*(const Vecteur4f & g, float f);
Vecteur4f operator/(const Vecteur4f & g, float f);

// Quaternion (vecteur 4dimension avec 3 float complexe et 1 float réel)
// Quand w = 0,  x, y et z forme un sphere.
struct Quaternion {
  float x;
  float y;
  float z;
  float w;

  Quaternion() = default;
  Quaternion(float x, float y, float z, float w);
  Quaternion(const Quaternion & q);
  Quaternion(float Angle, const Vecteur3f& V);

  float longueur() const;
  Vecteur3f enDegree();
  Quaternion conjugue() const;
  Quaternion & normaliser();

};

Quaternion operator*(const Quaternion & g, const Quaternion & d);

Quaternion operator*(const Quaternion & q, const Vecteur3f & v);



// Matrice 3x3 de floatant
struct Matrice4f;
struct Matrice3f {
    float m[3][3];

    Matrice3f() = default;
    Matrice3f(float a00, float a01, float a02, float a10, float a11, float a12,
            float a20, float a21, float a22);
    Matrice3f(const Matrice3f & o);
    Matrice3f(const Matrice4f & o);

    void identite();
    Matrice3f transposer() const;

    Vecteur3f operator*(const Vecteur3f & v) const;
    Matrice3f operator*(const Matrice3f & o) const;

};

// Matrice 4x4 de floatant
struct Matrice4f {
    float m[4][4];

    Matrice4f();
    Matrice4f(float f);
    Matrice4f(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33);
    Matrice4f(const Matrice3f  & o);
    Matrice4f(const Matrice4f  & o);
    Matrice4f(const aiMatrix3x3  & am);
    Matrice4f(const aiMatrix4x4  & am);

    void identite();
    Matrice4f transposer() const;
    float determinant() const;
    Matrice4f inverse() const;
    void setZero();
    Matrice4f operator*(const Matrice4f  & o) const;
    Vecteur4f operator*(const Vecteur4f  & v) const;
    // convert matrice en float *
    operator const float*() const;


    void scaleTransform(float x, float y, float z);
    void scaleTransform(float s);

    // Rotation par angle d'Euleur
    void rotationTransform(float angle, float x, float y, float z);
    void rotationTransform(float x, float y, float z);
    void rotationTransformZYX(float x, float y, float z);
    void rotationTransform(const Vecteur3f  & rot);
    void rotationX(float x);
    void rotationY(float y);
    void rotationZ(float z);
    // Rotation par quaternion
    void rotationTransform(const Quaternion  & q);

    void translationTransform(float x, float y, float z);
    void translationTransform(const Vecteur3f  & pos);

    void cameraTransform(const Vecteur3f  & cible, const Vecteur3f  & up);
    void cameraTransform(const Vecteur3f  & pos, const Vecteur3f  & cible, const Vecteur3f  & up);

    void persProjTransform(const PersProjInfo  & p);

    void orthoProjTransform(const OrthoProjInfo  & o);
};


//
// Functions mathématique
//

float degreeEnRadian(float f);
float radianEnDegree(float f);
float floattantAleatoire();
float plageFloattantAleatoire(float deb, float fin);
float baryCentriqueCoord(const Vecteur3f & p1, const Vecteur3f & p2, const Vecteur3f & p3, const Vecteur2f & pos);

