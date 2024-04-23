#pragma once
#include <algorithm>
#include <list>

#include "Carte.hh"
#include "Troupe.hh"

using vertex = uint8;
using gint = uint8;

struct Neighbor{
    vertex _v;
    uint8 _cost;
    Neighbor(vertex v, uint8 cost):_v(v),_cost(cost){}
};

class Graphe{
private:
    std::vector<float> _matrice;
public:
    Graphe(std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe_a_deplacer);
    gint nb_vertex() const;
    float is_edge(vertex r, vertex c) const;
    void add_edge(vertex r, vertex c, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe_a_deplacer);
    void add_all_edge(vertex r, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe_a_deplacer);
    void delete_edge(vertex r, vertex c);
    void delete_all_edge(vertex r);

    std::list<Neighbor> neighbors(vertex v) const;
};