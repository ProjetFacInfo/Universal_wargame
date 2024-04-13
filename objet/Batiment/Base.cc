#include "Base.hh"

Base::Base(uint32 pos, TypeJoueur const & joueur)
    :Batiment("Base", 1000, pos, Ressource(), joueur){}
