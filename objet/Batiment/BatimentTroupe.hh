#pragma once

#include "../Batiment.hh"
#include <memory>

class Troupe;

class BatimentTroupe : public Batiment {
public:
    BatimentTroupe(uint32 pos, TypeJoueur const & joueur, uint8 ere);
    std::string const & nom() const override;
	Ressources cout(uint8 ere) const override;
    void evolue(uint8 ere) override;
    
    /*
    std::shared_ptr<Element> creer_infanterie(uint32 pos, uint8 ere);
    std::shared_ptr<Element> creer_archer(uint32 pos, uint8 ere);
    std::shared_ptr<Element> creer_cavalier(uint32 pos, uint8 ere);
    std::shared_ptr<Element> creer_catapulte(uint32 pos, uint8 ere);
    */
};
