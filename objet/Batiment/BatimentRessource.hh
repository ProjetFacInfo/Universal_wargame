#pragma once

#include "../Batiment.hh"

class BatimentRessource: public Batiment{
private:
    TypeRessource _ressource;
public:
    BatimentRessource(TypeRessource const & r, uint32 pos, TypeJoueur const & joueur);
    std::string const & nom() const override;
	  Ressources cout() const override;
    TypeRessource const & ressourceProduite() const;
    uint32 quantiteProduite() const;
};
