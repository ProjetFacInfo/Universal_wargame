#pragma once

#include "Graphe.hh"

class MAPF{
private:
    Graphe _graphe;
public:
    MAPF(Carte const & carte, std::vector<Troupe> allies);
};