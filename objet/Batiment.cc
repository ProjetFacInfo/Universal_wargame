#include "Batiment.hh"

Batiment::Batiment(std::string const & nom, uint32 vie, uint32 pos, Ressource const & cout, TypeJoueur const & joueur)
    :Element(nom,vie,pos,cout, joueur){}

TypeElement Batiment::type() const
{
    return TypeElement::batiment;
}
