#include "texture_technique.hh"

TextureTechnique::TextureTechnique()
    :_MVPLoc(-1), _samplerLoc(-1) { }

bool TextureTechnique::init() {
    if (!Technique::init()) {
        return false;
    }

    if (!ajoutShader(GL_VERTEX_SHADER, "../graphique/shaders/texture.vs")) {
        return false;
    }

    if (!ajoutShader(GL_FRAGMENT_SHADER, "../graphique/shaders/texture.fs")) {
        return false;
    }

    if (!finalise()) {
        return false;
    }

    _MVPLoc = getUniformLocation("gMVP");
    _samplerLoc = getUniformLocation("gSampler");

    if (_MVPLoc == INVALID_UNIFORM_LOCALISATION ||
        _samplerLoc == INVALID_UNIFORM_LOCALISATION) {
        return false;
    }

    return true;
}


void TextureTechnique::setTextureUnit(uint textureUnit) {
    glUniform1i(_samplerLoc, textureUnit);
}


void TextureTechnique::setMVP(const Matrice4f & MVP) {
    glUniformMatrix4fv(_MVPLoc, 1, GL_TRUE, (const GLfloat*)MVP.m);
}
