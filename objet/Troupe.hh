#pragma once

#include "Component/Components.hh"
#include "Element.hh"
#include <map>

class Troupe: public Element{
private:
    std::map<signature, std::unique_ptr<IComponent>> _components;

public:
    Troupe(std::string const & nom, uint32 vie, uint32 pos, Ressource const & cout, TypeJoueur const & joueur);
    TypeElement type() const override;
    void add_component(signature const & s, std::unique_ptr<IComponent> C);
    void remove_component(signature const & s);
};
