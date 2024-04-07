#pragma once

#include "Element.hh"

class Troupe: public Element{
private:
public:
    Troupe(std::string const & nom, uint32 vie, uint32 pos, uint8 ere, Ressource const & cout);
    TypeElement const & type() const override;
};