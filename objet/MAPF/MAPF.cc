#include "MAPF.hh"



bool estAtteignable(Graphe const & graphe, std::shared_ptr<Carte> const & carte, std::shared_ptr<Troupe> const & agent, unsigned int target){
    std::vector<bool> check(carte->taille(), false);
    std::queue<vertex> file;
    file.push(target);
    while(!file.empty()){
        if (file.front() == agent->pos()) return true;
        check[file.front()] = true;
        for (auto const & neighbor : graphe.neighbors(file.front(),carte,agent)){
            if (!check[neighbor._v]) file.push(neighbor._v);
        }
        file.pop();
    }
    return false;
}


void ordrePrio(Graphe graphe, std::shared_ptr<Carte> const & carte, std::list<std::shared_ptr<Troupe>> &agents, std::list<unsigned int> &targets){
    for (auto const & target : targets){
        graphe.delete_all_edge(target, carte);
    }
    std::list<std::shared_ptr<Troupe>> agentsbis(agents);
    std::list<unsigned int> targetsbis(targets);
    agents.clear();
    targets.clear();
    while (!agentsbis.empty()){
        auto target_it = targetsbis.begin();
        bool changement = false;
        auto agent_it = agentsbis.begin();
        while(agent_it != agentsbis.end()){
            auto agent = *agent_it;
            auto target = *target_it;
            graphe.add_all_edge(target, carte);
            if (estAtteignable(graphe, carte, agent, target)){
                agents.push_front(agent);
                agent_it = agentsbis.erase(agent_it);
                targets.push_front(target);
                target_it = targetsbis.erase(target_it);
                changement = true;
            }
            else{
                graphe.delete_all_edge(*target_it, carte);
                ++agent_it;
                ++target_it;
            }
        }
        if (!changement){
            while (!agentsbis.empty()){
                agents.push_front(agentsbis.front());
                targets.push_front(targetsbis.front());
                agentsbis.pop_front();
                targets.pop_front();
            }
        }
    }
}

Paths MAPF::run(std::shared_ptr<Carte> const &carte, std::list<std::shared_ptr<Troupe>> agents, std::list<unsigned int> targets)
{
    Graphe graphe(carte, agents);
    Paths paths;
    
    ordrePrio(graphe, carte, agents, targets);

    while (!agents.empty()){
        std::shared_ptr<Troupe> troupe = agents.front();
        agents.pop_front();
        paths[troupe] = fabriqueChemin(graphe, carte, troupe, agents, paths, targets.front());
        targets.pop_front();
    }
    return paths;
}
