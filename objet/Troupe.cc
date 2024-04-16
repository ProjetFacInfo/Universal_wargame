#include "Troupe.hh"

Troupe::Troupe(uint32 vie, uint32 pos, TypeJoueur const & joueur, TypeTroupe const & t)
    :Element(vie,pos, joueur), _typeTroupe(t){}

TypeElement Troupe::type() const
{
    return TypeElement::troupe;
}

std::string const & Troupe::nom() const {
    return dataTroupes.at(_typeTroupe).nom;
}

Ressources Troupe::cout() const {
    return dataTroupes.at(_typeTroupe).cout * MULT_ERE[ere()];
}
