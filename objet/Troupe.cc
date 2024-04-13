#include "Troupe.hh"

Troupe::Troupe(std::string const &nom, uint32 vie, uint32 pos, Ressource const &cout)
    :Element(nom,vie,pos,cout){}

TypeElement Troupe::type() const
{
    return TypeElement::troupe;
}
