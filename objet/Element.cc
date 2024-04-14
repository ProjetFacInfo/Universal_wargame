#include "Element.hh"

uint8_t Element::ere_joueur1 = 0;
uint8_t Element::ere_joueur2 = 0;

Element::Element(uint32_t vie, uint32_t pos, TypeJoueur const & joueur)
    :_vie(vie),_pos(pos), _joueur(joueur){}

uint8_t Element::ere() const
{
    return (joueur() == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2;
}

void Element::passerEreSuivante(TypeJoueur const &joueur)
{
    switch (joueur)
    {
    case TypeJoueur::joueur1:
        ere_joueur1++;
        return;
    case TypeJoueur::joueur2:
        ere_joueur2++;
        return;
    }
}

void Element::retirerVie(uint32_t vieARetirer)
{
    if (vieARetirer > _vie) _vie = 0;
    else _vie-=vieARetirer;
}

bool Element::estDetruit() const
{
    return _vie == 0;
}
