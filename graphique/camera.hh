#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "math3D.hh"


class Camera {
private:
    Vecteur3f _pos;
    Vecteur3f _cible;
    Vecteur3f _up;
    float _vitesse;
    int _windowLargeur;
    int _windowHauteur;
    float _angleH;                  // angle vue horizontal
    float _angleV;                  // angle vue vertical
    // Les 4 bords de l'écran pour verifié si on l'attend
    bool _bordSup;
    bool _bordInf;
    bool _bordGauche;
    bool _bordDroite;
    Position _mousePos;
    PersProjInfo _persProfInfo;
    Matrice4f _projection;

public:

    Camera();
    Camera(int Windowlargeur, int WindowHauteur);
    Camera(const PersProjInfo& persProjInfo, const Vecteur3f& pos, const Vecteur3f& cible, const Vecteur3f& Up);
    Camera(const OrthoProjInfo& orthoProjInfo, const Vecteur3f& pos, const Vecteur3f& cible, const Vecteur3f& Up);
    void initCamera
    (const PersProjInfo& persProjInfo, const Vecteur3f& pos, const Vecteur3f& cible, const Vecteur3f& Up);
    void initCamera
    (const OrthoProjInfo& orthoProjInfo, const Vecteur3f& pos, const Vecteur3f& cible, const Vecteur3f& Up);
    void initInterne();
    void update();

    const Vecteur3f& getPos() const;
    const Vecteur3f& getCible() const;
    const Vecteur3f& getUp() const;
    const PersProjInfo& getPersProjInfo() const;
    Matrice4f getMatrice() const;
    Matrice4f getVueMat() const;
    const Matrice4f& getProjectionMat() const;
    Matrice4f getVueProjMat() const;
    // transformer les coordonnées de clip en coordonnées de fenêtre
    // pour la fenetre de visualisation
    Matrice4f getViewportMat() const;
    void setPosition(float x, float y, float z);
    void setPosition(const Vecteur3f& pos);
    void setCible(float x, float y, float z);
    void setCible(const Vecteur3f& cible);
    void setUp(float x, float y, float z);
    void setVitesse(float vit);
    bool OnKeyboard(int key);
    void OnMouse(int x, int y);
    void OnRender();
    // Pour debugger
    void print() const;

};
