#pragma once

#include "Element.hh"

class Troupe: public Element{
private:
public:
    Troupe(std::string const & nom, uint32 vie, uint32 pos, Ressource const & cout);
    TypeElement type() const override;
};