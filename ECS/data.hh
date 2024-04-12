#pragma once
#include "../type.hh"
#include "../math/vec3.hh"

////////////////
// Components //
////////////////

std::map<std::string, signature> ECS_mask {
    {"Health", 1},    // 0000'0001
    {"Attack", 2},    // 0000'0010
    {"Defense", 4}    // 0000'0100
};

struct Health { // a une vie (peut se faire "attaquer")
    int current_health;
    int max_health;
};

struct Attack { // a un moyen d'attaquer + une porté d'attaque
    int damage;
    int damaga_range;
};

struct Defense { // a un moyen de se défendre
    int shild;
};

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


struct Follow { // suivre
    Vec3 target;
};

struct Joystick { // action selon les touches

};


