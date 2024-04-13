#include "Troupe.hh"

Troupe::Troupe(std::string const &nom, uint32 vie, uint32 pos, Ressource const &cout, TypeJoueur const & joueur)
    :Element(nom,vie,pos,cout, joueur){}

TypeElement Troupe::type() const
{
    return TypeElement::troupe;
}
