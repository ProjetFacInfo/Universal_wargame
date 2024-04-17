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

Ressources Troupe::cout(uint8 ere) const {
    return dataTroupes.at(_typeTroupe).cout * MULT_ERE[ere];
}

void Troupe::evolue(uint8 ere)
{
}

uint32 Troupe::attaque() const {
    return dataTroupes.at(_typeTroupe).attaque;
}

uint32 Troupe::portee_min() const {
    return dataTroupes.at(_typeTroupe).portee.min;
}

uint32 Troupe::portee_max() const {
    return dataTroupes.at(_typeTroupe).portee.max;
}

uint32 Troupe::defense() const {
    return dataTroupes.at(_typeTroupe).defense;
}

uint32 Troupe::pas() const {
    return dataTroupes.at(_typeTroupe).pas;
}

uint32 Troupe::accesTerrain(Terrain const & t) const {
    return dataTroupes.at(_typeTroupe).accesTerrain.at(t);
}
