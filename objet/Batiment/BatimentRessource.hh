#pragma once

#include "../Batiment.hh"

class BatimentRessource: public Batiment{
private:
    TypeRessource _ressource;
public:
    BatimentRessource(TypeRessource const & r, uint32 pos, TypeJoueur const & joueur, uint8 ere);
    std::string const & nom() const override;
	Ressources cout(uint8 ere) const override;
    void evolue(uint8 ere) override;
    TypeRessource const & ressourceProduite() const;
    uint32 quantiteProduite(uint8 ere) const;
};
