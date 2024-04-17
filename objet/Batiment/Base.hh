#pragma once
#include "../Batiment.hh"

class Base : public Batiment{
private:

public:
    Base(uint32_t pos, TypeJoueur const & joueur);
    std::string const & nom() const override;
	Ressources cout(uint8 ere) const override;
    void evolue(uint8 ere) override;
};