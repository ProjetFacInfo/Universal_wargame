#include "camera.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static int MARGE = 40;
static float PAS_DE_BORD = 0.5f;

Camera::Camera()
    : _vitesse(10.0f) {}

Camera::Camera(int Windowlargeur, int WindowHauteur)
    : _pos(Vecteur3f(0.0f, 0.0f, 0.0f)), _cible(Vecteur3f(0.0f, 0.0f, 1.0f)) , _up(Vecteur3f(0.0f, 1.0f, 0.0f))
      , _windowLargeur(Windowlargeur), _windowHauteur(WindowHauteur){
    initInterne();
}


Camera::Camera
(const PersProjInfo& persProjInfo, const Vecteur3f& pos, const Vecteur3f& cible, const Vecteur3f& Up)
    : _persProfInfo(persProjInfo), _pos(pos), _cible(cible), _up(Up),
    _windowLargeur((int)persProjInfo.largeur), _windowHauteur((int)persProjInfo.hauteur) {
    _projection.persProjTransform(persProjInfo);
    _cible.normaliser();
    _up.normaliser();
    initInterne();
}


Camera::Camera
(const OrthoProjInfo& orthoProjInfo, const Vecteur3f& pos, const Vecteur3f& cible, const Vecteur3f& Up)
    : _pos(pos), _cible(cible), _up(Up),
    _windowLargeur((int)orthoProjInfo.largeur), _windowHauteur((int)orthoProjInfo.hauteur) {
    _projection.orthoProjTransform(orthoProjInfo);
    _cible.normaliser();
    _up.normaliser();
    initInterne();
}

void Camera::initInterne() {
    // atan2 calcul l'angle horizontal avec l'axe x et la position(z,x) de la cible
    _angleH = -radianEnDegree(atan2(_cible.z, _cible.x));

    // asin calcul l'angle vertical avec le y de la cible
    _angleV = -radianEnDegree(asin(_cible.y));

    _bordSup = false;
    _bordInf = false;
    _bordGauche  = false;
    _bordDroite = false;
    _mousePos.x  = _windowLargeur / 2;
    _mousePos.y  = _windowHauteur / 2;
}


const Vecteur3f& Camera::getPos() const {
    return _pos;
}

const Vecteur3f& Camera::getCible() const {
    return _cible;
}

const Vecteur3f& Camera::getUp() const {
    return _up;
}

const Matrice4f& Camera::getProjectionMat() const {
    return _projection;
}

const PersProjInfo& Camera::getPersProjInfo() const {
    return _persProfInfo;
}

Matrice4f Camera::getVueMat() const {
    return getMatrice();
}

Matrice4f Camera::getMatrice() const {
    Matrice4f cameraTrans;
    cameraTrans.cameraTransform(_pos, _cible, _up);
    return cameraTrans;
}

Matrice4f Camera::getVueProjMat() const {
    Matrice4f vue = getMatrice();
    Matrice4f proj = getProjectionMat();
    Matrice4f vueProj = proj * vue;
    return vueProj;
}

Matrice4f Camera::getViewportMat() const {
    float demiLargeur = _windowLargeur / 2.0f;
    float demiHauteur = _windowHauteur / 2.0f;
    Matrice4f viewport = Matrice4f(demiLargeur, 0.0f , 0.0f, demiLargeur,
                                 0.0f , demiHauteur, 0.0f, demiHauteur,
                                 0.0f , 0.0f , 1.0f, 0.0f,
                                 0.0f , 0.0f , 0.0f, 1.0f);

    return viewport;
}

void Camera::setPosition(float x, float y, float z) {
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
}


void Camera::setPosition(const Vecteur3f& pos) {
    setPosition(pos.x, pos.y, pos.z);
}

void Camera::setCible(float x, float y, float z) {
    _cible.x = x;
    _cible.y = y;
    _cible.z = z;
}

void Camera::setCible(const Vecteur3f& cible) {
    setCible(cible.x, cible.y, cible.z);
}

void Camera::setUp(float x, float y, float z) {
    _up.x = x;
    _up.y = y;
    _up.z = z;
}

void Camera::setVitesse(float vit) {
    if (vit <= 0.0f) {
        printf("vitesse camera doit etre positive %f\n", vit);
        exit(0);
    }

    _vitesse = vit;
}

bool Camera::OnKeyboard(int Key) {
    bool posChanger = false;

    switch (Key) {

        case GLFW_KEY_W:
            _pos += (_cible * _vitesse);
            posChanger = true;
            break;

        case GLFW_KEY_S: {
            _pos -= (_cible * _vitesse);
            posChanger = true;
            }
            break;

        case GLFW_KEY_A: {
            Vecteur3f gauche = _cible.produitVectoriel(_up);
            gauche.normaliser();
            gauche *= _vitesse;
            _pos += gauche;
            posChanger = true;
        }
            break;

        case GLFW_KEY_D: {
            Vecteur3f droite = _up.produitVectoriel(_cible);
            droite.normaliser();
            droite *= _vitesse;
            _pos += droite;
            posChanger = true;
        }
            break;

        case GLFW_KEY_UP:
            _angleV += _vitesse;
            update();
            break;

        case GLFW_KEY_DOWN:
            _angleV -= _vitesse;
            update();
            break;

        case GLFW_KEY_LEFT:
            _angleH -= _vitesse;
            update();
            break;

        case GLFW_KEY_RIGHT:
            _angleH += _vitesse;
            update();
            break;

        case GLFW_KEY_PAGE_UP:
            _pos.y += _vitesse;
            posChanger = true;
            break;

        case GLFW_KEY_PAGE_DOWN:
            _pos.y -= _vitesse;
            posChanger = true;
            break;


        case GLFW_KEY_KP_ADD:
            _vitesse += 0.1f;
            printf("vitesse change  %f\n", _vitesse);
            break;

        case GLFW_KEY_KP_SUBTRACT:
            _vitesse -= 0.1f;
            if (_vitesse < 0.1f) {
                _vitesse = 0.1f;
            }
            printf("vitesse change %f\n", _vitesse);
            break;

        case GLFW_KEY_C: {
            printf("Camera "); print(); printf("\n");
            break;
        }
    }


    return posChanger;
}


void Camera::OnMouse(int x, int y) {
    int deltaX = x - _mousePos.x;
    int deltaY = y - _mousePos.y;

    _mousePos.x = x;
    _mousePos.y = y;

    _angleH += (float)deltaX / 20.0f;
    _angleV += (float)deltaY / 20.0f;

    if (x <= MARGE) {
        _bordGauche = true;
	      _bordDroite = false;
    }  else if (x >= (_windowLargeur - MARGE)) {
        _bordDroite = true;
	      _bordGauche = false;
    } else {
        _bordGauche = false;
        _bordDroite = false;
    }

    if (y <= MARGE) {
        _bordSup = true;
        _bordInf = false;
    } else if (y >= (_windowHauteur - MARGE)) {
        _bordInf = true;
        _bordSup = false;
    } else {
        _bordSup = false;
        _bordInf = false;
    }

    update();
    // std::cout << "Camera::OnMouse" << std::endl;
}


void Camera::OnRender() {
    bool aAtteindBord = false;

    if (_bordGauche) {
        _angleH -= PAS_DE_BORD;
        aAtteindBord = true;
    }
    else if (_bordDroite) {
        _angleH += PAS_DE_BORD;
        aAtteindBord = true;
    }

    if (_bordSup) {
        if (_angleV > -90.0f) {
            _angleV -= PAS_DE_BORD;
            aAtteindBord = true;
        }
    }
    else if (_bordInf) {
        if (_angleV < 90.0f) {
           _angleV += PAS_DE_BORD;
           aAtteindBord = true;
        }
    }

    if (aAtteindBord) {
        update();
    }
}


void Camera::update() {
    Vecteur3f axeY(0.0f, 1.0f, 0.0f);

    // Tourne le vecteur vue par l'angle horizontal autour de l'axe vertical
    Vecteur3f vue(1.0f, 0.0f, 0.0f);
    vue.rotation(_angleH, axeY);
    vue.normaliser();

    // Tourne le vecteur vue par l'angle vertical autour de l'axe horizontal
    Vecteur3f U = axeY.produitVectoriel(vue);
    U.normaliser();
    vue.rotation(_angleV, U);
    _cible = vue;
    _cible.normaliser();
    _up = _cible.produitVectoriel(U);
    _up.normaliser();
}

void Camera::print() const {
    printf("pos "); _pos.print();
    printf("cible "); _cible.print();
}
