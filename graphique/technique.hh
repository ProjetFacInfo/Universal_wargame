#pragma once

#include <list>
#include <GL/glew.h>

class Technique {
private:
    // TODO : supprimer
    // typedef std::list<GLuint> ShaderObjList;
    // ShaderObjList _shaderObjList;
    std::list<GLuint> _shaderObjList;

// TODO : _shaderProg private ?
protected:
    GLuint _shaderProg;

public:
    Technique();
    virtual ~Technique();

    virtual bool init();
    void activeShaderProgram();
    GLuint getShaderProgram() const;
    GLint getUniformLocation(const char* pUniformName);
    bool ajoutShader(GLenum shaderType, const char* pFic);
    bool finalise();
};
