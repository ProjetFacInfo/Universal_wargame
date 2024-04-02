#pragma once
#include <vector>
#include <memory>

#include "Element.hh"
#include "Joueur.hh"

enum class Terrain{
    plaine, foret, colline, montagne, eau, mer, desert
};

struct Case {
private:
    std::shared_ptr<Element> _element;
    Terrain _terrain;
public:
    Case():_element(nullptr),_terrain(Terrain::plaine){}
    Case(std::shared_ptr<Element> const & element):_element(element),_terrain(Terrain::plaine){}
    Case(Terrain const & terrain):_element(nullptr),_terrain(terrain){}
    Case(std::shared_ptr<Element> const & element, Terrain const & terrain):_element(element),_terrain(terrain){}
};

const int TAILLECARTE = 16*16;

using Carte = std::vector<Case>;

class Jeu {
private:
    Carte _carte;
    Joueur _j1;
    Joueur _j2;
public:
    Jeu();

};