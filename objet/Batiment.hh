#pragma once

#include "Element.hh"

class Batiment: public Element{
public:
    Batiment(uint32 vie, uint32 pos, TypeJoueur const & joueur);
    TypeElement type() const override;
};