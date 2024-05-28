
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>

#include "terrain.hh"
#include "GLTerrainTextureUnit.hh"
#include "logiciel_tiers/stb_image_write.h"

Terrain::~Terrain() {
    effacer();
}


void Terrain::effacer() {
    m_heightMap.effacer();
    m_triangleList.effacer();
}



void Terrain::InitTerrain(float WorldScale, float TextureScale, const std::vector<std::string>& TextureFilenames)
{
    if (!m_terrainTech.init()) {
        printf("Error initializing tech\n");
        exit(0);
    }

    if (TextureFilenames.size() != nbreElmDansTab(m_pTextures)) {
      printf("%s:%d - number of provided textures (%d) is not equal to the size of the texture array (%d)\n", __FILE__, __LINE__, (int)TextureFilenames.size(), (int)nbreElmDansTab(m_pTextures));
        exit(0);
    }

    m_worldScale = WorldScale;
    m_textureScale = TextureScale;

    for (int i = 0 ; i < nbreElmDansTab(m_pTextures) ; i++) {
        m_pTextures[i] = new Texture(GL_TEXTURE_2D);
        m_pTextures[i]->charger(TextureFilenames[i]);
    }
}


float Terrain::getHeightInterpolated(float x, float z) const
{
    float BaseHeight = getHeight((int)x, (int)z);

    if (((int)x + 1 >= m_terrainSize) ||  ((int)z + 1 >= m_terrainSize)) {
        return BaseHeight;
    }

    float NextXHeight = getHeight((int)x + 1, (int)z);

    float RatioX = x - floorf(x);

    float InterpolatedHeightX = (float)(NextXHeight - BaseHeight) * RatioX + (float)BaseHeight;

    float NextZHeight = getHeight((int)x, (int)z + 1);

    float RatioZ = z - floorf(z);

    float InterpolatedHeightZ = (float)(NextZHeight - BaseHeight) * RatioZ + (float)BaseHeight;

    float FinalHeight = (InterpolatedHeightX + InterpolatedHeightZ) / 2.0f;

    return FinalHeight;
}

float Terrain::getHeightInterpolatedBaryCentrique(float x, float z) const {
    int coordX = (int)x;
    int coordZ = (int)z;

    float pos = getHeight(coordX, coordZ);

    if (
           (coordX + 1 >= m_terrainSize)
        || (coordZ + 1 >= m_terrainSize)
        || (coordX < 0)
        || (coordZ < 0)
        ) {
        return pos;
    }


    float hauteur;

    if (x <= (1 - z)) {
        hauteur = baryCentriqueCoord(
                    Vecteur3f(0, getHeight(coordX, coordZ), 0)
                    , Vecteur3f(1, getHeight(coordX, coordZ + 1), 0)
                    , Vecteur3f(1, getHeight(coordX + 1, coordZ + 1), 1)
                    , Vecteur2f(coordX, coordZ)
                    );
    } else {
        hauteur = baryCentriqueCoord(
                    Vecteur3f(0, getHeight(coordX, coordZ), 0)
                    , Vecteur3f(1, getHeight(coordX + 1, coordZ + 1), 1)
                    , Vecteur3f(0, getHeight(coordX + 1, coordZ), 1)
                    , Vecteur2f(coordX, coordZ)
                    );
    }
    return hauteur;
}

float Terrain::getWorldHeight(float x, float z) const
{
    float HeightMapX = x / m_worldScale;
    float HeightMapZ = z / m_worldScale;

    return getHeightInterpolated(HeightMapX, HeightMapZ);
    // return getHeightInterpolatedBaryCentrique(HeightMapX, HeightMapZ);
}

Vecteur3f Terrain::ConstrainPosToTerrain(const Vecteur3f& Pos) {
    Vecteur3f NewPos = Pos;

    // Make sure camera doesn't go outside of the terrain bounds
    if (Pos.x < 0.0f) {
        NewPos.x = 0.0f;
    }

    if (Pos.z < 0.0f) {
        NewPos.z = 0.0f;
    }

    if (Pos.x >= (getWorldSize() - 1.0f)) {
        NewPos.x = getWorldSize() - 2.0f;
    }


    if (Pos.z >= (getWorldSize() - 1.0f)) {
        NewPos.z = getWorldSize() - 2.0f;
    }

    NewPos.y = getWorldHeight(Pos.x, Pos.z);
    // std::cerr << " constrainpostoterrain ok " << std::endl;

    // NewPos.y += 0.0f;

    return NewPos;
}

void Terrain::CreateMap(const char * pFileName, int size, float MinHeight, float MaxHeight) {
    m_terrainSize = size ;
    setMinMaxHeight(MinHeight, MaxHeight);
    LoadMap(pFileName, m_terrainSize);
    m_heightMap.normaliser(MinHeight, MaxHeight);
    m_triangleList.CreateTriangleList(m_terrainSize, m_terrainSize, this);
    // std::cout<<"ok"<<std::endl;
}

void Terrain::LoadMap(const char* pFilename, int size) {
    std::ifstream fic(pFilename);

    float * data = (float * )malloc(size * size * sizeof(float));
    int ind(0);
    if(not fic)	{
        std::cout<<"ERREUR,Impossible d'ouvrir le fichier."<<std::endl;
    } else{
        std::string mot;
        float hauteur;

        while(fic >> mot){
            hauteur = std::stof(mot);
            data[ind++] = hauteur;
        }
    }
    std::cout << "Terrain size : " << size << std::endl;
    m_heightMap.initTableau2D(size, size, data);
}

// void Terrain::LoadFromFile(const char* pFilename)
// {
//     LoadHeightMapFile(pFilename);
//
//     m_triangleList.CreateTriangleList(m_terrainSize, m_terrainSize, this);
// }
//
//
// void Terrain::LoadHeightMapFile(const char* pFilename)
// {
//     int FileSize = 0;
//     unsigned char* p = (unsigned char*)ReadBinaryFile(pFilename, FileSize);
//
//     if (FileSize % sizeof(float) != 0) {
//         printf("%s:%d - '%s' does not contain an whole number of floats (size %d)\n", __FILE__, __LINE__, pFilename, FileSize);
//         exit(0);
//     }
//
//     m_terrainSize = (int)sqrtf((float)FileSize / (float)sizeof(float));
//
//     printf("Terrain size %d\n", m_terrainSize);
//
//     if ((m_terrainSize * m_terrainSize) != (FileSize / sizeof(float))) {
//         printf("%s:%d - '%s' does not contain a square height map - size %d\n", __FILE__, __LINE__, pFilename, FileSize);
//         exit(0);
//     }
//
//     m_heightMap.initTableau2D(m_terrainSize, m_terrainSize, (float*)p);
// }


void Terrain::SaveToFile(const char* pFilename)
{
    unsigned char* p = (unsigned char*)malloc(m_terrainSize * m_terrainSize);

    float* src = m_heightMap.getBaseAddr();

    float Delta = m_maxHeight - m_minHeight;

    for (int i = 0; i < m_terrainSize * m_terrainSize; i++) {
        float f = (src[i] - m_minHeight) / Delta;
        p[i] = (unsigned char)(f * 255.0f);
    }

    std::ofstream file;
    file.open(pFilename);

    for (int i = 0; i < m_terrainSize; ++i) {
        for (int j = 0; j < m_terrainSize; ++j) {
            file << m_heightMap.at(i,j) << " ";
        }
        file << "\n";
    }

    file.close();


    stbi_write_png("heightmap.png", m_terrainSize, m_terrainSize, 1, p, m_terrainSize);

    free(p);
}


void Terrain::Render(const Camera& camera) {
    Matrice4f VP = camera.getVueProjMat();

    m_terrainTech.activeShaderProgram();
    m_terrainTech.setVP(VP);

    for (int i = 0; i < nbreElmDansTab(m_pTextures); i++) {
        if (m_pTextures[i]) {
            m_pTextures[i]->attacher(COLOR_TEXTURE_UNIT_0 + i);
        }
    }

    m_terrainTech.setLightDir(m_lightDir);

    m_triangleList.Render();
}


void Terrain::setMinMaxHeight(float MinHeight, float MaxHeight) {
    m_minHeight = MinHeight;
    m_maxHeight = MaxHeight;

    m_terrainTech.activeShaderProgram();
    m_terrainTech.setMinMaxHeight(MinHeight, MaxHeight);
}


void Terrain::setTextureHeights(float Tex0Height, float Tex1Height, float Tex2Height, float Tex3Height)
{
    m_terrainTech.setTextureHeights(Tex0Height, Tex1Height, Tex2Height, Tex3Height);
}

void Terrain::CreateMidpointDisplacement(int TerrainSize, float Roughness, float MinHeight, float MaxHeight)
{
    if (Roughness < 0.0f) {
        printf("%s: roughness must be positive - %f\n", __FUNCTION__, Roughness);
        exit(0);
    }

    m_terrainSize = TerrainSize;

    setMinMaxHeight(MinHeight, MaxHeight);

    std::cout << "Terrain size : " << TerrainSize << std::endl;
    m_heightMap.initTableau2D(TerrainSize, TerrainSize, 0.0f);

    CreateMidpointDisplacementF32(Roughness);

    m_heightMap.normaliser(MinHeight, MaxHeight);

    m_triangleList.CreateTriangleList(m_terrainSize, m_terrainSize, this);

    // m_heightMap.print();
}


void Terrain::CreateMidpointDisplacementF32(float indChaos)
{
    // int RectSize = CalcNextPowerOfTwo(m_terrainSize);
    int RectSize = m_terrainSize;
    float CurHeight = (float)RectSize / 2.0f;
    float HeightReduce = pow(2.0f, -indChaos);

    while (RectSize > 0) {

        DiamondStep(RectSize, CurHeight);

        SquareStep(RectSize, CurHeight);

        RectSize /= 2;
        CurHeight *= HeightReduce;
    }

    // TODO : faire mer (-0.1 -> -1) + ocean (-1 -> -2)
}


void Terrain::DiamondStep(int RectSize, float CurHeight)
{
    int HalfRectSize = RectSize / 2;

    // x,y represente le coin superieur gauche de chaque sous-rectangle
    // next_x, next_y represente le coin inferieur droite de chaque sous-rectangle
    for (int y = 0 ; y < m_terrainSize ; y += RectSize) {
        for (int x = 0 ; x < m_terrainSize ; x += RectSize) {
            int next_x = (x + RectSize) % m_terrainSize;
            int next_y = (y + RectSize) % m_terrainSize;

            if (next_x < x) {
                next_x = m_terrainSize - 1;
            }

            if (next_y < y) {
                next_y = m_terrainSize - 1;
            }

            // Les 4 coins du sous-rectangle
            float TopLeft     = m_heightMap.get(x, y);
            float TopRight    = m_heightMap.get(next_x, y);
            float BottomLeft  = m_heightMap.get(x, next_y);
            float BottomRight = m_heightMap.get(next_x, next_y);

            //
            int mid_x = (x + HalfRectSize) % m_terrainSize;
            int mid_y = (y + HalfRectSize) % m_terrainSize;

            float RandValue = plageFloattantAleatoire(CurHeight, -CurHeight);
            float MidPoint = (TopLeft + TopRight + BottomLeft + BottomRight) / 4.0f;

            m_heightMap.set(mid_x, mid_y, MidPoint + RandValue);
        }
    }
}


void Terrain::SquareStep(int RectSize, float CurHeight)
{
    int HalfRectSize = RectSize / 2;

    for (int y = 0 ; y < m_terrainSize ; y += RectSize) {
        for (int x = 0 ; x < m_terrainSize ; x += RectSize) {
            int next_x = (x + RectSize) % m_terrainSize;
            int next_y = (y + RectSize) % m_terrainSize;

            if (next_x < x) {
                next_x = m_terrainSize - 1;
            }

            if (next_y < y) {
                next_y = m_terrainSize - 1;
            }

            int mid_x = (x + HalfRectSize) % m_terrainSize;
            int mid_y = (y + HalfRectSize) % m_terrainSize;

            int prev_mid_x = (x - HalfRectSize + m_terrainSize) % m_terrainSize;
            int prev_mid_y = (y - HalfRectSize + m_terrainSize) % m_terrainSize;

            float CurTopLeft  = m_heightMap.get(x, y);
            float CurTopRight = m_heightMap.get(next_x, y);
            float CurCenter   = m_heightMap.get(mid_x, mid_y);
            float PrevYCenter = m_heightMap.get(mid_x, prev_mid_y);
            float CurBotLeft  = m_heightMap.get(x, next_y);
            float PrevXCenter = m_heightMap.get(prev_mid_x, mid_y);

            float CurLeftMid = (CurTopLeft + CurCenter + CurBotLeft + PrevXCenter) / 4.0f + plageFloattantAleatoire(-CurHeight, CurHeight);
            float CurTopMid  = (CurTopLeft + CurCenter + CurTopRight + PrevYCenter) / 4.0f + plageFloattantAleatoire(-CurHeight, CurHeight);

            m_heightMap.set(mid_x, y, CurTopMid);
            m_heightMap.set(x, mid_y, CurLeftMid);
        }
    }
}

