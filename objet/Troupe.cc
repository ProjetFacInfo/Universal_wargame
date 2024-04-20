#include "Troupe.hh"
#include <iostream>
#include <cmath>

Troupe::Troupe(uint32 pos, TypeJoueur const & joueur, TypeTroupe const & t, uint8 ere)
    :Element(dataTroupes.at(t).vie * MULT_ERE[ere], pos, joueur), _typeTroupe(t){}

TypeElement Troupe::type() const
{
    return TypeElement::troupe;
}

std::string const & Troupe::nom() const {
    return dataTroupes.at(_typeTroupe).nom;
}

Ressources Troupe::cout(uint8 ere) const {
    return dataTroupes.at(_typeTroupe).cout * MULT_ERE[ere];
}

void Troupe::evolue(uint8 ere)
{
}

uint32 Troupe::attaque() const {
    return dataTroupes.at(_typeTroupe).attaque;
}

uint32 Troupe::portee_min() const {
    return dataTroupes.at(_typeTroupe).portee.min;
}

uint32 Troupe::portee_max() const {
    return dataTroupes.at(_typeTroupe).portee.max;
}

uint32 Troupe::defense() const {
    return dataTroupes.at(_typeTroupe).defense;
}

uint32 Troupe::pas() const {
    return dataTroupes.at(_typeTroupe).pas;
}

uint32 Troupe::accesTerrain(Terrain const & t) const {
    return dataTroupes.at(_typeTroupe).accesTerrain.at(t);
}

void Troupe::deplacer(uint32 pos) {
    _pos = pos;
}

std::vector<uint32> Troupe::list_pos_attaquable() const {
    int min(portee_min());
    int max(portee_max());
    int capacite(0);

    for (int i(min); i <= max; i++) {
        capacite += i * 8;
    }

    std::vector<uint32> l;
    l.reserve(capacite);

    int ligne(pos() / LARGEURCARTE);
    int colonne(pos() % LONGUEURCARTE);


    for (int i(1); i <= max; i++) {
        // Nord
        if (position_valable(ligne, colonne, (ligne - i), colonne, min)) {
            l.push_back((ligne - i) * LARGEURCARTE + colonne);
        }

        // Sud
        if (position_valable(ligne, colonne, (ligne + i), colonne, min)) {
            l.push_back((ligne + i) * LONGUEURCARTE + colonne);
        }

        for (int j(1); j <= max; j++) {

            // Nord-Ouest
            if (position_valable(ligne, colonne, (ligne - i), (colonne -j), min)) {
                l.push_back((ligne - i) * LONGUEURCARTE + colonne - j);
            }

            // Nord-EST
            if (position_valable(ligne, colonne, (ligne - i), (colonne + j), min)) {
                l.push_back((ligne - i) * LONGUEURCARTE + colonne + j);
            }

            // Sud-Ouest
            if (position_valable(ligne, colonne, (ligne + i), (colonne -j), min)) {
                l.push_back((ligne + i) * LONGUEURCARTE + colonne - j);
            }

            // Sud-EST
            if (position_valable(ligne, colonne, (ligne + i), (colonne + j), min)) {
                l.push_back((ligne + i) * LONGUEURCARTE + colonne + j);
            }

        }

        // Ouest
        if (position_valable(ligne, colonne, ligne, (colonne - i), min)) {
            l.push_back(ligne * LARGEURCARTE + colonne - i);
        }

        // Est
        if (position_valable(ligne, colonne, ligne, (colonne + i), min)) {
            l.push_back(ligne * LARGEURCARTE + colonne + i);
        }
    }

    return l;
}

void Troupe::attaquer(std::shared_ptr<Element> T) const {
    T->setVie(T->vie() + T->defense() - this->attaque());
}

bool Troupe::position_valable(int x1, int y1, int x2, int y2, int dist) const {
    return (x2 >= 0) and (x2 < 16) and (y2 >= 0) and (y2 < 16)
            and (abs(x2 - x1) >= dist or abs(y2 - y1) >= dist);
}

