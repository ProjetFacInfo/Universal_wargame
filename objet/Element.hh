#pragma once
#include <string>
using uint32 = uint32_t;
using uint8 = uint8_t;

enum class TypeElement { batiment, troupe };

struct Ressource {
	uint32 _metaux, _bois, _viande;
public:
	Ressource():_metaux(0),_bois(0),_viande(0){}
	Ressource(uint32_t metaux, uint32_t bois, uint32_t viande):_metaux(metaux),_bois(bois),_viande(viande){}
	uint32_t Metaux() const {return _metaux;}
	uint32_t Bois() const {return _bois;}
	uint32_t Viande() const {return _viande;}
};


class Element {
private:
	std::string _nom;
	uint32 _vie;
	uint32 _pos;
	uint8  _ere;
	Ressource _cout;

public:
	Element(std::string const & nom, uint32 vie, uint32 pos, uint8 ere, Ressource const & cout);
	virtual TypeElement const & type() const = 0;
};
