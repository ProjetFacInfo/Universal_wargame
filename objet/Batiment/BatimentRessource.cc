#include "BatimentRessource.hh"

BatimentRessource::BatimentRessource(TypeRessource const & r, uint32_t pos, TypeJoueur const & joueur)
    :Batiment(dataBatimentRessources.at(r).vie[(joueur == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2], pos, joueur){}
