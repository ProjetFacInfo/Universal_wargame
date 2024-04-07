#include "Batiment.hh"

Batiment::Batiment(std::string const & nom, uint32 vie, uint32 pos, uint8 ere, Ressource const & cout)
    :Element(nom,vie,pos,ere,cout){}

TypeElement const &Batiment::type() const
{
    return TypeElement::batiment;
}
