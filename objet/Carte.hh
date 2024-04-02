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

const int TAILLECARTE = 16*16;

class Carte{
private: 
    std::vector<Case> _plateau;
public:
    Carte();
};