#include "Graphe.hh"

Graphe::Graphe(std::shared_ptr<Carte> const & carte, std::list<std::shared_ptr<Troupe>> const & agents):_matrice(carte->taille() * (carte->taille() + 1) / 2 , false),_largeur(carte->largeur())
{
    _matrice.shrink_to_fit();
    for (vertex r = 0; r < carte->taille() ; ++r){
        if (!carte->getCase(r)._element) {
            add_all_edge(r, carte);
        }
    }
    for (auto const & agent : agents){
        add_all_edge(agent->pos(), carte);
    }
}

float Graphe::is_edge(vertex r, vertex c) const
{
    vertex min = std::min(r, c); 
    vertex max = std::max(r, c); 
    return _matrice[(max * (max + 1)) / 2 + min];
}

void Graphe::add_edge(vertex r, vertex c)
{
    vertex min = std::min(r, c); 
    vertex max = std::max(r, c); 
    _matrice[(max * (max + 1)) / 2 + min] = true;
}

void Graphe::add_all_edge(vertex r, std::shared_ptr<Carte> const & carte)
{
    if (carte->estCase(r / _largeur - 1, r % _largeur) && !carte->getCase(r / _largeur - 1, r % _largeur)._element, carte) add_edge(r / _largeur - 1, r % _largeur);
    if (carte->estCase(r / _largeur + 1, r % _largeur) && !carte->getCase(r / _largeur + 1, r % _largeur)._element, carte) add_edge(r / _largeur + 1, r % _largeur);
    if (carte->estCase(r / _largeur, r % _largeur - 1) && !carte->getCase(r / _largeur, r % _largeur - 1)._element, carte) add_edge(r / _largeur, r % _largeur - 1);
    if (carte->estCase(r / _largeur, r % _largeur + 1) && !carte->getCase(r / _largeur, r % _largeur + 1)._element, carte) add_edge(r / _largeur, r % _largeur + 1);
}

void Graphe::delete_edge(vertex r, vertex c)
{
    vertex min = std::min(r, c);
    vertex max = std::max(r, c);
    _matrice[(max * (max + 1)) / 2 + min] = false;
}

void Graphe::delete_all_edge(vertex r, std::shared_ptr<Carte> const & carte)
{
    for (unsigned int c = 0; c < carte->taille() ; ++c){
        delete_edge(r, c);
    }
}

float Graphe::cout(vertex r, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe) const{
    return troupe->accesTerrain(carte->getCase(r)._terrain) / troupe->pas();
}

std::list<Neighbor> Graphe::neighbors(vertex r, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe) const
{
    std::list<Neighbor> neighbors;
    if (is_edge(r, r - _largeur)){
        float cout = troupe->accesTerrain(carte->getCase(r - _largeur)._terrain) / troupe->pas();
        if (cout <= 1) neighbors.push_back(Neighbor(r - _largeur, cout));
    } 
    if (is_edge(r, r + _largeur)){
        float cout = troupe->accesTerrain(carte->getCase(r + _largeur)._terrain) / troupe->pas();
        if (cout <= 1) neighbors.push_back(Neighbor(r + _largeur, cout));
    } 
    if (is_edge(r, r - 1)){
        float cout = troupe->accesTerrain(carte->getCase(r - 1)._terrain) / troupe->pas();
        if (cout <= 1) neighbors.push_back(Neighbor(r - 1, cout));
    } 
    if (is_edge(r, r + 1)){
        float cout = troupe->accesTerrain(carte->getCase(r + 1)._terrain) / troupe->pas();
        if (cout <= 1) neighbors.push_back(Neighbor(r + 1, cout));
    } 
    return neighbors;
}
