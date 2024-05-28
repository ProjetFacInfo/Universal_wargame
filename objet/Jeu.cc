#include "Jeu.hh"

int posX1(unsigned int pos, std::shared_ptr<Carte> const & carte){
    return pos%carte->largeur();
}

int posY1(unsigned int pos, std::shared_ptr<Carte> const & carte){
    return pos/carte->largeur();
}

Jeu::Jeu(std::array<Terrain, TAILLECARTE> const & liste_terrains):_carte(std::make_shared<Carte>(liste_terrains)),_j1(_carte, TypeJoueur::joueur1), _j2(_carte, TypeJoueur::joueur2){
    _j1.giveTroupe(TypeTroupe::archer, posX1(_j1.getBase()->pos(), _carte), posY1(_j1.getBase()->pos(), _carte)-1);
    _j1.giveTroupe(TypeTroupe::catapulte, posX1(_j1.getBase()->pos(), _carte)-1, posY1(_j1.getBase()->pos(), _carte)-1);
    _j1.giveTroupe(TypeTroupe::cavalier, posX1(_j1.getBase()->pos(), _carte)+1, posY1(_j1.getBase()->pos(), _carte)-1);
    _j1.giveTroupe(TypeTroupe::infanterie, posX1(_j1.getBase()->pos(), _carte)-2, posY1(_j1.getBase()->pos(), _carte)-1);
    _j1.giveTroupe(TypeTroupe::archer, posX1(_j1.getBase()->pos(), _carte)+2, posY1(_j1.getBase()->pos(), _carte)-1);
    _j1.giveTroupe(TypeTroupe::infanterie, posX1(_j1.getBase()->pos(), _carte), posY1(_j1.getBase()->pos(), _carte)-2);
    _j2.giveTroupe(TypeTroupe::archer, posX1(_j2.getBase()->pos(), _carte), posY1(_j2.getBase()->pos(), _carte)+1);
    _j2.giveTroupe(TypeTroupe::catapulte, posX1(_j2.getBase()->pos(), _carte)-1, posY1(_j2.getBase()->pos(), _carte)+1);
    _j2.giveTroupe(TypeTroupe::cavalier, posX1(_j2.getBase()->pos(), _carte)+1, posY1(_j2.getBase()->pos(), _carte)+1);
    _j2.giveTroupe(TypeTroupe::infanterie, posX1(_j2.getBase()->pos(), _carte)-2, posY1(_j2.getBase()->pos(), _carte)+1);
    _j2.giveTroupe(TypeTroupe::archer, posX1(_j2.getBase()->pos(), _carte)+2, posY1(_j2.getBase()->pos(), _carte)+1);
    _j2.giveTroupe(TypeTroupe::infanterie, posX1(_j2.getBase()->pos(), _carte), posY1(_j2.getBase()->pos(), _carte)+2);
}

void Jeu::lancer()
{
    for (unsigned int i = 0; i < 6 ; i++){
        _j1.joue();
        afficherCarte(std::cout);
        _j2.joue();
        afficherCarte(std::cout);
    }
}

void Jeu::afficherCarte(std::ostream & flux) const
{
    _carte->afficher(flux);
}
