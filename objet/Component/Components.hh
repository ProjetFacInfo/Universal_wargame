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

