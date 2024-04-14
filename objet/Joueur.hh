#pragma once

#include <queue>

#include "Carte.hh"
#include "Batiment/Base.hh"
#include "Batiment/BatimentRessource.hh"
#include "Troupe.hh"

class Joueur{
private:
    std::shared_ptr<Carte> _carte;
    Ressources _ressources;
    std::queue<BatimentRessource> _batiments;
    std::shared_ptr<Element> _base;
    uint8_t _ere;
public:
    Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur);
    std::shared_ptr<Carte> const & getCarte() const;
    Ressources const & getRessources() const;
    std::queue<BatimentRessource> const & getBatiments() const;
    std::queue<Troupe> const & getTroupes() const;
    std::shared_ptr<Element> const & getBase() const;

    bool aPerdu() const;

    bool acheterBatiment(TypeRessource const & ressource, uint16_t i, uint16_t j);
    bool acheterTroupe(TypeTroupe const & troupe, uint16_t i, uint16_t j);
};