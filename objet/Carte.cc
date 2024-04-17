#include "Carte.hh"

Carte::Carte() : _largeur(LARGEURCARTE), _longueur(LONGUEURCARTE), _plateau(_largeur * _longueur), _posBase1((_longueur*3/4-1)*_largeur+_largeur/4), _posBase2(_longueur/4*_largeur+_largeur*3/4) {}

Carte::Carte(std::array<Terrain, TAILLECARTE> const & liste_terrains):Carte(){
    auto it = _plateau.begin();
    for (auto const & terrain: liste_terrains){
        it->_terrain = terrain;
        it++;
    }
    std::shared_ptr<Base> base1 = std::make_shared<Base>(_posBase1, TypeJoueur::joueur1);
    std::shared_ptr<Base> base2 = std::make_shared<Base>(_posBase2, TypeJoueur::joueur2);
    _getCase(_longueur*3/4-1, _largeur/4)._element = base1;
    _getCase(_longueur/4, _largeur*3/4)._element = base2;
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
    return i*_largeur+j;
}

bool Carte::estCase(uint16_t i, uint16_t j) const
{
    return i>=0 && i < _longueur && j>=0 && j < _largeur;
}

bool Carte::casesAdjacentes(uint16_t i1, uint16_t j1, uint16_t i2, uint16_t j2) const
{
    if (!estCase(i1, j1) || !estCase(i2, j2)) return false;
    return (i2 >= i1-1 && i2 <= i1+1 && j2 >= j1-1 && j2 <= j1+1);
}

bool Carte::caseBatimentAdjacent(TypeJoueur const &joueur, uint16 i, uint16 j) const
{
    if (!estCase(i, j)) return false;
    return (estCase(i-1, j-1) && getCase(i-1, j-1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i-1, j) && getCase(i-1, j)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i-1, j+1) && getCase(i-1, j+1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i, j-1) && getCase(i, j-1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i, j+1) && getCase(i, j+1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i+1, j-1) && getCase(i+1, j-1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i+1, j) && getCase(i+1, j)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur)
        || (estCase(i+1, j+1) && getCase(i+1, j+1)._element->type() == TypeElement::batiment && getCase(i-1,j-1)._element->joueur() == joueur);
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

bool Carte::poseElement(std::shared_ptr<Element> element, uint16_t i, uint16_t j)
{
    Case& c = _getCase(i, j);
    if (!c._element) return false;
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
            flux << "Ba";
            break;
        case TypeElement::troupe:
            flux << "Tr";
        default:
            break;
        }
    }
    else flux << "--";
    flux << ", ";
    switch (_terrain)
    {
    case Terrain::plaine:
        flux << "Pl";
        break;
    case Terrain::foret:
        flux << "Fo";
        break;
    case Terrain::colline:
        flux << "Co";
        break;
    case Terrain::montagne:
        flux << "Mo";
        break;
    case Terrain::eau:
        flux << "Ea";
        break;
    case Terrain::desert:
        flux << "De";
        break;
    default:
        flux << "Ot";
        break;
    }
    flux << ")";
}

void Carte::afficher(std::ostream &flux) const
{
    for (auto i = 0; i < _largeur ; ++i){
        for (auto j = 0; j < _longueur ; ++j){
            getCase(i, j).afficher(flux);
            flux << " ";
        }
        flux << "\n";
    }
}
