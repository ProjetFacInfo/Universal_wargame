#include "Base.hh"

Base::Base(uint32_t pos, TypeJoueur const & joueur)
    :Batiment(1000, pos, joueur){}

std::string const &Base::nom() const
{
    return "Base";
}

Ressource const &Base::cout() const
{
    return Ressource();
}
