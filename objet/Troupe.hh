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
    Ressources cout(uint8 ere) const override;
    void evolue(uint8 ere) override;
    uint32 attaque() const;
    uint32 portee_min() const;
    uint32 portee_max() const;
    uint32 defense() const;
    uint32 pas() const;
    uint32 accesTerrain(Terrain const & t) const;

    //TODO:
    // liste des positions attaquable

    friend BatimentTroupe;
};
