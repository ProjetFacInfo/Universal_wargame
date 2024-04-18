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
private:
	uint32 _vie;
	TypeJoueur _joueur;

protected:
	// En protected pour que Troupe puisse y accéder
	// avec la méthode deplacer().
	uint32 _pos;

protected:
	void setVie(uint32 vie);

public:
	Element(uint32 vie, uint32 pos, TypeJoueur const & joueur);
	virtual TypeElement type() const = 0;
	virtual std::string const & nom() const =0;
	virtual Ressources cout(uint8 ere) const =0;
	virtual void evolue(uint8 ere) =0;
	uint32 vie() const {return _vie;}
	uint32 pos() const {return _pos;}
	TypeJoueur const & joueur() const {return _joueur;}

	void retirerVie(uint32 vieARetirer);
	bool estDetruit() const;
};
