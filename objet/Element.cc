#include "Element.hh"

Element::Element(std::string const &nom, Type const &type, uint32 vie, uint32 pos, uint8 ere, Ressource const &cout)
    :_nom(nom),_type(type),_vie(vie),_pos(pos),_ere(ere),_cout(cout){}

Type const &Element::type() const
{
    return _type;
}
