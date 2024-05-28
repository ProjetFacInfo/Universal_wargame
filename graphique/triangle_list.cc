#include <cstdio>
#include <vector>
#include <cassert>

#include "math3D.hh"
#include "triangle_list.hh"
#include "terrain.hh"


TriangleList::Sommet::Sommet()
   : pos(Vecteur3f(0.0f, 0.0f, 0.0f)), tex(Vecteur2f(0.0f, 0.0f))
     , normal(Vecteur3f(0.0f, 0.0f, 0.0f)) {}

void TriangleList::Sommet::initSommet(const Terrain* pTerrain, int x, int z) {
    float y = pTerrain->getHauteur(x, z);

	float echelleMonde = pTerrain->getMondeEchelle();
	pos = Vecteur3f(x * echelleMonde, y, z * echelleMonde);

    float size = (float)pTerrain->getTaille();
    float textureEchelle = pTerrain->getTextureEchellee();
    tex = Vecteur2f(textureEchelle * (float)x / size, textureEchelle * (float)z / size);
}

TriangleList::TriangleList()
   : _largeur(0), _profondeur(0),
     _VAO(0), _VBO(0),
     _IndB(0) { }


TriangleList::~TriangleList() {
    effacer();
}


void TriangleList::effacer() {
    if (_VAO > 0) {
        glDeleteVertexArrays(1, &_VAO);
    }

    if (_VBO > 0) {
        glDeleteBuffers(1, &_VBO);
    }

    if (_IndB > 0) {
        glDeleteBuffers(1, &_IndB);
    }
}


void TriangleList::creerTriangleList(int largeur, int profondeur, const Terrain* pTerrain) {
   _largeur = largeur;
   _profondeur = profondeur;

   creerGlEtat();
   initBuffer(pTerrain);
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void TriangleList::creerGlEtat() {
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glGenBuffers(1, &_IndB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IndB);

    int POS_LOC = 0;
    int TEX_LOC = 1;
	  int NORMAL_LOC = 2;

   	size_t nbre = 0;

    glEnableVertexAttribArray(POS_LOC);
    glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Sommet), (const void*)(nbre * sizeof(float)));
    nbre += 3;

    glEnableVertexAttribArray(TEX_LOC);
    glVertexAttribPointer(TEX_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(Sommet), (const void*)(nbre * sizeof(float)));
    nbre += 2;

    glEnableVertexAttribArray(NORMAL_LOC);
    glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Sommet), (const void*)(nbre * sizeof(float)));
    nbre += 3;
}


void TriangleList::initBuffer(const Terrain* pTerrain) {
    std::vector<Sommet> sommets;
    sommets.resize(_largeur * _profondeur);
    initSommets(pTerrain, sommets);
	  std::vector<uint> inds;
    int NumQuads = (_largeur - 1) * (_profondeur - 1);
    inds.resize(NumQuads * 6);
    initIndBuffer(inds);

    calcNormals(sommets, inds);

    glBufferData(GL_ARRAY_BUFFER, sizeof(sommets[0]) * sommets.size(), &sommets[0], GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds[0]) * inds.size(), &inds[0], GL_STATIC_DRAW);
}




void TriangleList::initSommets(const Terrain* pTerrain, std::vector<Sommet>& sommets) {
    int ind = 0;

    for (int z = 0 ; z < _profondeur ; z++) {
        for (int x = 0 ; x < _largeur ; x++) {
            assert(ind < (int)sommets.size());
			      sommets[ind].initSommet(pTerrain, x, z);
			      ind++;
        }
    }

    assert(ind == (int)sommets.size());
}


void TriangleList::initIndBuffer(std::vector<uint>& inds) {
    int ind = 0;

    for (int z = 0 ; z < _profondeur - 1 ; z++) {
        for (int x = 0 ; x < _largeur - 1 ; x++) {
			uint indBasGauche = z * _largeur + x;
			uint indHautGauche = (z + 1) * _largeur + x;
			uint indHautDroite = (z + 1) * _largeur + x + 1;
			uint indBasDroite = z * _largeur + x + 1;

            assert(ind < (int)inds.size());
            inds[ind++] = indBasGauche;
            assert(ind < (int)inds.size());
            inds[ind++] = indHautGauche;
            assert(ind < (int)inds.size());
            inds[ind++] = (int)indHautDroite;

            assert(ind < (int)inds.size());
            inds[ind++] = indBasGauche;
            assert(ind < (int)inds.size());
            inds[ind++] = (int)indHautDroite;
            assert(ind < (int)inds.size());
            inds[ind++] = indBasDroite;
        }
    }

    assert(ind == (int)inds.size());
}


void TriangleList::calcNormals(std::vector<Sommet>& sommets, std::vector<uint>& inds) {
    uint ind = 0;

    for (uint i = 0 ; i < inds.size() ; i += 3) {
        uint ind0 = inds[i];
        uint ind1 = inds[i + 1];
        uint ind2 = inds[i + 2];
        Vecteur3f v1 = sommets[ind1].pos - sommets[ind0].pos;
        Vecteur3f v2 = sommets[ind2].pos - sommets[ind0].pos;
        Vecteur3f normal = v1.produitVectoriel(v2);
        normal.normaliser();

        sommets[ind0].normal += normal;
        sommets[ind1].normal += normal;
        sommets[ind2].normal += normal;
    }

    for (uint i = 0 ; i < sommets.size() ; i++) {
        sommets[i].normal.normaliser();
    }
}


void TriangleList::render() {
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, (_profondeur - 1) * (_largeur - 1) * 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}
