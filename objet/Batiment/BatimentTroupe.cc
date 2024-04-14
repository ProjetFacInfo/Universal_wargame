#include "BatimentTroupe.hh"

BatimentTroupe::BatimentTroupe(uint32 pos, TypeJoueur const & joueur)
    :Batiment(
            dataBatimentTroupes.at(TypeRessource::troupe).vie * MULT_ERE[(joueur == TypeJoueur::joueur1) ? ere_joueur1 : ere_joueur2], pos, joueur),
            _ressource(r){}

std::string const &BatimentTroupe::nom() const {
    return dataBatimentTroupes.at(TypeRessource::troupe).nom;
}

Ressources const &BatimentTroupe::cout() const {
    Troupes cout = dataBatimentTroupes.at(TypeRessource::troupe).cout;
    return cout * MULT_ERE[ere()];
}

TypeRessource const &BatimentTroupe::ressourceProduite() const
{
    return TypeRessource::troupe;
}

uint32 BatimentTroupe::quantiteProduite() const
{
    return dataBatimentTroupes.at(TypeRessource::troupe).quantite * MULT_ERE[ere()];
}

static BatimentTroupe::std::shared_ptr<Element> creer_infanterie(uint32 pos, TypeJoueur const & joueur) {
    uint8 ere_joueur = ere();
    uint16 vie = dataTroupeRessources[TypeTroupe::infanterie].vie[ere_joueur];
    std::shared_ptr<Troupe> infanterie(vie, pos, joueur, TypeTroupe::infanterie);

    infanterie->add_component(component_to_signature_map["Attaque_component"],
            std::make_unique<Attaque_component>(20 + (ere_joueur * 10), 1));
    infanterie->add_component(component_to_signature_map["Defense_component"],
            std::make_unique<Defense_component>(20 + (ere_joueur * 10)));
    infanterie->add_component(component_to_signature_map["Mov_component"],
            std::make_unique<Mov_component>(4));
    // Terrain acces 0000'0011'1111'0101
    infanterie->add_component(component_to_signature_map["Terrain_component"],
            std::make_unique<Terrain_component>(1013));
    return infanterie;
}

static BatimentTroupe::std::shared_ptr<Element> creer_archer(uint32 pos, TypeJoueur const & joueur) {
    uint8 ere_joueur = ere();
    uint16 vie = dataTroupeRessources[TypeTroupe::archer].vie[ere_joueur];
    std::shared_ptr<Troupe> archer(vie, pos, joueur, TypeTroupe::archer);

    std::Attaque_component att(20 + (ere_joueur1 * 10), 1);
    Defense_component att(20 + (ere_joueur1 * 10), 1);
    Attaque_component att(20 + (ere_joueur1 * 10), 1);
    archer->add_component(component_to_signature_map["Attaque_component"],
            std::make_unique<Attaque_component>(20 + (ere_joueur * 10), 2));
    archer->add_component(component_to_signature_map["Defense_component"],
            std::make_unique<Defense_component>(10 + (ere_joueur * 10)));
    archer->add_component(component_to_signature_map["Mov_component"],
            std::make_unique<Mov_component>(4));
    // Terrain acces 0000'0011'1111'0101
    archer->add_component(component_to_signature_map["Terrain_component"],
            std::make_unique<Terrain_component>(1013));
    return archer;

}

static BatimentTroupe::std::shared_ptr<Element> creer_cavalier(uint32 pos, TypeJoueur const & joueur) {
    uint8 ere_joueur = ere();
    uint16 vie = dataTroupeRessources[TypeTroupe::infanterie].vie[ere_joueur];
    std::shared_ptr<Troupe> infanterie(vie, pos, joueur, TypeTroupe::cavalier);

    infanterie->add_component(component_to_signature_map["Attaque_component"],
            std::make_unique<Attaque_component>(20 + (ere_joueur * 10), 1));
    infanterie->add_component(component_to_signature_map["Defense_component"],
            std::make_unique<Defense_component>(10 + (ere_joueur * 10)));
    infanterie->add_component(component_to_signature_map["Mov_component"],
            std::make_unique<Mov_component>(4));
    // Terrain acces 0000'0001'1111'0101
    infanterie->add_component(component_to_signature_map["Terrain_component"],
            std::make_unique<Terrain_component>(501));
    return infanterie;
}
