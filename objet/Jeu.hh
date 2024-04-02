#pragma once
#include <vector>
#include <memory>

#include "Element.hh"
#include "Joueur.hh"

enum class Terrain{
    plaine, foret, colline, montagne, eau, mer, desert
};

struct Case {
    std::shared_ptr<Element> _element;
    Terrain _terrain;
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