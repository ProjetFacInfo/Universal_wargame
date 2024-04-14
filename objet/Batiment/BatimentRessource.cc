#include "BatimentRessource.hh"

BatimentRessource::BatimentRessource(TypeRessource const & r, uint32 pos, TypeJoueur const & joueur)
    :Batiment(dataBatimentRessources.at(r).vie * MULT_ERE[(joueur == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2], pos, joueur), _ressource(r){}

std::string const &BatimentRessource::nom() const
{
    return dataBatimentRessources.at(_ressource).nom;
}

Ressources const &BatimentRessource::cout() const
{
    Ressources cout = dataBatimentRessources.at(_ressource).cout;
    return cout * MULT_ERE[ere()];
}

TypeRessource const &BatimentRessource::ressourceProduite() const
{
    return _ressource;
}

uint32 BatimentRessource::quantiteProduite() const
{
    return dataBatimentRessources.at(_ressource).quantite * MULT_ERE[ere()];
}
