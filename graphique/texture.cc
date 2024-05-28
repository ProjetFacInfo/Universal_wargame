#include "texture.hh"
#include "util.hh"

#include "logiciel_tiers/stb_image.h"
#include "logiciel_tiers/stb_image_write.h"

#include <cmath>

Texture::Texture(GLenum cible, const std::string & fic)
    :_nomFic(fic), _textureCible(cible), _textureObj(0), _largeur(0), _hauteur(0), _BPP(0) {}

Texture::Texture(GLenum cible)
    :_nomFic(), _textureCible(cible), _textureObj(0), _largeur(0), _hauteur(0), _BPP(0) {}

GLuint Texture::getTexture() const {
    return _textureObj;
}

void Texture::getTailImage(int & imageLargeur, int & hauteurImage) {
    imageLargeur = _largeur;
    hauteurImage = _hauteur;
}

void Texture::charger(const std::string & fic) {
    _nomFic = fic;

    if (!charger()) {
        exit(0);
    }
}

bool Texture::charger() {
    stbi_set_flip_vertically_on_load(1);

    unsigned char* pImageData = stbi_load(_nomFic.c_str(),  &_largeur,  &_hauteur,  &_BPP, 0);

    if (!pImageData) {
        printf("Erreur de chargement de texture : '%s' - %s\n", _nomFic.c_str(), stbi_failure_reason());
        exit(0);
    }

    printf("largeur %d, hauteur %d, BPP %d\n", _largeur, _hauteur, _BPP);

    chargerInterne(pImageData);

    return true;
}

void Texture::chargerInterne(const void* pImageData) {
    // glGenTextures(1,  &_textureObj);
    // glBindTexture(_textureCible, _textureObj);
    //
    // if (_textureCible == GL_TEXTURE_2D) {
    //     switch (_BPP) {
    //     case 1:
    //         glTexImage2D(_textureCible, 0, GL_RED, _largeur, _hauteur, 0, GL_RED, GL_UNSIGNED_BYTE, pImageData);
    //         break;
    //
    //     case 2:
    //         glTexImage2D(_textureCible, 0, GL_RG, _largeur, _hauteur, 0, GL_RG, GL_UNSIGNED_BYTE, pImageData);
    //         break;
    //
    //     case 3:
    //         glTexImage2D(_textureCible, 0, GL_RGB, _largeur, _hauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, pImageData);
    //         break;
    //
    //     case 4:
    //         glTexImage2D(_textureCible, 0, GL_RGBA, _largeur, _hauteur, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImageData);
    //         break;
    //
    //     default:
            // printf("Non implementée %s:%d\n", __FILE__, __LINE__);
            // exit(0);
    //     }
    // } else {
    //     printf("Le support de la texture %x n'est pas implementée\n", _textureCible);
    //     exit(1);
    // }
    //
    // glTexParameteri(_textureCible, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(_textureCible, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(_textureCible, GL_TEXTURE_BASE_LEVEL, 0);
    // glTexParameteri(_textureCible, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(_textureCible, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //
    // glGenerateMipmap(_textureCible);
    //
    // glBindTexture(_textureCible, 0);

    // DSA
    glCreateTextures(_textureCible, 1, &_textureObj);

    int niveau = std::min(5, (int)log2f((float)std::max(_largeur, _hauteur)));

    if (_textureCible == GL_TEXTURE_2D) {
        switch (_BPP) {
        case 1:
            glTextureStorage2D(_textureObj, niveau, GL_R8, _largeur, _hauteur);
            glTextureSubImage2D(_textureObj, 0, 0, 0, _largeur, _hauteur, GL_RED, GL_UNSIGNED_BYTE, pImageData);
            break;

        case 2:
            glTextureStorage2D(_textureObj, niveau, GL_RG8, _largeur, _hauteur);
            glTextureSubImage2D(_textureObj, 0, 0, 0, _largeur, _hauteur, GL_RG, GL_UNSIGNED_BYTE, pImageData);
            break;

        case 3:
            glTextureStorage2D(_textureObj, niveau, GL_RGB8, _largeur, _hauteur);
            glTextureSubImage2D(_textureObj, 0, 0, 0, _largeur, _hauteur, GL_RGB, GL_UNSIGNED_BYTE, pImageData);
            break;

        case 4:
            glTextureStorage2D(_textureObj, niveau, GL_RGBA8, _largeur, _hauteur);
            glTextureSubImage2D(_textureObj, 0, 0, 0, _largeur, _hauteur, GL_RGBA, GL_UNSIGNED_BYTE, pImageData);
            break;

        default:
            printf("Non implementée %s:%d\n", __FILE__, __LINE__);
            exit(0);
        }
    }
    else {
        printf("Le support de la texture %x n'est pas implementée\n", _textureCible);
        exit(1);
    }

    glTextureParameteri(_textureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(_textureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameterf(_textureObj, GL_TEXTURE_BASE_LEVEL, 0);
    glTextureParameteri(_textureObj, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_textureObj, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateTextureMipmap(_textureObj);
}

void Texture::charger(unsigned int taiBuffer, void* pData) {
    void* pImageData = stbi_load_from_memory((const stbi_uc*)pData, taiBuffer,  &_largeur,  &_hauteur,  &_BPP, 0);
    chargerInterne(pImageData);
    stbi_image_free(pImageData);
}

void Texture::attacher(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(_textureCible, _textureObj);
}

void Texture::chargerF32(int largeur, int hauteur, const float* pImageData) {
    _largeur = largeur;
    _hauteur = hauteur;

    glCreateTextures(_textureCible, 1,  &_textureObj);
    glTextureStorage2D(_textureObj, 1, GL_R32F, _largeur, _hauteur);
    glTextureSubImage2D(_textureObj, 0, 0, 0, _largeur, _hauteur, GL_RED, GL_FLOAT, pImageData);

    glTextureParameteri(_textureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(_textureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameterf(_textureObj, GL_TEXTURE_BASE_LEVEL, 0);
    glTextureParameteri(_textureObj, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_textureObj, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// TODO : supprimer
// void Texture::chargerBrut(int largeur, int hauteur, int _BPP, const unsigned char* pImageData)
// {
//     _largeur = largeur;
//     _hauteur = hauteur;
//     _BPP = _BPP;
//
//     chargerInterne(pImageData);
// }


