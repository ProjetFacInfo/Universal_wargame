#include "Troupe.hh"

Troupe::Troupe(std::string const &nom, uint32 vie, uint32 pos, Ressource const &cout, TypeJoueur const & joueur)
    :Element(nom,vie,pos,cout, joueur){}

TypeElement Troupe::type() const
{
    return TypeElement::troupe;
}

void Troupe::add_component(signature const & s, std::unique_ptr<Icomponent> C) {
   _components.insert({s, std::move(C)});
}

void Troupe::remove_component(signature const & s) {
    _components.erase(s);
}
