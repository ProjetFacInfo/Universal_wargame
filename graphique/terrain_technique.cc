#include "util.hh"
#include "terrain_technique.hh"
#include "GLTerrainTextureUnit.hh"
#include <cassert>


TerrainTechnique::TerrainTechnique()
    : _VPLoc(INVALID_UNIFORM_LOCALISATION), _hauteutMinLoc(INVALID_UNIFORM_LOCALISATION),
     _hauteurMaxLoc(INVALID_UNIFORM_LOCALISATION), _hauteurTex0Loc(INVALID_UNIFORM_LOCALISATION),
     _hauteurTex1Loc(INVALID_UNIFORM_LOCALISATION), _hauteurTex2Loc(INVALID_UNIFORM_LOCALISATION),
     _hauteurTex3Loc(INVALID_UNIFORM_LOCALISATION), _hauteurTex4Loc(INVALID_UNIFORM_LOCALISATION),
     _hauteurTex5Loc(INVALID_UNIFORM_LOCALISATION), _texUnit0Loc(INVALID_UNIFORM_LOCALISATION),
     _texUnit1Loc(INVALID_UNIFORM_LOCALISATION), _texUnit2Loc(INVALID_UNIFORM_LOCALISATION),
     _texUnit3Loc(INVALID_UNIFORM_LOCALISATION), _texUnit4Loc(INVALID_UNIFORM_LOCALISATION),
     _texUnit5Loc(INVALID_UNIFORM_LOCALISATION), _lumireDirInverseLoc(INVALID_UNIFORM_LOCALISATION) { }

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

    _VPLoc = getUniformLocation("gVP");
    _hauteutMinLoc = getUniformLocation("gHauteurMin");
    _hauteurMaxLoc = getUniformLocation("gHauteutMax");
    _texUnit0Loc = getUniformLocation("gTextureHauteur0");
    _texUnit1Loc = getUniformLocation("gTextureHauteur1");
    _texUnit2Loc = getUniformLocation("gTextureHauteur2");
    _texUnit3Loc = getUniformLocation("gTextureHauteur3");
    _texUnit4Loc = getUniformLocation("gTextureHauteur4");
    _texUnit5Loc = getUniformLocation("gTextureHauteur5");
    _hauteurTex0Loc = getUniformLocation("gHauteur0");
    _hauteurTex1Loc = getUniformLocation("gHauteur1");
    _hauteurTex2Loc = getUniformLocation("gHauteur2");
    _hauteurTex3Loc = getUniformLocation("gHauteur3");
    _hauteurTex4Loc = getUniformLocation("gHauteur4");
    _hauteurTex5Loc = getUniformLocation("gHauteur5");
    _lumireDirInverseLoc = getUniformLocation("gLumiereDirInverse");

    activeShaderProgram();
    glUniform1i(_texUnit0Loc, COULEUR_TEXTURE_UNIT_IND_0);
    glUniform1i(_texUnit1Loc, COULEUR_TEXTURE_UNIT_IND_1);
    glUniform1i(_texUnit2Loc, COULEUR_TEXTURE_UNIT_IND_2);
    glUniform1i(_texUnit3Loc, COULEUR_TEXTURE_UNIT_IND_3);
    glUniform1i(_texUnit4Loc, COULEUR_TEXTURE_UNIT_IND_4);
    glUniform1i(_texUnit5Loc, COULEUR_TEXTURE_UNIT_IND_5);
    glUseProgram(0);
    return true;
}


void TerrainTechnique::setVP(const Matrice4f& VP) {
    glUniformMatrix4fv(_VPLoc, 1, GL_TRUE, (const GLfloat*)VP.m);
}


void TerrainTechnique::setHauteurMinMax(float min, float max) {
    glUniform1f(_hauteutMinLoc, min);
    glUniform1f(_hauteurMaxLoc, max);
}


void TerrainTechnique::setTextureHauteur
(float hauteurTex0, float hauteurTex1, float hauteurTex2, float hauteurTex3, float hauteurTex4, float hauteurTex5) {
    glUniform1f(_hauteurTex0Loc, hauteurTex0);
    glUniform1f(_hauteurTex1Loc, hauteurTex1);
    glUniform1f(_hauteurTex2Loc, hauteurTex2);
    glUniform1f(_hauteurTex3Loc, hauteurTex3);
    glUniform1f(_hauteurTex4Loc, hauteurTex4);
    glUniform1f(_hauteurTex5Loc, hauteurTex5);
}


void TerrainTechnique::setLumiereDir(const Vecteur3f& dir) {
    Vecteur3f lumiereDirInv = dir * -1.0f;
    lumiereDirInv = lumiereDirInv.normaliser();
    glUniform3f(_lumireDirInverseLoc, lumiereDirInv.x, lumiereDirInv.y, lumiereDirInv.z);
}


