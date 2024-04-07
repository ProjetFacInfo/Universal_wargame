#include "Troupe.hh"

Troupe::Troupe(std::string const &nom, uint32 vie, uint32 pos, uint8 ere, Ressource const &cout)
    :Element(nom,vie,pos,ere,cout){}

TypeElement const &Troupe::type() const
{
    return TypeElement::troupe;
}
