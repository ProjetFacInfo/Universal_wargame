#pragma once
#include <memory>
#include <vector>
#include "Element.hh"

enum class Terrain{
    plaine, foret, colline, montagne, eau, mer, desert
};

struct Case {
    std::shared_ptr<Element> _element;
    Terrain _terrain;
    
    Case():_element(nullptr),_terrain(Terrain::plaine){}
    Case(std::shared_ptr<Element> const & element):_element(element),_terrain(Terrain::plaine){}
    Case(Terrain const & terrain):_element(nullptr),_terrain(terrain){}
    Case(std::shared_ptr<Element> const & element, Terrain const & terrain):_element(element),_terrain(terrain){}
};

const uint16_t LARGEURCARTE = 16;
const uint16_t LONGUEURCARTE = 16;

class Carte{
private: 
    uint16_t _largeur; // horizontal
    uint16_t _longueur; // vertical
    std::vector<Case> _plateau;
public:
    Carte();
    uint16_t largeur() const;
    uint16_t longueur() const;
    uint16_t taille() const;
    Case const & getCase(uint16_t i, uint16_t j) const;
};