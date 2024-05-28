#include "Jeu.hh"

Jeu::Jeu(std::array<Terrain, TAILLECARTE> const & liste_terrains):_carte(std::make_shared<Carte>(liste_terrains)),_j1(_carte, TypeJoueur::joueur1), _j2(_carte, TypeJoueur::joueur2){}

void Jeu::lancer()
{
    unsigned int i = 0;
    while(i<21 && i++){
        _j1.joue();
        afficherCarte(std::cout);
        _j2.joue();
        afficherCarte(std::cout);
    }
}

void Jeu::afficherCarte(std::ostream & flux) const
{
    _carte->afficher(flux);
}
