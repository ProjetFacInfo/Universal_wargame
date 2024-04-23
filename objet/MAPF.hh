#pragma once

#include <list>
#include <vector>

#include "Graphe.hh"

using Chemin = std::list<uint16>;

using CheminParTroupe = std::map<std::shared_ptr<Troupe>, Chemin>;

using Chemins = std::vector<CheminParTroupe>;

class MAPF{
private:
    Graphe _graphe;
public:
    MAPF(Carte const & carte, std::vector<Troupe> allies);
};