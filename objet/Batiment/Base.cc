#include "Base.hh"

Base::Base(uint32_t pos, TypeJoueur const & joueur)
    :Batiment("Base", 1000, pos, Ressource(), joueur){}
