#pragma once
#include "../Batiment.hh"

class Base : public Batiment{
private:

public:
    Base(uint32_t pos, TypeJoueur const & joueur);
    std::string const & nom() const override;
	Ressources const & cout() const override;
};