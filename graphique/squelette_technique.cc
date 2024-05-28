#include "squelette_technique.hh"
#include <cstring>

bool SqueletteTechnique::init() {
    if (!Technique::init()) {
        return false;
    }

    if (!ajoutShader(GL_VERTEX_SHADER, "../graphique/shaders/squelette.vs")) {
        return false;
    }

    if (!ajoutShader(GL_FRAGMENT_SHADER, "../graphique/shaders/lumiere.fs")) {
        return false;
    }

    if (!finalise()) {
        return false;
    }

    if (!initInterne()) {
        return false;
    }

    for (uint i = 0 ; i < nbreElmDansTab(_osLoc) ; i++) {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        snprintf(Name, sizeof(Name), "gOs[%d]", i);
        _osLoc[i] = getUniformLocation(Name);
    }

    return true;
}


void SqueletteTechnique::setSqueletteTransform(uint ind, const Matrice4f & transform) {
    if (ind >= MAX_OS) {
        return;
    }
    glUniformMatrix4fv(_osLoc[ind], 1, GL_TRUE, (const GLfloat*)transform);
}
