#pragma once

#include <queue>

#include "ConstanteElement.hh"
#include "Carte.hh"
#include "Batiment/Base.hh"
#include "Batiment/BatimentRessource.hh"
#include "Batiment/BatimentTroupe.hh"
#include "Troupe.hh"

class Joueur{
private:
    std::shared_ptr<Carte> _carte;
    Ressources _ressources;
    std::queue<std::shared_ptr<BatimentRessource>> _batimentsRessources;
    std::queue<std::shared_ptr<BatimentTroupe>> _batimentsTroupes;
    std::queue<std::shared_ptr<Troupe>> _troupes;
    std::shared_ptr<Element> _base;
    uint8_t _ere;
    TypeJoueur _type;
public:
    Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur);
    std::shared_ptr<Carte> const & getCarte() const;
    Ressources const & getRessources() const;
    std::queue<std::shared_ptr<BatimentRessource>> const & getBatimentsRessources() const;
    std::queue<std::shared_ptr<BatimentTroupe>> const & getBatimentsTroupes() const;
    std::queue<std::shared_ptr<Troupe>> const & getTroupes() const;
    std::shared_ptr<Element> const & getBase() const;

    bool aPerdu() const;

    bool acheterBatimentRessource(TypeRessource const & ressource, uint16_t i, uint16_t j);
    bool acheterBatimentTroupe(uint16_t i, uint16_t j);
    bool acheterTroupe(TypeTroupe const & troupe, uint16_t i, uint16_t j);
};