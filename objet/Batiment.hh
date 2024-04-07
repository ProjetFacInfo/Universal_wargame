#pragma once

#include "Element.hh"

class Batiment: public Element{
private:

public:
    Batiment(std::string const & nom, uint32 vie, uint32 pos, uint8 ere, Ressource const & cout);
    TypeElement const & type() const override;
};