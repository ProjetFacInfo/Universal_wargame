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

std::queue<std::shared_ptr<BatimentRessource>> const &Joueur::getBatimentsRessources() const
{
    return _batimentsRessources;
}

std::queue<std::shared_ptr<BatimentTroupe>> const &Joueur::getBatimentsTroupes() const
{
    return _batimentsTroupes;
}

std::queue<std::shared_ptr<Troupe>> const &Joueur::getTroupes() const
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
    std::shared_ptr<BatimentRessource> batiment = std::make_shared<BatimentRessource>(ressource, _carte->pos(i,j), _type, _ere);
    if (_carte->caseBatimentAdjacent(_type, i, j) && batiment->cout(_ere) <= _ressources){
        _carte->poseElement(batiment, i, j);
        _batimentsRessources.push(batiment);
        _ressources -= batiment->cout(_ere);
        return true;
    }
    return false;
}

bool Joueur::acheterBatimentTroupe(uint16_t i, uint16_t j)
{
    std::shared_ptr<BatimentTroupe> batiment = std::make_shared<BatimentTroupe>(_carte->pos(i,j), _type, _ere);
    if (_carte->caseBatimentAdjacent(_type, i, j) && batiment->cout(_ere) <= _ressources){
        _carte->poseElement(batiment, i, j);
        _batimentsTroupes.push(batiment);
        _ressources -= batiment->cout(_ere);
        return true;
    }
    return false;
}

bool Joueur::acheterTroupe(TypeTroupe const &troupe, uint16_t i, uint16_t j)
{
    return false;
}
