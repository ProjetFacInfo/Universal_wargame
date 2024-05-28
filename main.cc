#include <iostream>
#include <algorithm>

#include "objet/Jeu.hh"
#include "instance/carteInstanceTest.hh"
#include "objet/Troupe.hh"

void test_list_position();


int main(int argc, char *argv[]){

    Jeu jeu(maps["1"]);
    jeu.afficherCarte(std::cout);

    jeu.lancer();

    return 0;
}

void test_list_position() {
    // portée attaque 1-1
    // Coin Nord-Ouest : OK
    // Troupe T(0, TypeJoueur::joueur1, TypeTroupe::cavalier, 1);
    // Coin Sud-Ouest : OK
    // Troupe T(240, TypeJoueur::joueur1, TypeTroupe::cavalier, 1);
    // Millieur : OK
    // Troupe T(70, TypeJoueur::joueur1, TypeTroupe::cavalier, 1);
    // Coin Nord-Est : OK
    // Troupe T(15, TypeJoueur::joueur1, TypeTroupe::cavalier, 1);
    // Coin Sud-Est : OK
    // Troupe T(255, TypeJoueur::joueur1, TypeTroupe::cavalier, 1);

    // portée attaque 1-2
    // Coin Nord-Ouest : OK
    // Troupe T(0, TypeJoueur::joueur1, TypeTroupe::archer, 1);
    // Coin Sud-Ouest : OK
    // Troupe T(240, TypeJoueur::joueur1, TypeTroupe::archer, 1);
    // Millieur : OK
    // Troupe T(70, TypeJoueur::joueur1, TypeTroupe::archer, 1);
    // Coin Nord-Est : OK
    // Troupe T(15, TypeJoueur::joueur1, TypeTroupe::archer, 1);
    // Coin Sud-Est : OK
    // Troupe T(255, TypeJoueur::joueur1, TypeTroupe::archer, 1);


    // portée attaque 2-4
    // Coin Nord-Ouest : OK
    // Troupe T(0, TypeJoueur::joueur1, TypeTroupe::catapulte, 1);
    // Coin Sud-Ouest : OK
    // Troupe T(240, TypeJoueur::joueur1, TypeTroupe::catapulte, 1);
    // Millieur : OK
    Troupe T(70, TypeJoueur::joueur1, TypeTroupe::catapulte, 1);
    // Coin Nord-Est : OK
    // Troupe T(15, TypeJoueur::joueur1, TypeTroupe::catapulte, 1);
    // Coin Sud-Est : OK
    // Troupe T(255, TypeJoueur::joueur1, TypeTroupe::catapulte, 1);

    auto cibles = T.list_pos_attaquable();
    std::sort(cibles.begin(), cibles.end());
    std::cout << "nb de cibles : " << cibles.size() << std::endl;
    for (auto const & c : cibles) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
