#include "Element.hh"

Element::Element(std::string const &nom, uint32 vie, uint32 pos, uint8 ere, Ressource const &cout)
    :_nom(nom),_vie(vie),_pos(pos),_ere(ere),_cout(cout){}

