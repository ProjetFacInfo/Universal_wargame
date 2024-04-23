#include "Graphe.hh"

Graphe::Graphe(std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe_a_deplacer):_matrice(carte->taille() * carte->taille() , false)
{
    _matrice.shrink_to_fit();
    for (vertex r = 0; r < nb_vertex() ; ++r){
        if (!carte->getCase(r)._element) {
            add_all_edge(r, carte, troupe_a_deplacer);
        }
    }
    add_all_edge(troupe_a_deplacer->pos(), carte,  troupe_a_deplacer);
}

gint Graphe::nb_vertex() const
{
    return _matrice.size();
}

float Graphe::is_edge(vertex r, vertex c) const
{
    return _matrice[r*nb_vertex()+c];
}

void Graphe::add_edge(vertex r, vertex c, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe_a_deplacer)
{
    _matrice[r*nb_vertex()+c] = true;
}

void Graphe::add_all_edge(vertex r, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe_a_deplacer)
{
    if (carte->estCase(r / carte->largeur() - 1, r % carte->largeur()) && !carte->getCase(r / carte->largeur() - 1, r % carte->largeur())._element && troupe_a_deplacer->accesTerrain(carte->getCase(r / carte->largeur() - 1, r % carte->largeur())._terrain) <= troupe_a_deplacer->pas()) add_edge(r, carte->pos(r / carte->largeur() - 1, r % carte->largeur()), carte, troupe_a_deplacer);
    if (carte->estCase(r / carte->largeur() + 1, r % carte->largeur()) && !carte->getCase(r / carte->largeur() + 1, r % carte->largeur())._element && troupe_a_deplacer->accesTerrain(carte->getCase(r / carte->largeur() + 1, r % carte->largeur())._terrain) <= troupe_a_deplacer->pas()) add_edge(r, carte->pos(r / carte->largeur() + 1, r % carte->largeur()), carte, troupe_a_deplacer);
    if (carte->estCase(r / carte->largeur(), r % carte->largeur() - 1) && !carte->getCase(r / carte->largeur(), r % carte->largeur() - 1)._element && troupe_a_deplacer->accesTerrain(carte->getCase(r / carte->largeur(), r % carte->largeur() - 1)._terrain) <= troupe_a_deplacer->pas()) add_edge(r, carte->pos(r / carte->largeur(), r % carte->largeur() - 1), carte, troupe_a_deplacer);
    if (carte->estCase(r / carte->largeur(), r % carte->largeur() + 1) && !carte->getCase(r / carte->largeur(), r % carte->largeur() + 1)._element && troupe_a_deplacer->accesTerrain(carte->getCase(r / carte->largeur(), r % carte->largeur() + 1)._terrain) <= troupe_a_deplacer->pas()) add_edge(r, carte->pos(r / carte->largeur(), r % carte->largeur() + 1), carte, troupe_a_deplacer);
}

void Graphe::delete_edge(vertex r, vertex c)
{
    _matrice[r*nb_vertex()+c] = false;
}

void Graphe::delete_all_edge(vertex r)
{
    for (vertex c = 0; c < nb_vertex() ; ++c){
        delete_edge(r, c);
    }
}

std::list<Neighbor> Graphe::neighbors(vertex v) const
{
    std::list<Neighbor> neighbors;
    for (vertex c = 0; c < nb_vertex() ; ++c){
        float cost = is_edge(v, c);
        if (cost) neighbors.push_back(Neighbor(c, cost));
    }
    return neighbors;
}
