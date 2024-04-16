#pragma once

#include "../Batiment.hh"
#include <memory>


class BatimentTroupe : public Batiment {
public:
    BatimentTroupe(uint32 pos, TypeJoueur const & joueur);
    std::string const & nom() const override;
	Ressources const & cout() const override;

    // std::shared_ptr<Element> creer_infanterie(uint32 pos);
    // std::shared_ptr<Element> creer_archer(uint32 pos);
    // std::shared_ptr<Element> creer_cavalier(uint32 pos);
};
