#include "BatimentRessource.hh"

BatimentRessource::BatimentRessource(TypeRessource const & r, uint32_t pos, TypeJoueur const & joueur)
    :Batiment(dataBatimentRessources.at(r).vie, pos, joueur), _ressource(r){}

std::string const &BatimentRessource::nom() const
{
    return dataBatimentRessources.at(_ressource).nom;
}

Ressource const &BatimentRessource::cout() const
{
    return dataBatimentRessources.at(_ressource).cout;
}

TypeRessource const &BatimentRessource::ressourceProduite() const
{
    return _ressource;
}

uint32_t BatimentRessource::quantiteProduite() const
{
    return dataBatimentRessources.at(_ressource).quantite;
}
