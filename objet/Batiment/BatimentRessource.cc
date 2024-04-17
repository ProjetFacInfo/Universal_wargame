#include "BatimentRessource.hh"

BatimentRessource::BatimentRessource(TypeRessource const & r, uint32 pos, TypeJoueur const & joueur, uint8 ere)
    :Batiment(dataBatimentRessources.at(r).vie * MULT_ERE[ere], pos, joueur), _ressource(r){}

std::string const &BatimentRessource::nom() const
{
    return dataBatimentRessources.at(_ressource).nom;
}

Ressources BatimentRessource::cout(uint8 ere) const
{
    return dataBatimentRessources.at(_ressource).cout * MULT_ERE[ere];
}

void BatimentRessource::evolue(uint8 ere)
{
}

TypeRessource const &BatimentRessource::ressourceProduite() const
{
    return _ressource;
}

uint32 BatimentRessource::quantiteProduite(uint8 ere) const
{
    return dataBatimentRessources.at(_ressource).quantite * MULT_ERE[ere];
}
