// Structures assimp
//
// aiScene{aiMesh[]}
// 	-> aiMesh[]{aiBone[], aiVector3D vertices[]}
// 			-> aiBone[]{mName, mNumWeights, mOffsetMatrix, mWeights}
// 					-> aiVertexWeight[]{mVertexId, mWeight}
//
// mNumWeights : Le nombre de sommets affecté par le squelette
// mWeights : les sommets affecté par le squelette
// const aiVertexWeight& vw = pBone->mWeights[i];

#pragma once

#include "mesh.hh"

class SqueletteMesh : public Mesh {
    public:
         static const uint NBRE_OS_PAR_SOMMET = 4;

    private:
        struct OsSommetInfo {
            uint osID[NBRE_OS_PAR_SOMMET];
            float poids[NBRE_OS_PAR_SOMMET];
            int ind = 0;

            OsSommetInfo();
            void ajoutOsInfo(uint osId, float poids);
        };

        struct SqueletteSommet {
            Vecteur3f position;
            Vecteur2f textureCoord;
            Vecteur3f normal;
            OsSommetInfo   os;
        };

        struct LocalTransform {
            aiVector3D   scaling;
            aiQuaternion rotation;
            aiVector3D   translation;
        };

        struct OsInfo {
            Matrice4f matriceDecalage;
            Matrice4f transformFinal;

            OsInfo(const Matrice4f & decalage);
        };

        struct NoeudInfo {
            const aiNode * pNoeud = NULL;
            bool estNecessair = false;

            NoeudInfo();
            NoeudInfo(const aiNode * n);
        };

        std::vector<SqueletteSommet> _squeletteSommets;
        GLuint _osBuffer;
        std::map<std::string,uint> _osIndMap;
        std::vector<OsInfo> _osInfos;
        std::map<std::string,NoeudInfo> _noeudMap;

    public:
        SqueletteMesh();
        ~SqueletteMesh();

        uint getNbreOs() const;
        std::vector<Matrice4f> getSqueletteTransforms(float temps, uint animationInd = 0);
        std::vector<Matrice4f> getSqueletteTransformsAttache
            (float temps, uint deb, uint fin, float taux);

    private:
        int getOsId(const aiBone * pBone);
        uint getPositionAi(float temps, const aiNodeAnim * pNodeAnim);
        uint getScalingAi(float temps, const aiNodeAnim * pNodeAnim);
        uint getRotationAi(float temps, const aiNodeAnim * pNodeAnim);
        const aiNodeAnim *
            getNodeAnim(const aiAnimation & animation, const std::string & nomNoeud);
        void reserve(uint nbreSommet, uint nbreInd);
        void initMesh(uint meshInd, const aiMesh * paiMesh);
        void initBuffers();
        void chargerSquelettes(uint meshInd, const aiMesh * paiMesh, int baseSommet);
        void chargerSquelette(uint meshInd, const aiBone * pBone, int baseSommet);
        // Au moins deux valeur pour interpoler
        void interpoleScaling(aiVector3D & out, float temps, const aiNodeAnim * pNodeAnim);
        void interpoleRotation(aiQuaternion & out, float temps, const aiNodeAnim * pNodeAnim);
        void interpolePosition(aiVector3D & out, float temps, const aiNodeAnim * pNodeAnim);
        void hierarchieNoeud
        (float temps, const aiNode * pNode,
         const Matrice4f & parentTransform, const aiAnimation & animation);
        void hierarchieNoeudAttache
        (float debAnimationEnTicks, float finAnimationEnTicks, const aiNode * pNode,
         const Matrice4f & parentTransform, const aiAnimation & debAnimation,
         const aiAnimation & finAnimation, float taux);
        void markNoeudPourOs(const aiBone * pBone);
        void initNoeudMap(const aiNode * pNode);
        float convertTempsEnTicks(float tempsEnSecond, uint animationInd);
        void calcLocalTransform
        (LocalTransform & transform, float tickes, const aiNodeAnim * pNodeAnim);

};
