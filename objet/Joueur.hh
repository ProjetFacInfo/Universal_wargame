#pragma once

#include <list>
#include <unordered_map>
#include <unistd.h>

#include "ConstanteElement.hh"
#include "Carte.hh"
#include "Batiment/Base.hh"
#include "Batiment/BatimentRessource.hh"
#include "Batiment/BatimentTroupe.hh"
#include "Troupe.hh"
#include "MAPF/MAPF.hh"

class Joueur{
protected:
    std::shared_ptr<Carte> _carte;
    Ressources _ressources;
    std::list<std::shared_ptr<BatimentRessource>> _batimentsRessources;
    std::list<std::shared_ptr<BatimentTroupe>> _batimentsTroupes;
    std::list<std::shared_ptr<Troupe>> _troupes;
    std::shared_ptr<Element> _base;
    uint8_t _ere;
    TypeJoueur _joueur;
public:
    Joueur(std::shared_ptr<Carte> const & carte, TypeJoueur const & joueur);
    std::shared_ptr<Carte> const & getCarte() const;
    Ressources const & getRessources() const;
    std::list<std::shared_ptr<BatimentRessource>> const & getBatimentsRessources() const;
    std::list<std::shared_ptr<BatimentTroupe>> const & getBatimentsTroupes() const;
    std::list<std::shared_ptr<Troupe>> const & getTroupes() const;
    std::shared_ptr<Element> const & getBase() const;

    bool aPerdu() const;

    bool acheterBatimentRessource(TypeRessource const & ressource, uint16_t i, uint16_t j);
    bool acheterBatimentTroupe(uint16_t i, uint16_t j);
    bool acheterTroupe(TypeTroupe const & troupe, uint16_t i, uint16_t j);

    bool giveTroupe(TypeTroupe const & troupe, uint16_t i, uint16_t j); // uniquement pour faire des tests

    std::unordered_map<std::shared_ptr<Troupe>, std::list<unsigned int>> trouveChemins(std::list<std::shared_ptr<Troupe>> agents, std::list<unsigned int> targets);

    // Rechercher une cible parmi une liste de position attaquable
    std::shared_ptr<Element> cible(std::shared_ptr<Troupe> t) const;

    // Parcourir la liste des troupes pour combattre l'ennemie a portée de l'arme
    void combat();

    void passerEreSuivante();
};
