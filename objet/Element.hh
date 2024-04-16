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
	static uint8 ere_joueur1;
	static uint8 ere_joueur2;

private:
	uint32 _vie;
	uint32 _pos;
	TypeJoueur _joueur;

public:
	Element(uint32 vie, uint32 pos, TypeJoueur const & joueur);
	virtual TypeElement type() const = 0;
	virtual std::string const & nom() const =0;
	virtual Ressources cout() const =0;
	uint32 vie() const {return _vie;}
	uint32 pos() const {return _pos;}
	TypeJoueur const & joueur() const {return _joueur;}
	uint8 ere() const;

	static void passerEreSuivante(TypeJoueur const & joueur);
	void retirerVie(uint32 vieARetirer);
	bool estDetruit() const;
};
