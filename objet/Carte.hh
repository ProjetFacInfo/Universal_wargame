#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Terrain.hh"
#include "Element.hh"

#include "Batiment/Base.hh"

struct Case {
    std::shared_ptr<Element> _element;
    Terrain _terrain;

    Case():_element(nullptr),_terrain(Terrain::plaine){}
    Case(std::shared_ptr<Element> const & element):_element(element),_terrain(Terrain::plaine){}
    Case(Terrain const & terrain):_element(nullptr),_terrain(terrain){}
    Case(std::shared_ptr<Element> const & element, Terrain const & terrain):_element(element),_terrain(terrain){}

    void afficher(std::ostream & flux) const;
};


class Carte{
private:
    uint16_t _largeur; // horizontal
    uint16_t _longueur; // vertical
    std::vector<Case> _plateau;
    uint16_t _posBase1;
    uint16_t _posBase2;
    Case & _getCase(uint16_t i, uint16_t j);
public:
    Carte();
    Carte(std::array<Terrain, TAILLECARTE> const & liste_terrains);
    uint16_t largeur() const;
    uint16_t longueur() const;
    uint16_t taille() const;
    Case const & getCase(uint16_t i, uint16_t j) const;
    Case const & getCase(uint16_t i) const;
    uint16_t getPosBase1() const;
    uint16_t getPosBase2() const;
    void afficher(std::ostream & flux) const;
};
