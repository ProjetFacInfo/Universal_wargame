#pragma once
#include "../type.hh"
#include "../math/vec3.hh"

////////////////
// Components //
////////////////

struct Transform { // a une position sur la map
    Vec3 position;
    Vec3 rotation;
};

struct Motion { // vélocité, accélération
    Vec3 velocity;
    Vec3 accelaration;
};

struct Sprite { // pour le rendu sur l'écran

};

struct Collision { // collision avec d'autre entité

};

struct Health { // a une vie (peut se faire "attaquer")
    int current_health, max_health;
}

struct Follow { // suivre
    Vec3 target;
};

struct Joystick { // action selon les touches

};

