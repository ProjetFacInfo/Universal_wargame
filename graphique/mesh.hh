#pragma once

#include <map>
#include <vector>

#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "util.hh"
#include "math3D.hh"

#include "texture.hh"
#include "monde_transformation.hh"
#include "materiau.hh"


class Mesh {
    protected:
        struct MeshInfo {
            MeshInfo();
            uint nbreInd;
            uint baseSommet;
            uint baseInd;
            uint materiauInd;
        };

        enum BUFFER_TYPE {
            INDEX_BUFFER = 0,       // Tampon d'index
            SOMMET_BUFFER = 1,      // Tampon de sommet
            MVP_MAT_BUFFER = 2,     // Monde Vue Projection matrice
            MONDE_MAT_BUFFER = 3,   // Monde matrice
            NBRE_BUFFERS = 4        // Nombre totale de buffers
        };

        MondeTrans _mondeTrans;
        const aiScene * _pScene;
        Matrice4f _globalInverseTransform;
        std::vector<MeshInfo> _meshes;
        std::vector<uint> _indices;
        GLuint _VAO;                        // Vertex Array Objects
        GLuint _buffers[NBRE_BUFFERS];

    private:
        struct Sommet {
            Vecteur3f position;
            Vecteur2f textureCoord;
            Vecteur3f normal;
        };

        std::vector<Materiau> _materiaux;
        std::vector<Sommet> _sommets;
        Assimp::Importer _importer;


    public:
        Mesh();
        ~Mesh();

        float getScale() const;
        Vecteur3f getPosition() const;
        void setScale(float Scale);
        void setPosition(float x, float y, float z);
        void setPosition(const Vecteur3f & pos);
        void setRotation(float x, float y, float z);
        Matrice4f getMondeMatrice() const;
        MondeTrans  & getMondeTransform();
        const Materiau & getMateriau();
        PBRMateriau & getPBRMateriau();
        void getSommetBase(uint renderInd, uint primitifInd, Vecteur3f & sommet);
        bool chargerMesh(const std::string & fic);
        void render();
        void render(uint renderInd, uint primitifInd);
        void render(uint nbreInstance, const Matrice4f * matMVP, const Matrice4f * matMonde);

    protected:
        void effacer();
        virtual void reserve(uint nbreSommet, uint nbreInd);
        virtual void initMesh(uint meshInd, const aiMesh * paiMesh);
        virtual void initBuffers();

    private:
        void initMeshes(const aiScene * pScene);
        bool initScene(const aiScene * pScene, const std::string & fic);
        bool initMateriau(const aiScene * pScene, const std::string & fic);
        void chargerTextureDiffuse(const std::string & dir, const aiMaterial * pMaterial, int index);
        void chargerTextureSpeculair(const std::string & dir, const aiMaterial * pMaterial, int index);
        void chargerCouleur(const aiMaterial * pMaterial, int index);
        void nbreSommetIndice(const aiScene * pScene, uint & nbreSommet, uint & nbreInd);

};
