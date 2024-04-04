#include "Carte.hh"

Carte::Carte():_largeur(LARGEURCARTE),_longueur(LONGUEURCARTE),_plateau(_largeur*_longueur){}

Carte::Carte(std::array<Terrain, TAILLECARTE> const & liste_terrains):Carte(){
    auto it = _plateau.begin();
    for (auto const & terrain: liste_terrains){
        it->_terrain = terrain;
        it++;
    }
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

Case const &Carte::getCase(uint16_t i, uint16_t j) const
{
    return _plateau[i*_largeur+j];
}

void Case::afficher(std::ostream &flux) const
{
    flux << "(";
    if (_element){
        switch (_element->type())
        {
        case Type::batiment:
            flux << "Ba";
            break;
        case Type::troupe:
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
