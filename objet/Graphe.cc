#include "Graphe.hh"

Graphe::Graphe(Carte const & carte, std::vector<Troupe> allies):_n(carte.taille()), _matrice(_n * (_n + 1) / 2, false)
{
    _matrice.shrink_to_fit();
}

bool Graphe::is_edge(vertex r, vertex c)
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

void Graphe::delete_edge(vertex r, vertex c)
{
    vertex min = std::min(r, c);
    vertex max = std::max(r, c);
    _matrice[(max * (max + 1)) / 2 + min] = false;
}
