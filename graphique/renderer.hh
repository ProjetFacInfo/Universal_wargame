#pragma once

#include "camera.hh"
#include "lumiere.hh"
#include "squelette_technique.hh"
#include "mesh.hh"
#include "squelette_mesh.hh"

class Renderer {
private:
    LumiereTechnique _lumiereTech;
    SqueletteTechnique _squeletteTech;
    LumiereDirectionnel _lumiereDir;
    LumierePonctuel _lumierePonctuels[LumiereTechnique::MAX_LUMIERE_PONCTUEL];
    LumiereProjecteur _lumiereProjecteurs[LumiereTechnique::MAX_LUMIERE_PROJECTEUR];
    const Camera * _pCamera;
    uint _nbreLumierePonctuel;
    uint _nbreLumiereProjecteur;
    bool _estPBR;

 public:

    Renderer();
    ~Renderer() = default;
    void initRenderer();

    void getMVP(Mesh* pMesh, Matrice4f& MVP);
    void setCamera(const Camera* pCamera);
    void setPBR(bool estPBR);
    void setLumiereDirectionel(const LumiereDirectionnel& dirLumiere);
    void setLumierePonctuels(uint nbreLumiere, const LumierePonctuel* pLumierePonctuels);
    void setLumiereProjecteurs(uint nbreLumiere, const LumiereProjecteur* pLumiereProjecteurs);
    void updateDirLumiereDir(const Vecteur3f& mondeDir);
    void updateLumierePonctuelPos(uint ind, const Vecteur3f& mondePos);
    void updateLumiereProjecteurPosAndDir(uint ind, const Vecteur3f& mondePos, const Vecteur3f& mondeDir);
    void controlLumiereContour(bool estActive);
    void render(Mesh* pMesh);
    void renderAnimationInterne(SqueletteMesh* pMesh);
    void renderAnimation(SqueletteMesh* pMesh, float tempAnimation, int animationInd = 0);

    void passerEnLumiereTech();
    void passerEnSqueletteTech();
    void actualiseLumierePosDir(Mesh* pMesh);

};
