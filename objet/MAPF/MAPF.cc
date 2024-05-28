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
    std::list<std::shared_ptr<Troupe>> agentsbis;
    std::list<unsigned int> targetsbis;
    while (!agents.empty()){
        auto target_it = targets.begin();
        auto agent_it = agents.begin();
        bool changement = false;
        while(agent_it != agents.end()){
            auto agent = *agent_it;
            auto target = *target_it;
            if (estAtteignable(graphe, carte, agent, target)){
                agentsbis.push_front(agent);
                agent_it = agents.erase(agent_it);
                targetsbis.push_front(target);
                target_it = targets.erase(target_it);
                changement = true;
            }
            else{
                graphe.delete_all_edge(*target_it, carte);
                ++agent_it;
                ++target_it;
            }
        }
        if (!changement){
            while (!agents.empty()){
                agentsbis.push_front(agents.front());
                targetsbis.push_front(targets.front());
                agents.pop_front();
                targets.pop_front();
            }
        }
    }
    for (auto const & agent : agentsbis){
        graphe.delete_all_edge(agent->pos(), carte);
    }
    while(!agentsbis.empty()){
        auto target_it = targetsbis.begin();
        auto agent_it = agentsbis.begin();
        while(agent_it != agentsbis.end() && !estAtteignable(graphe, carte, *agent_it, *target_it)){
            agent_it++;
            target_it++;
        }
        if (agent_it != agentsbis.end()){
            agents.push_back(*agent_it);
            targets.push_back(*target_it);
            agentsbis.erase(agent_it);
            targetsbis.erase(target_it);
        }
        else {
            for (auto const & agent : agentsbis){
                agents.push_back(agent);
            }
            for (auto const & target : targetsbis){
                targets.push_back(target);
            }
            break;
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
        if (!estAtteignable(graphe, carte, troupe, targets.front())) std::cout << "target non atteignable !" << std::endl;
        paths[troupe] = fabriqueChemin(graphe, carte, troupe, agents, paths, targets.front());
        targets.pop_front();
    }
    return paths;
}
