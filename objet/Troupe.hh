#pragma once

#include <vector>
#include <memory>
#include "Element.hh"

class BatimentTroupe;

class Troupe: public Element{
private:
    TypeTroupe _typeTroupe;


public:
    Troupe(uint32 pos, TypeJoueur const & joueur, TypeTroupe const & t, uint8 ere);
    TypeElement type() const override;
    std::string const & nom() const override;
    Ressources cout(uint8 ere) const override;
    void evolue(uint8 ere) override;
    uint32 attaque() const;
    uint32 portee_min() const;
    uint32 portee_max() const;
    uint32 defense() const override;
    uint32 pas() const;
    uint32 accesTerrain(Terrain const & t) const;

    void deplacer(uint32 pos);

    // liste des positions attaquable
    std::vector<uint32> list_pos_attaquable() const;

    void attaquer(std::shared_ptr<Element> T) const;



private:
    // Une fonction pour vérifié si une position valable
    // dans la fonction list_pos_attaquable selon la portee.
    bool position_valable(int x1, int y1, int x2, int y2, int dist) const;

    friend BatimentTroupe;
};
