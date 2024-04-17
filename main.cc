#include <iostream>

#include "objet/Jeu.hh"
#include "instance/carteInstanceTest.hh"

int main(int argc, char *argv[]){

    Jeu jeu(maps["1"]);
    jeu.afficherCarte(std::cout);

    BatimentRessource Fonderie(TypeRessource::metaux, 1, TypeJoueur::joueur1, 0);
    std::cout << Fonderie.nom() << std::endl;

    BatimentTroupe Caserne(1, TypeJoueur::joueur1, 0);
    std::cout << Caserne.nom() << std::endl;

    return 0;
}
