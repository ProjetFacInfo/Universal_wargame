#include <iostream>
#include <algorithm>

#include "objet/Jeu.hh"
#include "instance/carteInstanceTest.hh"
#include "objet/Troupe.hh"

int main(int argc, char *argv[]){

    Jeu jeu(maps["2"]);
    jeu.afficherCarte(std::cout);

    jeu.lancer();
    printf("ok");
    // jeu.getCarte()->creerCarteHauteur();

    return 0;
}

