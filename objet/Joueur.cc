#include "Joueur.hh"

const Ressources RESSOURCES_JOUEUR_INIT = {500, 500, 500};

Joueur::Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur)
    :_ressources(RESSOURCES_JOUEUR_INIT), _base(carte->getCase((joueur == TypeJoueur::joueur1) ? carte->getPosBase1() : carte->getPosBase2())._element){}
