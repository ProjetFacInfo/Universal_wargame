#pragma once

#include <list>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <cmath>

#include "Graphe.hh"

using Chemin = std::list<unsigned int>;

using Paths = std::unordered_map<std::shared_ptr<Troupe>, std::vector<Chemin>>; 

std::vector<Chemin> fabriqueChemin(Graphe graphe, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & troupe, std::list<std::shared_ptr<Troupe>> const &agentsRestants, Paths const & paths, unsigned int target);