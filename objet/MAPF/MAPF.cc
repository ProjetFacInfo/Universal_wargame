#include "MAPF.hh"

Paths MAPF::run(std::shared_ptr<Carte> const &carte, std::list<std::shared_ptr<Troupe>> agents, std::list<unsigned int> targets)
{
    Graphe graphe(carte, agents);
    Paths paths;

    int i = 0;
    while (!agents.empty()){
        std::shared_ptr<Troupe> troupe = agents.front();
        agents.pop_front();
        paths[troupe] = fabriqueChemin(graphe, carte, troupe, agents, paths, targets.front());
        targets.pop_front();
        i++;
    }
    return paths;
}
