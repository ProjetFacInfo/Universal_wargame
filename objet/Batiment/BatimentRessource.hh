#pragma once

#include "../Batiment.hh"

class BatimentRessource: public Batiment{
public:
    BatimentRessource(TypeRessource const & ressource, uint8_t pos, TypeJoueur const & joueur);
};