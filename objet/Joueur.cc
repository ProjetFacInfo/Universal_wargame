#include "Joueur.hh"

const Ressources RESSOURCES_JOUEUR_INIT = {500, 500, 500};

Joueur::Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur)
    :_carte(carte), _ressources(RESSOURCES_JOUEUR_INIT), _base(carte->getCase((joueur == TypeJoueur::joueur1) ? carte->getPosBase1() : carte->getPosBase2())._element), _ere(0), _type(joueur){}

std::shared_ptr<Carte> const &Joueur::getCarte() const
{
    return _carte;
}

Ressources const &Joueur::getRessources() const
{
    return _ressources;
}

std::queue<BatimentRessource> const &Joueur::getBatiments() const
{
    return _batiments;
}

std::queue<Troupe> const &Joueur::getTroupes() const
{
    return _troupes;
}

std::shared_ptr<Element> const &Joueur::getBase() const
{
    return _base;
}

bool Joueur::aPerdu() const
{
    return _base->estDetruit();
}

bool Joueur::acheterBatimentRessource(TypeRessource const &ressource, uint16_t i, uint16_t j)
{
    if (dataBatimentRessources.at(ressource).cout * MULT_ERE[_ere] <= _ressources){
        _carte->poseElement(std::make_shared<BatimentRessource>(ressource, _carte->pos(i,j), _type, _ere), i, j);
        _ressources -= dataBatimentRessources.at(ressource).cout * MULT_ERE[_ere];
        return true;
    }
    return false;
}