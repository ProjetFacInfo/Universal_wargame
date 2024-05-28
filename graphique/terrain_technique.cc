#include "util.hh"
#include "terrain_technique.hh"
#include "GLTerrainTextureUnit.hh"
#include <cassert>


TerrainTechnique::TerrainTechnique()
{
}

bool TerrainTechnique::init() {
    if (!Technique::init()) {
        return false;
    }

    if (!ajoutShader(GL_VERTEX_SHADER, "../graphique/shaders/terrain.vs")) {
        return false;
    }

    if (!ajoutShader(GL_FRAGMENT_SHADER, "../graphique/shaders/terrain.fs")) {
        return false;
    }

    if (!finalise()) {
        return false;
    }

    m_VPLoc = getUniformLocation("gVP");
    m_minHeightLoc = getUniformLocation("gMinHeight");
    m_maxHeightLoc = getUniformLocation("gMaxHeight");
    m_tex0UnitLoc = getUniformLocation("gTextureHeight0");
    m_tex1UnitLoc = getUniformLocation("gTextureHeight1");
    m_tex2UnitLoc = getUniformLocation("gTextureHeight2");
    m_tex3UnitLoc = getUniformLocation("gTextureHeight3");
    m_tex0HeightLoc = getUniformLocation("gHeight0");
    m_tex1HeightLoc = getUniformLocation("gHeight1");
    m_tex2HeightLoc = getUniformLocation("gHeight2");
    m_tex3HeightLoc = getUniformLocation("gHeight3");
    m_reversedLightDirLoc = getUniformLocation("gReversedLightDir");

    if (m_VPLoc == INVALID_UNIFORM_LOCALISATION||
        m_minHeightLoc == INVALID_UNIFORM_LOCALISATION ||
        m_maxHeightLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex0UnitLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex1UnitLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex2UnitLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex3UnitLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex0HeightLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex1HeightLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex2HeightLoc == INVALID_UNIFORM_LOCALISATION ||
        m_tex3HeightLoc == INVALID_UNIFORM_LOCALISATION ||
        m_reversedLightDirLoc == INVALID_UNIFORM_LOCALISATION) {
        return false;
    }

    activeShaderProgram();

    glUniform1i(m_tex0UnitLoc, COLOR_TEXTURE_UNIT_INDEX_0);
    glUniform1i(m_tex1UnitLoc, COLOR_TEXTURE_UNIT_INDEX_1);
    glUniform1i(m_tex2UnitLoc, COLOR_TEXTURE_UNIT_INDEX_2);
    glUniform1i(m_tex3UnitLoc, COLOR_TEXTURE_UNIT_INDEX_3);

    glUseProgram(0);

    return true;
}


void TerrainTechnique::setVP(const Matrice4f& VP)
{
    glUniformMatrix4fv(m_VPLoc, 1, GL_TRUE, (const GLfloat*)VP.m);
}


void TerrainTechnique::setMinMaxHeight(float Min, float Max)
{
    glUniform1f(m_minHeightLoc, Min);
    glUniform1f(m_maxHeightLoc, Max);
}


void TerrainTechnique::setTextureHeights(float Tex0Height, float Tex1Height, float Tex2Height, float Tex3Height)
{
    glUniform1f(m_tex0HeightLoc, Tex0Height);
    glUniform1f(m_tex1HeightLoc, Tex1Height);
    glUniform1f(m_tex2HeightLoc, Tex2Height);
    glUniform1f(m_tex3HeightLoc, Tex3Height);
}


void TerrainTechnique::setLightDir(const Vecteur3f& Dir)
{
    Vecteur3f ReversedLightDir = Dir * -1.0f;
    ReversedLightDir = ReversedLightDir.normaliser();
    glUniform3f(m_reversedLightDirLoc, ReversedLightDir.x, ReversedLightDir.y, ReversedLightDir.z);
}

