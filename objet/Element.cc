#include "Element.hh"

Element::Element(uint32 vie, uint32 pos, TypeJoueur const &joueur)
    : _vie(vie),  _joueur(joueur), _pos(pos) {}

void Element::setVie(uint32 vie)
{
    _vie = vie;
}

void Element::retirerVie(uint32 vieARetirer)
{
    if (vieARetirer > _vie) _vie = 0;
    else _vie-=vieARetirer;
}

bool Element::estDetruit() const
{
    return _vie == 0;
}
