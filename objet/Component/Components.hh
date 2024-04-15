#pragma once
#include "../type.hh"
#include <map>

std::map<std::string, signature> component_to_signature_map = {
    {"Attaque_component", 1},   // 0000'0001
    {"Defense_component", 2},   // 0000'0010
    {"Mov_component", 4},       // 0000'0100
    {"Terrain_component", 8},   // 0000'1000
    {"Collision_component", 16} // 0001'0000
};

std::map<signature, std::string> signature_to_component_map = {
    {1,"Attaque_component"},
    {2, "Defense_component"},
    {4, "Mov_component"},
    {8, "Terrain_component"},
    {16, "Collision_component"}
};


struct IComponent {
    virtual ~IComponent = default;
}

// A une attaquer + une porté d'attaque
struct Attaque_component : public IComponent {
    int damage;
    int damage_range;
}

// A une defense
struct Defense_component : public IComponent {
    int defense;
}

// A un nombre de pas
struct Mov_component : public IComponent {
    int step;
}

// A un type de terrain accessible (avec malus)
struct Terrai_component : public IComponent {
    signature sig;
}

// A un perimetre de collision
struct Collision_component : public IComponent {
    int radus;
}

// A un parametre de controle
struct Control_component : public ICompoenent {

}

// A une arme (court porté, long porté, artillerie)
struct Weapon_component {
   constexpr uint16 range_min;
   constexpr uint16 range_max;
   Weapon_component(uint16 min, uint16 max)
       :range_min(min), range_max(max) {}
};

struct Melee_weapon {
   Melee_weapon(): Weapon_component(1, 1) {}
};

struct Ranged_weapon {
   Melee_weapon(): Weapon_component(1, 3) {}
};

struct Artillery_weapon {
   Artillery_weapon(): Weapon_component(2, 6) {}
};

// A un type de comportement d'unité
// infanterie, cavalerie, etc..
struct Arms_component {
    constexpr signature terrain;
    constexpr uint16 step;
    Arms_component(signature const & t, uint16 s)
        :terrain(t), step(s) {}
};

struct Infantry {
    // Terrain acces 0000'...'0000'0011'1111'0101
    signature terrain_behaviour() {
        return 1013;
    }

    uint16 step_behaviour() {
        return 2;
    }
};

struct Rider  {

}
