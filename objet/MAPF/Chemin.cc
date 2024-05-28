#include "Chemin.hh"

struct InfoChemins{
    float * _cost;
    InfoChemins():_cost(new float(std::numeric_limits<unsigned int>::max())){}
};

std::list<unsigned int> modifGraphe(Graphe & graphe, std::shared_ptr<Carte> const & carte, Paths const paths, unsigned int tour){
    std::list<unsigned int> sommetAjout;
    for (auto const & path : paths){
        if (path.second.size() > tour - 1){ 
            sommetAjout.push_back(path.second.at(tour-2).back());
            graphe.add_all_edge(sommetAjout.back(), carte);
            std::list<unsigned int> listChemins = path.second.at(tour-1);
            auto dernier_element = listChemins.end(); dernier_element--;
            for (auto it = listChemins.begin() ; it != dernier_element; ++it){
                sommetAjout.push_back(*it);
                graphe.add_all_edge(sommetAjout.back(), carte);
            }
            graphe.delete_all_edge(*dernier_element, carte);
        }
        else if (path.second.size() > tour - 2){ 
            sommetAjout.push_back(path.second.at(tour-2).back());
            graphe.add_all_edge(sommetAjout.back(), carte);
        }
    }
    return sommetAjout;
}

bool aUpdate(Graphe const & graphe, std::shared_ptr<Carte> const & carte, std::vector<bool> const & check, std::shared_ptr<Troupe> const &troupe, vertex const & v){

    for (auto const & neighbor : graphe.neighbors(v, carte, troupe)){
        if (check.at(neighbor._v)) return true;
    }
    return false;
}

void suppInitGraphe(Graphe & graphe, std::shared_ptr<Carte> const & carte, Paths const paths){
    for (auto const & path : paths){
        if (path.second.size() > 0){ 
            graphe.delete_all_edge(path.second.at(0).back(), carte);
            if (path.second.size() > 1) {
                for (unsigned int i = 1 ; i < path.second.size() ; ++i){
                    std::list<unsigned int> listChemins = path.second.at(i);
                    for (auto it = listChemins.begin() ; it != listChemins.end(); ++it){
                        graphe.delete_all_edge(*it, carte);
                    }
                }
            }
        }
    }
}

unsigned int tourMax(Paths const & paths){
    unsigned int tour = 0;
    for (auto const & path : paths){
        if (path.second.size()>tour) tour = path.second.size();
    }
    return tour;
}

// Algorithme de dijkstra modifié
std::vector<InfoChemins> construitInfosChemins(Graphe graphe, std::shared_ptr<Carte> const &carte, Paths const & paths, std::shared_ptr<Troupe> const &troupe, unsigned int target)
{
    struct Voisin {
        vertex _v;
        float * _cost;
        Voisin(vertex v, float * cost):_v(v),_cost(cost){}
    };

    unsigned int maxTour = tourMax(paths);

    suppInitGraphe(graphe, carte, paths);
    
    std::vector<InfoChemins> listInfosChemins(carte->taille());
    std::list<Voisin> list;
    std::vector<bool> check(carte->taille(), false);
    std::vector<bool> check2(carte->taille(), false);
    unsigned int start = troupe->pos();
    listInfosChemins[start]._cost = new float(0);
    
    list.push_front(Voisin(start, new float(0)));
    check[start] = true;
    unsigned int tour = 1;
    do {
        while (!list.empty()){
            Voisin n = list.front();
            check2[n._v] = true;
            if (n._v == target) return listInfosChemins;
            list.pop_front();
            if (*n._cost >= tour){
                tour++;
                std::list<unsigned int> nouveaux_sommets = modifGraphe(graphe, carte, paths, tour);
                for (auto const & sommet : nouveaux_sommets){
                    if (aUpdate(graphe, carte, check2, troupe, sommet)){
                        *listInfosChemins[sommet]._cost = tour-1+graphe.cout(sommet, carte, troupe);
                        if (*listInfosChemins[sommet]._cost > tour)
                            *listInfosChemins[sommet]._cost = std::numeric_limits<unsigned int>::max();
                        else{ 
                            check[sommet] = true;
                            list.push_back(Voisin(sommet, listInfosChemins[sommet]._cost));
                        }
                    }
                }
            } 
            for (auto const & neighbor : graphe.neighbors(n._v, carte, troupe)){
                float cost = neighbor._cost + *listInfosChemins[n._v]._cost;
                if (cost > tour) cost = tour+neighbor._cost;
                if (cost < *listInfosChemins[neighbor._v]._cost){
                    *listInfosChemins[neighbor._v]._cost = cost;
                    if (!check[neighbor._v]){
                        check[neighbor._v] = true;
                        list.push_back(Voisin(neighbor._v, listInfosChemins[neighbor._v]._cost));
                    }
                }
            }
            list.sort([](Voisin const & v1, Voisin const & v2){ return *v1._cost < *v2._cost;});
        }
        tour++;
        if (tour <= maxTour){
            std::list<unsigned int> nouveaux_sommets = modifGraphe(graphe, carte, paths, tour);
            for (auto const & sommet : nouveaux_sommets){
                if (aUpdate(graphe, carte, check2, troupe, sommet)){
                    *listInfosChemins[sommet]._cost = tour-1+graphe.cout(sommet, carte, troupe);
                    if (*listInfosChemins[sommet]._cost > tour)
                        *listInfosChemins[sommet]._cost = std::numeric_limits<unsigned int>::max();
                    else{ 
                        check[sommet] = true;
                        list.push_back(Voisin(sommet, listInfosChemins[sommet]._cost));
                    }
                }
            }
            list.sort([](Voisin const & v1, Voisin const & v2){ return *v1._cost < *v2._cost;});
        }
    }while(tour <= maxTour);
    return listInfosChemins;
}

std::vector<Chemin> construitChemin(Graphe const & graphe, std::shared_ptr<Carte> const & carte, std::vector<InfoChemins> const & listInfosChemins, std::shared_ptr<Troupe> const & troupe, unsigned int target){

    /*
    unsigned int i = 0;
    for (auto const & infoChemins : listInfosChemins){
        if (*infoChemins._cost == std::numeric_limits<unsigned int>::max()) std::cout << "inf" << "\t";
        else std::cout << *infoChemins._cost << "\t";
        i++;
        if (i == 16){
            i = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    */
    
    if (*listInfosChemins[target]._cost < std::numeric_limits<unsigned int>::max()){
        unsigned int nbTours = (int)std::ceil(*listInfosChemins[target]._cost);
        std::vector<Chemin> listTourChemins(nbTours);
        unsigned int tourActuel = nbTours;
        listTourChemins[tourActuel-1].push_front(target);
        while(target != troupe->pos()){
            float costMin(*listInfosChemins[target]._cost);
            unsigned int next(target);
            for (auto const & neighbor : graphe.neighbors(target, carte, troupe)){
                if (costMin > *listInfosChemins[neighbor._v]._cost) {
                    costMin = *listInfosChemins[neighbor._v]._cost;
                    next = neighbor._v; 
                }
            }
            if (target == next){
                std::cout << "pb MAPF !" << std::endl;
                return std::vector<Chemin>(1, std::list<unsigned int>{troupe->pos()});
            }
            target = next;
            if (tourActuel > std::ceil(*listInfosChemins[target]._cost)){
                tourActuel = std::ceil(*listInfosChemins[target]._cost);
            }
            if (target != troupe->pos()) listTourChemins[tourActuel-1].push_front(target);
        }
        return listTourChemins;
    }
    return std::vector<Chemin>(1, std::list<unsigned int>{troupe->pos()});
}

std::vector<Chemin> fabriqueChemin(Graphe graphe, std::shared_ptr<Carte> const &carte, std::shared_ptr<Troupe> const &troupe, std::list<std::shared_ptr<Troupe>> const &agentsRestants, Paths const & paths, unsigned int target)
{
    for (auto const & agent: agentsRestants){
        graphe.delete_all_edge(agent->pos(), carte);
    }
    return construitChemin(graphe, carte, construitInfosChemins(graphe, carte, paths, troupe, target), troupe, target);
}
