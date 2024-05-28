#pragma once
#include <GL/glew.h>
#include <vector>

#include "math3D.hh"

class Terrain;

class TriangleList {
 public:
    TriangleList();

    ~TriangleList();

    void CreateTriangleList(int Width, int Depth, const Terrain* pTerrain);

    void effacer();

    void Render();

 private:

    struct Vertex {
        Vecteur3f Pos;
        Vecteur2f Tex;
        Vecteur3f Normal = Vecteur3f(0.0f, 0.0f, 0.0f);

        void InitVertex(const Terrain* pTerrain, int x, int z);
    };

    void CreateGLState();

	void PopulateBuffers(const Terrain* pTerrain);
    void InitVertices(const Terrain* pTerrain, std::vector<Vertex>& Vertices);
    void InitIndices(std::vector<uint>& Indices);
    void CalcNormals(std::vector<Vertex>& Vertices, std::vector<uint>& Indices);

    int m_width = 0;
    int m_depth = 0;
    GLuint m_vao = 0;
    GLuint m_vb = 0;
    GLuint m_ib = 0;

};

