#include "../objet/Jeu.hh"
#include "../instance/carteInstanceTest.hh"
#include "../objet/MAPF/MAPF.hh"

/*
using Chemin = std::list<unsigned int>;
using Paths = std::unordered_map<std::shared_ptr<Troupe>, std::vector<Chemin>>; 
*/

void afficheTroupe(std::shared_ptr<Troupe> const & troupe, std::shared_ptr<Carte> const & carte){

    std::cout << "agent (";
    switch (troupe->getType())
    {
    case TypeTroupe::archer:
        std::cout << "archer";
        break;
    case TypeTroupe::catapulte:
        std::cout << "catapulte";
        break;
    case TypeTroupe::cavalier:
        std::cout << "cavalier";
        break;
    case TypeTroupe::infanterie:
        std::cout << "infanterie";
        break;
    default:
        break;
    }
    std::cout << ", " << troupe->pos() << ")" << std::endl;
}

void affichePaths(Paths const & paths, std::shared_ptr<Carte> const & carte){
    for (auto const & path : paths){
        afficheTroupe(path.first, carte);
        for (auto const & tourPath : path.second){
            std::cout << "( ";
            for (auto const & pos : tourPath){
                std::cout << pos << " ";
            }
            std::cout << ")"; 
        }
        std::cout << std::endl;
    }
}

int posX(unsigned int pos, std::shared_ptr<Carte> const & carte){
    return pos/carte->largeur();
}

int posY(unsigned int pos, std::shared_ptr<Carte> const & carte){
    return pos%carte->largeur();
}


int main(){

    std::shared_ptr<Carte> carte(std::make_shared<Carte>(maps.at("1")));
    IA j1(carte, TypeJoueur::joueur1);
    j1.giveTroupe(TypeTroupe::archer, posX(j1.getBase()->pos(), carte), posY(j1.getBase()->pos(), carte)-1);
    j1.giveTroupe(TypeTroupe::catapulte, posX(j1.getBase()->pos(), carte)-1, posY(j1.getBase()->pos(), carte)-1);
    j1.giveTroupe(TypeTroupe::cavalier, posX(j1.getBase()->pos(), carte)+1, posY(j1.getBase()->pos(), carte)-1);
    j1.giveTroupe(TypeTroupe::infanterie, posX(j1.getBase()->pos(), carte)-2, posY(j1.getBase()->pos(), carte)-1);
    j1.giveTroupe(TypeTroupe::archer, posX(j1.getBase()->pos(), carte)+2, posY(j1.getBase()->pos(), carte)-1);
    j1.giveTroupe(TypeTroupe::infanterie, posX(j1.getBase()->pos(), carte), posY(j1.getBase()->pos(), carte)-2);

    std::list<std::shared_ptr<Troupe>> agents = j1.getTroupes();
    std::list<unsigned int> targets {
        carte->pos(12, 12),
        carte->pos(6, 8),
        carte->pos(5, 5),
        carte->pos(5, 4),
        carte->pos(15, 10),
        carte->pos(14, 10),
    };

    Paths paths = MAPF::run(carte, agents, targets);
    
    affichePaths(paths, carte);

    return 0;
}