#include <iostream>

#include "objet/Jeu.hh"
#include "instance/carteInstanceTest.hh"

int main(int argc, char *argv[]){

    Jeu jeu(maps["1"]);
    jeu.afficherCarte(std::cout);

    return 0;
}
