#pragma once
#include <string>
#include "ConstanteElement.hh"
using uint32 = uint32_t;
using uint8 = uint8_t;

enum class TypeElement { batiment, troupe };

enum class TypeJoueur {
	joueur1, joueur2
};


class Element {
protected:
	static uint8_t ere_joueur1;
	static uint8_t ere_joueur2;

private:
	std::string _nom;
	uint32 _vie;
	uint32 _pos;
	Ressource _cout;
	TypeJoueur _joueur;

public:
	Element(std::string const & nom, uint32 vie, uint32 pos, Ressource const & cout, TypeJoueur const & joueur);
	virtual TypeElement type() const = 0;
	
	void passerEreSuivante(TypeJoueur const & joueur);
};
