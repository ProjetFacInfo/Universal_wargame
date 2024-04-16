#include "Joueur.hh"

const Ressources RESSOURCES_JOUEUR_INIT = {500, 500, 500};

Joueur::Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur)
    :_carte(carte), _ressources(RESSOURCES_JOUEUR_INIT), _base(carte->getCase((joueur == TypeJoueur::joueur1) ? carte->getPosBase1() : carte->getPosBase2())._element), _ere(0){}

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

/*
bool Joueur::acheterBatiment(TypeRessource const &ressource, uint16_t i, uint16_t j)
{
    Ressources cout = dataBatimentRessources.at(ressource).cout;
    // if (cout * MULT_ERE[_ere] < _ressources)
    return true;
}
*/