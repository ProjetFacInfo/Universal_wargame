#include "Joueur.hh"

class IA: public Joueur{
public:
    IA(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur);
    void joue();
};