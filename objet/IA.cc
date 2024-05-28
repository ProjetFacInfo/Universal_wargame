#include "IA.hh"

IA::IA(std::shared_ptr<Carte> const &carte, TypeJoueur const &joueur):Joueur(carte, joueur){}

void IA::joue()
{
    if (_joueur == TypeJoueur::joueur1){
        std::list<unsigned int> targets {
            _carte->pos(12, 12),
            _carte->pos(8, 6),
            _carte->pos(5, 5),
            _carte->pos(4, 5),
            _carte->pos(10, 15),
            _carte->pos(8, 14),
        };
        auto cheminsParTroupe = trouveChemins(getTroupes(),targets);
        for(auto & chemin : cheminsParTroupe) {
            auto troupe = chemin.first;
            for (auto position : chemin.second){
                if (_carte->deplacer(troupe, position)){
                    std::cout << std::endl;
                    _carte->afficher(std::cout);
                    usleep(1000000);
                }
            }
        }
    }
    else if (_joueur == TypeJoueur::joueur2){
        std::list<unsigned int> targets {
            _carte->pos(10, 8),
            _carte->pos(6, 8),
            _carte->pos(2, 5),
            _carte->pos(9, 6),
            _carte->pos(5, 15),
            _carte->pos(14, 8),
        };
        auto cheminsParTroupe = trouveChemins(getTroupes(),targets);
        for(auto & chemin : cheminsParTroupe) {
            auto troupe = chemin.first;
            for (auto position : chemin.second){
                if (_carte->deplacer(troupe, position)){
                    std::cout << std::endl;
                    _carte->afficher(std::cout);
                    usleep(1000000);
                }
            }
        }
    }
}
