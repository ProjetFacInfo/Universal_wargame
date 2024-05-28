#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
    private:
        std::string _nomFic;
        GLenum _textureCible;
        GLuint _textureObj;
        int _largeur;
        int _hauteur;
        // Bits Par Pixel (GL_R8, GL_RGB8, GL_RGBA8, GL_RGB565 , GL_RGBA4)
        int _BPP;

    public:
        Texture(GLenum cible, const std::string & fic);
        Texture(GLenum cible);

        void getTailImage(int & imageLargeur, int & hauteurImage);
        GLuint getTexture() const;

        // Mesh
        void charger(const std::string & fic);
        bool charger();
        void chargerInterne(const void* pImageData);
        void attacher(GLenum textureUnit);
        // terrain
        void charger(unsigned int taiBuffer, void* pImageData);
        void chargerF32(int largeur, int hauteur, const float* pImageData);

};
