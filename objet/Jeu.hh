#pragma once
#include <vector>
#include <memory>

#include "Element.hh"

enum class Terrain{
    plaine, foret, colline, montagne, eau, mer, desert
};

struct Case {
    std::shared_ptr<Element> _element;
    Terrain _terrain;
};

using TailleCarte = 16*16;

using Carte = std::vector<Case, TailleCarte>

class Jeu {
private:
    Carte _carte;

public:
    Jeu();
};