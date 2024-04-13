#pragma once

#include <map>
#include <string>
#include <array>

const uint8_t NB_ERE = 5;

enum class TypeRessource{
    metaux, bois, viande
};

struct Ressource {
	uint32_t _metaux, _bois, _viande;
public:
	Ressource():_metaux(0),_bois(0),_viande(0){}
	Ressource(uint32_t metaux, uint32_t bois, uint32_t viande):_metaux(metaux),_bois(bois),_viande(viande){}
	uint32_t Metaux() const {return _metaux;}
	uint32_t Bois() const {return _bois;}
	uint32_t Viande() const {return _viande;}
};

struct infoBatimentRessource {
    std::string nom;
    std::array<uint16_t, NB_ERE> vie;
    std::array<Ressource, NB_ERE> cout;
};

const std::map<TypeRessource, infoBatimentRessource> dataBatimentRessources {
    {TypeRessource::metaux, infoBatimentRessource{"BatimentMetaux", {1000, 2000, 3000, 4000, 5000}, {Ressource(100,100,0), Ressource(120,120,0), Ressource(140,140,0), Ressource(160,160,0), Ressource(180,180,0)}}},
    {TypeRessource::bois, infoBatimentRessource{"BatimentBois", {1000, 2000, 3000, 4000, 5000}, {Ressource(100,100,0), Ressource(120,120,0), Ressource(140,140,0), Ressource(160,160,0), Ressource(180,180,0)}}},
    {TypeRessource::viande, infoBatimentRessource{"BatimentViande", {1000, 2000, 3000, 4000, 5000}, {Ressource(100,100,0), Ressource(120,120,0), Ressource(140,140,0), Ressource(160,160,0), Ressource(180,180,0)}}}
};
