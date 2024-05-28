#pragma once

#include "types.hh"
#include "camera.hh"
#include "tableau2D.hh"
#include "texture.hh"
#include "triangle_list.hh"
#include "terrain_technique.hh"

class Terrain
{
 public:
    Terrain() {}

    ~Terrain();

    void effacer();

	void InitTerrain(float WorldScale, float TextureScale, const std::vector<std::string>& TextureFilenames);

    void Render(const Camera& camera);

    // void LoadFromFile(const char* pFilename);
    //
    void LoadMap(const char* pFilename, int size);

    void CreateMap(const char * pFileName, int size, float MinHeight, float MaxHeight);
    void SaveToFile(const char* pFilename);

	float getHeight(int x, int z) const { return m_heightMap.get(x, z); }

    float getWorldHeight(float x, float z) const;

    float getHeightInterpolated(float x, float z) const;

    float getHeightInterpolatedBaryCentrique(float x, float z) const;

	float getWorldScale() const { return m_worldScale; }

    float getTextureScale() const { return m_textureScale; }

    int getSize() const { return m_terrainSize; }

    void setTexture(Texture* pTexture) { m_pTextures[0] = pTexture; }

    void setTextureHeights(float Tex0Height, float Tex1Height, float Tex2Height, float Tex3Height);

    void setLightDir(const Vecteur3f& Dir) { m_lightDir = Dir; }

    float getMaxHeight() const { return m_maxHeight; }
    float getWorldSize() const { return m_terrainSize * m_worldScale; }
    Vecteur3f ConstrainPosToTerrain(const Vecteur3f& Pos);

    void CreateMidpointDisplacement(int Size, float Roughness, float MinHeight, float MaxHeight);

 protected:

	// void LoadHeightMapFile(const char* pFilename);

    void setMinMaxHeight(float MinHeight, float MaxHeight);


    int m_terrainSize = 0;
	  float m_worldScale = 1.0f;
    tableau2D<float> m_heightMap;
    TriangleList m_triangleList;
    Texture* m_pTextures[4] = { 0 };
    float m_textureScale = 1.0f;

private:
    float m_minHeight = 0.0f;
    float m_maxHeight = 0.0f;
    TerrainTechnique m_terrainTech;
    Vecteur3f m_lightDir;

    void CreateMidpointDisplacementF32(float Roughness);
    void DiamondStep(int RectSize, float CurHeight);
    void SquareStep(int RectSize, float CurHeight);
};

