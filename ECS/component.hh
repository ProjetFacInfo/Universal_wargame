#pragma once
#include "../type.hh"
#include "../math/vec3.hh"

////////////////
// Components //
////////////////

struct Transform { // a une position sur la map
    Vec3 position;
};

struct Motion { // vélocité, accélération
    vec3 velocity, accelaration;
};

struct Sprite { // pour le rendu sur l'écran

};

struct Collision { // collision avec d'autre entité

};

struct Health { // a une vie (peut se faire "attaquer")
    int current_health, max_health;
}

struct Follow { // suivre

};

struct Joystick { // action selon les touches

};

