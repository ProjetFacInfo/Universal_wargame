#include "Jeu.hh"

Jeu::Jeu():_carte(){}

Jeu::Jeu(std::array<Terrain, TAILLECARTE> const & liste_terrains):_carte(std::make_shared<Carte>(liste_terrains)){}

void Jeu::afficherCarte(std::ostream & flux) const
{
    _carte->afficher(flux);
}
