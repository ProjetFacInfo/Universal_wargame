#include "Troupe.hh"

Troupe::Troupe(uint32 vie, uint32 pos, TypeJoueur const & joueur, TypeTroupe const & t)
    :Element(vie,pos, joueur), _type(t){}

TypeElement Troupe::type() const
{
    return TypeElement::troupe;
}

void Troupe::add_component(signature const & s, std::unique_ptr<IComponent> C) {
   _components.insert({s, std::move(C)});
}

void Troupe::remove_component(signature const & s) {
    _components.erase(s);
}

std::string const & Troupe::nom() const {
    return dataTroupeRessources.at(_type).nom;
}

Ressources const & Troupe::cout() const {
    Ressources cout = dataTroupeRessources.at(_type).cout;
    return cout * MULT_ERE[ere()];
}
