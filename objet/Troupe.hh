#pragma once

#include "Component/Components.hh"
#include "Element.hh"
#include <map>

class Troupe: public Element{
private:
    std::map<signature, std::unique_ptr<IComponent>> _components;
    TypeTroupe _type;

private:
    Troupe(uint32 vie, uint32 pos, TypeJoueur const & joueur, TypeTroupe const & t);

public:
    TypeElement type() const override;
    void add_component(signature const & s, std::unique_ptr<IComponent> C);
    void remove_component(signature const & s);
    std::string const & nom() const override;
    Ressource const & cout() const override;

};
