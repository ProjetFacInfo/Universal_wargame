#include "technique.hh"
#include "util.hh"

#include <cstdio>
#include <cstring>


Technique::Technique()
    : _shaderProg(0) {}


Technique::~Technique() {
    for (std::list<GLuint>::iterator it = _shaderObjList.begin() ; it != _shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    if (_shaderProg != 0) {
        glDeleteProgram(_shaderProg);
        _shaderProg = 0;
    }
}


bool Technique::init() {
    _shaderProg = glCreateProgram();

    if (_shaderProg == 0) {
        fprintf(stderr, "erreur creation shader program\n");
        return false;
    }

    return true;
}

void Technique::activeShaderProgram() {
    glUseProgram(_shaderProg);
}

GLuint Technique::getShaderProgram() const {
    return _shaderProg;
}

GLint Technique::getUniformLocation(const char* pUniformName) {
    GLuint Location = glGetUniformLocation(_shaderProg, pUniformName);

    if (Location == INVALID_UNIFORM_LOCALISATION) {
        fprintf(stderr, "attention! Impossible de recupere l'emplacement de la variable uniform '%s'\n", pUniformName);
    }
    // else {
        // printf("Success! recupere l'emplacement de la variable uniform '%s'\n", pUniformName);
    // }

    return Location;
}

bool Technique::ajoutShader(GLenum shaderType, const char* pFic) {
    std::string s;

    if (!lireFichier(pFic, s)) {
        fprintf(stderr, "erreur fichier ajout shader %s\n",  pFic);
        return false;
    }

    GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0) {
        fprintf(stderr, "erreur creation shader type %d\n", shaderType);
        return false;
    }

    _shaderObjList.push_back(shaderObj);

    const GLchar* p[1];
    p[0] = s.c_str();
    GLint longueur[1] = { (GLint)s.size() };

    glShaderSource(shaderObj, 1, p, longueur);

    glCompileShader(shaderObj);

    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
        fprintf(stderr, "erreur compilation '%s': '%s'\n", pFic, infoLog);
        return false;
    }

    glAttachShader(_shaderProg, shaderObj);

    return true;
}


bool Technique::finalise() {
    GLint succes = 0;
    GLchar erreuLog[1024] = { 0 };

    glLinkProgram(_shaderProg);

    glGetProgramiv(_shaderProg, GL_LINK_STATUS, &succes);
        if (succes == 0) {
                glGetProgramInfoLog(_shaderProg, sizeof(erreuLog), NULL, erreuLog);
                fprintf(stderr, "erreur d'édition de lien shader program: '%s'\n", erreuLog);
        return false;
        }

    glValidateProgram(_shaderProg);
    glGetProgramiv(_shaderProg, GL_VALIDATE_STATUS, &succes);
    if (!succes) {
        glGetProgramInfoLog(_shaderProg, sizeof(erreuLog), NULL, erreuLog);
        fprintf(stderr, "Invalide shader program: '%s'\n", erreuLog);
    }

    for (std::list<GLuint>::iterator it = _shaderObjList.begin() ; it != _shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    _shaderObjList.clear();

    return glGetError() == GL_NO_ERROR;
}




