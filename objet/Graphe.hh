#pragma once
#include <algorithm>

#include "Carte.hh"
#include "Troupe.hh"

using vertex = uint8_t;
using gint = uint8_t;

class Graphe{
private:
    vertex _n;
    std::vector<bool> _matrice;
public:
    Graphe(Carte const & carte, std::vector<Troupe> allies);
    gint nb_vertex() {return _n;};
    bool is_edge(vertex r, vertex c);
    void add_edge(vertex r, vertex c);
    void delete_edge(vertex r, vertex c);
};