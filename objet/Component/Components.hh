#pragma once
#include "../type.hh"
#include <map>

// A une arme (court porté, long porté, artillerie)
//
// Arme de melée distance 1~1   : signature 001
// Arme à distance distance 1~3 : signature 010
// Artillerie distance 2~6      : signature 100

struct Range {
    uint16 min;
    uint16 max;
};

const std::map<weapon_signature, Range} infoWeapon{
    {1,{1,1}},
    {2,{1,3}},
    {4,{2,6}}
};

struct Weapon_component {
   constexpr uint16 range_min;
   constexpr uint16 range_max;
   Weapon_component(uint16 min, uint16 max)
       :range_min(min), range_max(max) {}
};

// A un type de comportement d'unité.
// Terrain accéssibilité (avec ou sans malus)
// Nombre de pas (Prendre le max en cas de type mixte)
//
// Infanterie :
// Terrain acces : 0000'0011'1111'0101
// Nombre de pas : 4
//
// Cavalier :
//
// Terrain acces : 0000'0001'1111'0101
// Nombre de pas : 6
//
//

struct Arms {
    signature terrain;
    uint16 step;
};

const std::map<arms_signature, Arms {
    {1, {1013, 4}},
    {2, {501, 6}}
};

struct Arms_component {
    constexpr signature terrain;
    constexpr uint16 step;
    Arms_component(signature const & t, uint16 s)
        :terrain(t), step(s) {}
};





// A un parametre de controle
struct Control_component : public ICompoenent {

}
