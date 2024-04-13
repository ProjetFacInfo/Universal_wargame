#pragma once

#include <map>
#include <string>
#include <array>

const uint8_t NB_ERE = 5;

const std::array<float, NB_ERE> MULT_ERE {
    1, 1.25, 1.5, 1.75, 2
};

enum class TypeRessource{
    metaux, bois, viande
};

struct Ressources {
	uint32_t _metaux, _bois, _viande;
public:
	Ressources():_metaux(0),_bois(0),_viande(0){}
	Ressources(uint32_t metaux, uint32_t bois, uint32_t viande):_metaux(metaux),_bois(bois),_viande(viande){}
	uint32_t Metaux() const {return _metaux;}
	uint32_t Bois() const {return _bois;}
	uint32_t Viande() const {return _viande;}
    Ressources& operator*(float mult) {
        this->_bois*=mult;
        this->_metaux*=mult;
        this->_viande*=mult;
        return *this;
    }
};

struct infoBatimentRessource {
    std::string nom;
    uint32_t vie;
    uint32_t quantite;
    Ressources cout;
};

const std::map<TypeRessource, infoBatimentRessource> dataBatimentRessources {
    {TypeRessource::metaux, infoBatimentRessource{"Mine", 1000, 100, Ressources(100,100,0)}},
    {TypeRessource::bois, infoBatimentRessource{"Scierie", 1000, 100, Ressources(100,100,0)}},
    {TypeRessource::viande, infoBatimentRessource{"Ferme", 1000, 100, Ressources(100,100,0)}}
};
