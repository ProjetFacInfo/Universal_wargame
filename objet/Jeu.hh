#pragma once
#include <iostream>
#include <string>
#include <array>
#include <memory>

#include "Carte.hh"
#include "IA.hh"

class Jeu {
private:
    std::shared_ptr<Carte> _carte;
    IA _j1;
    IA _j2;
public:
    Jeu(std::array<Terrain, TAILLECARTE> const & liste_terrains);
    void afficherCarte(std::ostream & flux) const;
};