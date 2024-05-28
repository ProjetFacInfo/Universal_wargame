#include "Carte.hh"
#include <fstream>

Carte::Carte() : _largeur(LARGEURCARTE), _longueur(LONGUEURCARTE), _plateau(_largeur * _longueur), _posBase1(_largeur*3/4*_largeur+_longueur/4), _posBase2(_largeur/4*_largeur+_longueur*3/4-1) {}

Carte::Carte(std::array<Terrain, TAILLECARTE> const & liste_terrains):Carte(){
    auto it = _plateau.begin();
    for (auto const & terrain: liste_terrains){
        it->_terrain = terrain;
        it++;
    }
    std::shared_ptr<Base> base1 = std::make_shared<Base>(_posBase1, TypeJoueur::joueur1);
    std::shared_ptr<Base> base2 = std::make_shared<Base>(_posBase2, TypeJoueur::joueur2);
    _getCase(_longueur/4, _largeur*3/4)._element = base1;
    _getCase(_longueur*3/4-1, _largeur/4)._element = base2;
}

uint16_t Carte::largeur() const
{
    return _largeur;
}

uint16_t Carte::longueur() const
{
    return _longueur;
}

uint16_t Carte::taille() const
{
    return _plateau.size();
}

uint16_t Carte::pos(uint16_t i, uint16_t j) const
{
    return j*_largeur+i;
}

bool Carte::estCase(uint16_t i, uint16_t j) const
{
    return i < _longueur && j < _largeur;
}

bool Carte::casesAdjacentes(uint16_t i1, uint16_t j1, uint16_t i2, uint16_t j2) const
{
    if (!estCase(i1, j1) || !estCase(i2, j2)) return false;
    return (i2 >= i1-1 && i2 <= i1+1 && j2 >= j1-1 && j2 <= j1+1);
}

bool Carte::casesAdjacentes(uint16_t pos1, uint16_t pos2) const
{
    return casesAdjacentes(pos1%largeur(), pos1/largeur(), pos2%largeur(), pos2/largeur());
}

bool Carte::caseBatimentAdjacent(TypeJoueur const &joueur, uint16 i, uint16 j) const
{
    if (!estCase(i, j)) return false;
    return (estCase(i-1, j-1) && getCase(i-1, j-1)._element && getCase(i-1, j-1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i-1, j) && getCase(i-1, j)._element && getCase(i-1, j)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i-1, j+1) && getCase(i-1, j+1)._element && getCase(i-1, j+1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i, j-1) && getCase(i, j-1)._element && getCase(i, j-1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i, j+1) && getCase(i, j+1)._element && getCase(i, j+1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i+1, j-1) && getCase(i+1, j-1)._element && getCase(i+1, j-1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i+1, j) && getCase(i+1, j)._element && getCase(i+1, j)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i+1, j+1) && getCase(i+1, j+1)._element && getCase(i+1, j+1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur);
}

Case &Carte::_getCase(uint16_t i, uint16_t j)
{
    return _plateau[pos(i,j)];
}

Case const &Carte::getCase(uint16_t i, uint16_t j) const
{
    return _plateau[pos(i,j)];
}

Case const &Carte::getCase(uint16_t i) const
{
    return _plateau[i];
}

uint16_t Carte::getPosBase1() const
{
    return _posBase1;
}

uint16_t Carte::getPosBase2() const
{
    return _posBase2;
}

bool Carte::deplacer(std::shared_ptr<Troupe> &troupe, uint16 position)
{
    if (getCase(position)._element || !casesAdjacentes(troupe->pos(),position)) return false;
    this->operator[](position)._element = troupe;
    this->operator[](troupe->pos())._element = nullptr;
    troupe->deplacer(position);
    return true;
}

bool Carte::poseElement(std::shared_ptr<Element> element, uint16_t i, uint16_t j)
{
    Case& c = _getCase(i, j);
    if (c._element) return false;
    else c._element = element;
    return true;
}

void Case::afficher(std::ostream &flux) const
{
    flux << "(";
    if (_element){
        switch (_element->type())
        {
        case TypeElement::batiment:
            flux << "Bas" << ((_element->joueur()==TypeJoueur::joueur1) ? 1 : 2);
            break;
        case TypeElement::troupe:
            {
                Troupe * troupe = dynamic_cast<Troupe *>(_element.get());
                switch (troupe->getType())
                {
                case TypeTroupe::archer:
                    flux << "Arc";
                    break;
                case TypeTroupe::infanterie:
                    flux << "Inf";
                    break;
                case TypeTroupe::catapulte:
                    flux << "Cat";
                    break;
                case TypeTroupe::cavalier:
                    flux << "Cav";
                    break;
                default:
                    break;
                }
                flux << ((_element->joueur()==TypeJoueur::joueur1) ? 1 : 2);
            }
            break;
        default:
            break;
        }
    }
    else flux << "----";
    flux << ",";
    switch (_terrain)
    {
    case Terrain::plaine:
        flux << "Pla";
        break;
    case Terrain::foret:
        flux << "For";
        break;
    case Terrain::colline:
        flux << "Col";
        break;
    case Terrain::montagne:
        flux << "Mon";
        break;
    case Terrain::eau:
        flux << "Eau";
        break;
    case Terrain::desert:
        flux << "Des";
        break;
    case Terrain::mer:
        flux << "Mer";
        break;
    default:
        flux << "Oth";
        break;
    }
    flux << ")";
}

void Carte::afficher(std::ostream &flux) const
{
    for (auto i = 0; i < _largeur ; ++i){
        for (auto j = 0; j < _longueur ; ++j){
            getCase(j, i).afficher(flux);
            flux << " ";
        }
        flux << "\n";
    }
}

Case & Carte::at(uint16 pos) {
    return _plateau.at(pos);
}

const Case & Carte::at(uint16 pos) const {
    return _plateau.at(pos);
}

Case & Carte::operator[](uint16 pos) {
    return _plateau[pos];
}

const Case & Carte::operator[](uint16 pos) const {
    return _plateau[pos];
}

std::vector<float> Carte::getPlageHauteur(float min, float max) const {
    srand(time(NULL));
    std::vector<float> tmp(_largeur * _longueur);

    for (uint16_t i=0; i < _largeur * _longueur; i++) {
            tmp[i] = (rand() / (float)RAND_MAX) * (max - min) + min;
    }
    return tmp;
}


void Carte::creerCarteHauteur() const {
    float merMin = -3.0f;
    float merMax = -2.0f;
    float eauMin = -2.0f;
    float eauMax = -1.0f;
    float desertMin = -1.0f;
    float desertMax = 0.0f;
    float plaineMin = 0.0f;
    float plaineMax = 5.0f;
    float foretMin = 0.0f;
    float foretMax = 5.0f;
    float collineMin = 1.0f;
    float collineMax = 20.0f;
    float montagneMin = 20.0f;
    float montagneMax = 200.0f;

    std::ofstream flux;
    flux.open("../instance/carte_hauteur");
    std::vector<std::vector<float>> acc(_largeur * _longueur);
    std::vector<float> tmp;
    int cpt = 0;

    for (const auto & c : _plateau) {
        switch (c._terrain) {
            case Terrain::mer:
            tmp = getPlageHauteur(merMin, merMax);
            break;

            case Terrain::eau:
            tmp = getPlageHauteur(eauMin, eauMax);
            break;

            case Terrain::desert:
            tmp = getPlageHauteur(desertMin, desertMax);
            break;

            case Terrain::plaine:
            tmp = getPlageHauteur(plaineMin, plaineMax);
            break;

            case Terrain::foret:
            tmp = getPlageHauteur(foretMin, foretMax);
            break;

            case Terrain::colline:
            tmp = getPlageHauteur(collineMin, collineMax);
            break;

            case Terrain::montagne:
            tmp = getPlageHauteur(montagneMin, collineMax);
            break;
        }
        acc[cpt] = tmp;
        ++cpt;
    }

    for (int l=0; l < _longueur; ++l) {
        for (int k=0; k < _largeur; ++k) {
            for (int j= l*_longueur; j < l*_longueur+_longueur; ++j) {
                for (int i= k*_longueur; i < k*_largeur+_largeur; ++i) {
                   flux << acc[j][i] << " ";
                }
            }
            flux << "\n";
        }
    }


    flux.close();
}
