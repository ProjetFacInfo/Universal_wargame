#pragma once

#include "Element.hh"

class BatimentTroupe;

class Troupe: public Element{
private:
    TypeTroupe _typeTroupe;

private:

public:
    Troupe(uint32 vie, uint32 pos, TypeJoueur const & joueur, TypeTroupe const & t);
    TypeElement type() const override;
    std::string const & nom() const override;
    Ressources cout() const override;


    friend BatimentTroupe;
};
