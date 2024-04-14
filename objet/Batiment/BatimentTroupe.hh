#pragma once

#include "../Batiment.hh"

class BatimentTroupe : public Batiment {
public:
    BatimentTroupe(uint32 pos, TypeJoueur const & joueur);
    std::string const & nom() const override;
	  Ressources const & cout() const override;
    TypeRessource const & ressourceProduite() const;
    uint32 quantiteProduite() const;

    static std::shared_ptr<Element> creer_infanterie(uint32 pos, TypeJoueur const & joueur);
    static std::shared_ptr<Element> creer_archer(uint32 pos, TypeJoueur const & joueur);
    static std::shared_ptr<Element> creer_cavalier(uint32 pos, TypeJoueur const & joueur);
}
