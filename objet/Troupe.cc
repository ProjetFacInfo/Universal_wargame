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

Ressources const & Troupe::cout() const {
    Ressources cout = dataTroupes.at(_typeTroupe).cout;
    return cout * MULT_ERE[ere()];
}
