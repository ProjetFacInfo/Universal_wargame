#include "Element.hh"

uint8_t Element::ere_joueur1 = 1;
uint8_t Element::ere_joueur2 = 1;

Element::Element(std::string const &nom, uint32 vie, uint32 pos, Ressource const &cout, TypeJoueur const & joueur)
    :_nom(nom),_vie(vie),_pos(pos),_cout(cout), _joueur(joueur){}

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
