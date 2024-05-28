#pragma once
#include <GL/glew.h>
#include <vector>

#include "math3D.hh"

class Terrain;

class TriangleList {
 private:

    struct Sommet {
        Vecteur3f pos;
        Vecteur2f tex;
        Vecteur3f normal;

        Sommet();
        void initSommet(const Terrain* pTerrain, int x, int z);
    };

    int _largeur;
    int _profondeur;
    GLuint _VAO;
    GLuint _VBO;
    GLuint _IndB;

 public:
    TriangleList();
    ~TriangleList();

    void creerTriangleList(int largeur, int profondeur, const Terrain* pTerrain);
    void effacer();
    void render();
    void creerGlEtat();
   	void initBuffer(const Terrain* pTerrain);
    void initSommets(const Terrain* pTerrain, std::vector<Sommet>& sommets);
    void initIndBuffer(std::vector<uint>& inds);
    void calcNormals(std::vector<Sommet>& sommets, std::vector<uint>& inds);

};
