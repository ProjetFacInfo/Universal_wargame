#include "BatimentRessource.hh"

BatimentRessource::BatimentRessource(TypeRessource const &r, uint8_t pos, TypeJoueur const & joueur)
    :Batiment(  dataBatimentRessources.at(r).nom, 
                dataBatimentRessources.at(r).vie[(joueur == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2],
                pos, 
                dataBatimentRessources.at(r).cout[(joueur == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2], 
                joueur)
{}
