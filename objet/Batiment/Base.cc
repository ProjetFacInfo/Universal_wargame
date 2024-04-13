#include "Base.hh"

const std::string NOM_BASE = "Base";
const Ressources RESSOURCE_VIDE;

Base::Base(uint32_t pos, TypeJoueur const & joueur)
    :Batiment(1000, pos, joueur){}

std::string const &Base::nom() const
{
    return NOM_BASE;
}

Ressources const &Base::cout() const
{
    return RESSOURCE_VIDE;
}
