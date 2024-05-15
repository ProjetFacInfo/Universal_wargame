#pragma once

#include <list>
#include <vector>

#include "Chemin.hh"

class MAPF{
public:
    MAPF() = delete;
    Paths run(std::shared_ptr<Carte> const &carte, std::list<std::shared_ptr<Troupe>> agents, std::list<unsigned int> targets);
};