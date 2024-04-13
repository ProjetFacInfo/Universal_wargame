#pragma once

#include <queue>

#include "Carte.hh"
#include "Batiment/Base.hh"
#include "Batiment/BatimentRessource.hh"
#include "Troupe.hh"

class Joueur{
private:
    Ressources _ressources;
    std::queue<BatimentRessource> _batiments;
    std::shared_ptr<Element> _base;
public:
    Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur);
};