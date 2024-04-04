#pragma once
#include <iostream>
#include <string>
#include <array>

#include "Carte.hh"
#include "Joueur.hh"

class Jeu {
private:
    Carte _carte;
    Joueur _j1;
    Joueur _j2;
public:
    Jeu();
    Jeu(std::array<Terrain, TAILLECARTE> const & liste_terrains);
    void afficherCarte(std::ostream & flux) const;
};