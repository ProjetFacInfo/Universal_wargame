#include "Carte.hh"

Carte::Carte():_largeur(LARGEURCARTE),_longueur(LONGUEURCARTE),_plateau(_largeur*_longueur){}

uint16_t Carte::largeur() const
{
    return _largeur;
}

uint16_t Carte::longueur() const
{
    return _longueur;
}

uint16_t Carte::taille() const
{
    return _plateau.size();
}

Case const &Carte::getCase(uint16_t i, uint16_t j) const
{
    return _plateau[i*_largeur+j];
}
