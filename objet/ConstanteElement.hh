#pragma once

#include "../type.hh"

#include <map>
#include <string>
#include <array>

const uint8 NB_ERE = 5;

const std::array<float, NB_ERE> MULT_ERE {
    1, 1.25, 1.5, 1.75, 2
};

enum class TypeRessource{
    metaux, bois, viande, troupe
};

enum class TypeTroupe{
    infanterie, archer, cavalier
};

struct Ressources {
	uint32 _metaux, _bois, _viande;
public:
	Ressources():_metaux(0),_bois(0),_viande(0){}
	Ressources(uint32 metaux, uint32 bois, uint32 viande):_metaux(metaux),_bois(bois),_viande(viande){}
	uint32 Metaux() const {return _metaux;}
	uint32 Bois() const {return _bois;}
	uint32 Viande() const {return _viande;}
    bool operator<=(Ressources const & r){
        return this->_metaux <= r._metaux && this->_bois <= r._bois && this->_viande <= r._viande;
    }
    bool operator>=(Ressources const & r){
        return this->_metaux >= r._metaux && this->_bois >= r._bois && this->_viande >= r._viande;
    }
    void operator+=(Ressources const & r){
        this->_metaux+=r._metaux;
        this->_bois+=r._bois;
        this->_viande+=r._viande;
    }
    void operator-=(Ressources const & r){
        this->_metaux-=r._metaux;
        this->_bois-=r._bois;
        this->_viande-=r._viande;
    }
    Ressources operator*(float mult) const{
        Ressources ret;
        ret._metaux = this->_metaux * mult;
        ret._bois = this->_bois * mult;
        ret._viande = this->_viande * mult;
        return ret;
    }
};

struct infoBatimentRessource {
    std::string nom;
    uint32 vie;
    uint32 quantite;
    Ressources cout;
};

const std::map<TypeRessource, infoBatimentRessource> dataBatimentRessources {
    {TypeRessource::metaux, infoBatimentRessource{"Mine", 1000, 100, Ressources(100,100,0)}},
    {TypeRessource::bois, infoBatimentRessource{"Scierie", 1000, 100, Ressources(100,100,0)}},
    {TypeRessource::viande, infoBatimentRessource{"Ferme", 1000, 100, Ressources(100,100,0)}},
    {TypeRessource::troupe, infoBatimentRessource{"Caserne", 1500, 1, Ressources(200,200,0)}}
};


struct infoTroupeRessource {
    std::string nom;
    uint32 vie;
    Ressources cout;
};

const std::map<TypeTroupe, infoTroupeRessource> dataTroupeRessources {
    {TypeTroupe::infanterie, infoTroupeRessource{"infanterie", 80, Ressources(20, 0, 50)}},
    {TypeTroupe::archer, infoTroupeRessource{"archer", 60, Ressources(20, 20, 50)}},
    {TypeTroupe::cavalier, infoTroupeRessource{"cavalier", 120, Ressources(50, 10, 100)}}
};
