#include "Joueur.hh"

const Ressources RESSOURCES_JOUEUR_INIT = {500, 500, 500};

Joueur::Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur)
    :_carte(carte), _ressources(RESSOURCES_JOUEUR_INIT), _base(carte->getCase((joueur == TypeJoueur::joueur1) ? carte->getPosBase1() : carte->getPosBase2())._element), _ere(0), _joueur(joueur){}

std::shared_ptr<Carte> const &Joueur::getCarte() const
{
    return _carte;
}

Ressources const &Joueur::getRessources() const
{
    return _ressources;
}

std::list<std::shared_ptr<BatimentRessource>> const &Joueur::getBatimentsRessources() const
{
    return _batimentsRessources;
}

std::list<std::shared_ptr<BatimentTroupe>> const &Joueur::getBatimentsTroupes() const
{
    return _batimentsTroupes;
}

std::list<std::shared_ptr<Troupe>> const &Joueur::getTroupes() const
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
    std::shared_ptr<BatimentRessource> batiment = std::make_shared<BatimentRessource>(ressource, _carte->pos(i,j), _joueur, _ere);
    if (_carte->caseBatimentAdjacent(_joueur, i, j) && batiment->cout(_ere) <= _ressources){
        _carte->poseElement(batiment, i, j);
        _batimentsRessources.push_back(batiment);
        _ressources -= batiment->cout(_ere);
        return true;
    }
    return false;
}

bool Joueur::acheterBatimentTroupe(uint16_t i, uint16_t j)
{
    std::shared_ptr<BatimentTroupe> batiment = std::make_shared<BatimentTroupe>(_carte->pos(i,j), _joueur, _ere);
    if (_carte->caseBatimentAdjacent(_joueur, i, j) && batiment->cout(_ere) <= _ressources){
        _carte->poseElement(batiment, i, j);
        _batimentsTroupes.push_back(batiment);
        _ressources -= batiment->cout(_ere);
        return true;
    }
    return false;
}

bool Joueur::acheterTroupe(TypeTroupe const &troupe, uint16_t i, uint16_t j)
{
    std::shared_ptr<Troupe> tr = std::make_shared<Troupe>(_carte->pos(i,j), _joueur, troupe, _ere);
    if (_carte->caseBatimentAdjacent(_joueur, i, j) && tr->cout(_ere) <= _ressources){
        _carte->poseElement(tr, i, j);
        _troupes.push_back(tr);
        _ressources -= tr->cout(_ere);
        return true;
    }
    return false;
}

bool Joueur::giveTroupe(TypeTroupe const &troupe, uint16_t i, uint16_t j)
{
    std::shared_ptr<Troupe> tr = std::make_shared<Troupe>(_carte->pos(i,j), _joueur, troupe, _ere);
    _carte->poseElement(tr, i, j);
    _troupes.push_back(tr);
    return true;
}

std::unordered_map<std::shared_ptr<Troupe>, std::list<unsigned int>> Joueur::trouveChemins(std::list<std::shared_ptr<Troupe>> agents, std::list<unsigned int> targets)
{
    Paths paths = MAPF::run(_carte, agents, targets);
    std::unordered_map<std::shared_ptr<Troupe>, std::list<unsigned int>> res;
    for(auto const & path : paths){
        res[path.first] = path.second.at(0);
    }
    return res;
}

std::shared_ptr<Element> Joueur::cible(std::shared_ptr<Troupe> t) const {
    auto list_pos_att = t->list_pos_attaquable();
    for (auto pos : list_pos_att) {
        auto elm = _carte->at(pos)._element;
        if (elm and elm->joueur() != _joueur) {
            return elm;
        }
    }
    return nullptr;
}

void Joueur::combat() {
    for (const auto & t : _troupes) {
        auto ennemi = cible(t);
        if (ennemi) {
            t->attaquer(ennemi);
        }
    }
}

void Joueur::passerEreSuivante()
{
    // Definir les conditions pour passer à l'ère suivante à faire
    _ere++;
    for (auto const & el : _batimentsRessources) el->evolue(_ere);
    for (auto const & el : _batimentsTroupes) el->evolue(_ere);
    for (auto const & el : _troupes) el->evolue(_ere);
}
