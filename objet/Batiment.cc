#include "Batiment.hh"

Batiment::Batiment(uint32 vie, uint32 pos, TypeJoueur const &joueur)
    :Element(vie, pos, joueur){}

TypeElement Batiment::type() const
{
    return TypeElement::batiment;
}

uint32 Batiment::defense() const {
    return 0;
}
