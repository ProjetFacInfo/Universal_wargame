#pragma once

#include "Element.hh"

class Batiment: public Element{
private:

public:
    Batiment(std::string const & nom, uint32 vie, uint32 pos, Ressource const & cout, TypeJoueur const & joueur);
    TypeElement type() const override;
};