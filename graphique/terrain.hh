#pragma once

#include "types.hh"
#include "camera.hh"
#include "tableau2D.hh"
#include "texture.hh"
#include "triangle_list.hh"
#include "terrain_technique.hh"

class Terrain {
   private:
      tableau2D<float> _carteHauteur;
      TriangleList _triangleList;
      TerrainTechnique _terrainTech;
      Vecteur3f _lumiereDir;
      int _tailleTerrain;
      float _mondeEchelle;
      Texture* _pTextures[6];
      float _textureEchelle;
      float _hauteurMin;
      float _hauteurMax;

   public:
      Terrain();
      ~Terrain();

      void effacer();
      void initTerrain(float mondeEchelle, float textureEchelle, const std::vector<std::string>& textureNomFic);
      void render(const Camera& camera);
      void chargerCarte(const char* pFilename, int size);
      void creerCarte(const char * pFileName, int size, float hauteurMin, float hauteurMax);
      void saveDansFic(const char* pFilename);
      float getHauteur(int x, int z) const { return _carteHauteur.get(x, z); }
      float getHauteurMax() const { return _hauteurMax; }
      float getTailleMonde() const { return _tailleTerrain * _mondeEchelle; }
      float getTextureEchellee() const { return _textureEchelle; }
      float getMondeEchelle() const { return _mondeEchelle; }
      float getHauteurMonde(float x, float z) const;
      float getHauteurInterpoler(float x, float z) const;
      float getHauteurInterpolerBaryCentrique(float x, float z) const;
      int getTaille() const { return _tailleTerrain; }
      void setHauteurMinMax(float hauteurMin, float hauteurMax);
      void setTexture(Texture* pTexture) { _pTextures[0] = pTexture; }
      void setTextureHauteur(float hauteurTex0, float hauteurTex1, float hauteurTex2, float hauteurTex3, float hauteurTex4, float hauteurTex5);
      void setLumiereDir(const Vecteur3f& dir) { _lumiereDir = dir; }
      void creerCarteDiamantCarre(int Size, float chaos, float hauteurMin, float hauteurMax);
      Vecteur3f constrainPosToTerrain(const Vecteur3f& pos);

   private:
      void diamant(int tailRect, float hauteurCourant);
      void carre(int tailRect, float hauteurCourant);
};

