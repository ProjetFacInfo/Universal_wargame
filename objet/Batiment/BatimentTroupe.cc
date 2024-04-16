#include "BatimentTroupe.hh"
#include "../Troupe.hh"

BatimentTroupe::BatimentTroupe(uint32 pos, TypeJoueur const & joueur)
    :Batiment( dataBatimentRessources.at(TypeRessource::troupe).vie * MULT_ERE[(joueur == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2], pos, joueur) {}

std::string const & BatimentTroupe::nom() const {
    return dataBatimentRessources.at(TypeRessource::troupe).nom;
}

Ressources BatimentTroupe::cout() const {
    return dataBatimentRessources.at(TypeRessource::troupe).cout * MULT_ERE[ere()];
}

//
// std::shared_ptr<Element> BatimentTroupe::creer_infanterie(uint32 pos) {
//     TypeJoueur joueur = joueur();
//     uint8 ere_joueur = ere();
//     uint16 vie = dataTroupes.at(TypeTroupe::infanterie).vie * MULT_ERE[ere_joueur];
//     std::shared_ptr<Troupe> infanterie(vie, pos, joueur, TypeTroupe::infanterie);
//
//     return infanterie;
// }
//
// std::shared_ptr<Element> BatimentTroupe::creer_archer(uint32 pos) {
//     TypeJoueur joueur = joueur();
//     uint8 ere_joueur = ere();
//     uint16 vie = dataTroupes.at(TypeTroupe::archer).vie * MULT_ERE[ere_joueur];
//     std::shared_ptr<Troupe> archer(vie, pos, joueur, TypeTroupe::archer);
//
//     return archer;
//
// }
//
// std::shared_ptr<Element> BatimentTroupe::creer_cavalier(uint32 pos) {
//     TypeJoueur joueur = joueur();
//     uint8 ere_joueur = ere();
//     uint16 vie = dataTroupes.at(TypeTroupe::archer).vie * MULT_ERE[ere_joueur];
//     std::shared_ptr<Troupe> infanterie(vie, pos, joueur, TypeTroupe::cavalier);
//
//     return infanterie;
// }
