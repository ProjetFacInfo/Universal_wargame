#pragma once

#include "../Batiment.hh"

class BatimentRessource: public Batiment{
public:
    BatimentRessource(TypeRessource const & r, uint32_t pos, TypeJoueur const & joueur);
    std::string const & nom() const override;
	Ressource const & cout() const override;
};