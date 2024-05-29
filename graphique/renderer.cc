#include "renderer.hh"
#include "GLTextureUnit.hh"

Renderer::Renderer()
    :_pCamera(nullptr), _nbreLumierePonctuel(0), _nbreLumiereProjecteur(0), _estPBR(false) {}


void Renderer::initRenderer() {
    if (!_lumiereTech.init()) {
        printf("erreur initialisation lumiere technique\n");
        exit(1);
    }

    _lumiereTech.activeShaderProgram();
    _lumiereTech.setTextureUnit(COULEUR_TEXTURE_UNIT_IND);

    if (!_squeletteTech.init()) {
        printf("erreur initialisation squelette technique\n");
        exit(1);
    }

    _squeletteTech.activeShaderProgram();
    _squeletteTech.setTextureUnit(COULEUR_TEXTURE_UNIT_IND);

    glUseProgram(0);
}

void Renderer::getMVP(Mesh* pMesh, Matrice4f& MVP) {
    MondeTrans& meshMondeTransform = pMesh->getMondeTransform();

    Matrice4f monde = meshMondeTransform.getMatrice();
    Matrice4f vue = _pCamera->getMatrice();
    Matrice4f proj = _pCamera->getProjectionMat();

    MVP = proj * vue * monde;
}

void Renderer::setCamera(const Camera* pCamera) {
    _pCamera = pCamera;
}

void Renderer::setPBR(bool estPBR) {
    _estPBR = estPBR;
    passerEnLumiereTech();
    _lumiereTech.setPBR(estPBR);
    passerEnSqueletteTech();
    _squeletteTech.setPBR(estPBR);
}

void Renderer::passerEnLumiereTech() {
    GLint cur_prog = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &cur_prog);

    if (cur_prog != _lumiereTech.getShaderProgram()) {
        _lumiereTech.activeShaderProgram();
    }
}


void Renderer::passerEnSqueletteTech() {
    GLint cur_prog = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &cur_prog);

    if (cur_prog != _squeletteTech.getShaderProgram()) {
        _squeletteTech.activeShaderProgram();
    }
}


void Renderer::setLumiereDirectionel(const LumiereDirectionnel& dirLumiere) {
    _lumiereDir = dirLumiere;
    passerEnLumiereTech();
    _lumiereTech.setLumiereDirectionnel(_lumiereDir, false);
    _squeletteTech.activeShaderProgram();
    _squeletteTech.setLumiereDirectionnel(_lumiereDir, false);
}


void Renderer::setLumierePonctuels(uint nbreLumiere, const LumierePonctuel* pLumierePonctuels) {
    if (!pLumierePonctuels || (nbreLumiere == 0)) {
        _nbreLumierePonctuel = 0;
        return;
    }

    if (nbreLumiere > LumiereTechnique::MAX_LUMIERE_PONCTUEL) {
        printf("nombre lumiere ponctuels (%d) > max (%d)\n", nbreLumiere, LumiereTechnique::MAX_LUMIERE_PONCTUEL);
        exit(0);
    }

    for (uint i = 0 ; i < nbreLumiere ; i++) {
        _lumierePonctuels[i] = pLumierePonctuels[i];
    }

    _nbreLumierePonctuel = nbreLumiere;
    passerEnLumiereTech();
    _lumiereTech.setLumierePonctuels(nbreLumiere, pLumierePonctuels, false);
    _squeletteTech.activeShaderProgram();
    _squeletteTech.setLumierePonctuels(nbreLumiere, pLumierePonctuels, false);
}


void Renderer::setLumiereProjecteurs(uint nbreLumiere, const LumiereProjecteur* pLumiereProjecteurs) {
    if (!pLumiereProjecteurs || (nbreLumiere == 0)) {
        _nbreLumiereProjecteur = 0;
        return;
    }

    if (nbreLumiere > LumiereTechnique::MAX_LUMIERE_PROJECTEUR) {
        printf("nombre lumiere spot (%d) > max (%d)\n", nbreLumiere, LumiereTechnique::MAX_LUMIERE_PROJECTEUR);
        exit(0);
    }

    for (uint i = 0 ; i < nbreLumiere ; i++) {
        _lumiereProjecteurs[i] = pLumiereProjecteurs[i];
    }

    _nbreLumiereProjecteur = nbreLumiere;
    passerEnLumiereTech();
    _lumiereTech.setLumiereProjecteurs(nbreLumiere, pLumiereProjecteurs, false);
    _squeletteTech.activeShaderProgram();
    _squeletteTech.setLumiereProjecteurs(nbreLumiere, pLumiereProjecteurs, false);
}


void Renderer::updateDirLumiereDir(const Vecteur3f& mondeDir) {
    _lumiereDir.directionMonde = mondeDir;
}


void Renderer::updateLumierePonctuelPos(uint ind, const Vecteur3f& mondePos) {
    if (ind > _nbreLumierePonctuel) {
        printf("erreur MAJ lumiere ponctuel %d avec la lumiere %d\n", ind, _nbreLumierePonctuel);
        exit(0);
    }

    _lumierePonctuels[ind].posMonde = mondePos;
}


void Renderer::updateLumiereProjecteurPosAndDir(uint ind, const Vecteur3f& mondePos, const Vecteur3f& mondeDir) {
    if (ind > _nbreLumiereProjecteur) {
        printf("erreur MAJ lumiere ponctuel %d avec la lumiere %d\n", ind, _nbreLumiereProjecteur);
        exit(0);
    }

    _lumiereProjecteurs[ind].posMonde = mondePos;
    _lumiereProjecteurs[ind].directionMonde = mondeDir;
}


void Renderer::render(Mesh* pMesh) {
    if (!pMesh) {
        printf("Renderer: Mesh non initialiser\n");
        exit(0);
    }

    if (!_pCamera) {
        printf("Renderer: camera non initialiser\n");
        exit(0);
    }

    if ((_nbreLumierePonctuel == 0) && (_nbreLumiereProjecteur == 0) && _lumiereDir.estZero()) {
        printf("erreur de rendu avec 0 lumiere\n");
    }

    passerEnLumiereTech();

    Matrice4f MVP;
    getMVP(pMesh, MVP);
    _lumiereTech.setMVP(MVP);

    actualiseLumierePosDir(pMesh);

    if (_lumiereDir.intensiteDiffuse > 0.0) {
        _lumiereTech.setLumiereDirectionnel(_lumiereDir);
    }

    _lumiereTech.updateLumierePonctuelPos(_nbreLumierePonctuel, _lumierePonctuels);

    _lumiereTech.updateLumiereProjecteurPosDir(_nbreLumiereProjecteur, _lumiereProjecteurs);

    _lumiereTech.setMateriau(pMesh->getMateriau());

    if (_estPBR) {
        _lumiereTech.setPBR(true);
        _lumiereTech.setPBRmateriau(pMesh->getPBRMateriau());
    } else {
        _lumiereTech.setPBR(false);
    }

    Vecteur3f cameraLocalPos3f = pMesh->getMondeTransform().posMondeEnPosLocal(_pCamera->getPos());
    _lumiereTech.setCameraLocalPos(cameraLocalPos3f);

    Matrice4f World = pMesh->getMondeTransform().getMatrice();
    _lumiereTech.setMatMonde(World);


    pMesh->render();
}


void Renderer::renderAnimation(SqueletteMesh* pMesh, float tempAnimation, int animationInd) {
    if (!pMesh) {
        printf("RendererAnimation: Squelette Mesh non initialiser\n");
        exit(0);
    }

    renderAnimationInterne(pMesh);


    std::vector<Matrice4f> transforms = pMesh->getSqueletteTransforms(tempAnimation, animationInd);

    for (uint i = 0 ; i < transforms.size() ; i++) {
        _squeletteTech.setSqueletteTransform(i, transforms[i]);
    }

    pMesh->render();
}


void Renderer::renderAnimationInterne(SqueletteMesh* pMesh) {
    if (!_pCamera) {
        printf("Renderer: camera non initialiser\n");
        exit(0);
    }

    if ((_nbreLumierePonctuel == 0) && (_nbreLumiereProjecteur == 0) && _lumiereDir.estZero()) {
        printf("erreur de rendu avec 0 lumiere\n");
    }

    passerEnSqueletteTech();
    Matrice4f MVP;
    getMVP(pMesh, MVP);
    _squeletteTech.setMVP(MVP);
    actualiseLumierePosDir(pMesh);

    if (_lumiereDir.intensiteDiffuse > 0.0) {
        _squeletteTech.updateDirLumiereDirection(_lumiereDir);
    }

    _squeletteTech.updateLumierePonctuelPos(_nbreLumierePonctuel, _lumierePonctuels);
    _squeletteTech.updateLumiereProjecteurPosDir(_nbreLumiereProjecteur, _lumiereProjecteurs);
    _squeletteTech.setMateriau(pMesh->getMateriau());

    PBRMateriau materiau;
    materiau.rugosite = 0.50f;
    materiau.estMetalique = false;
    // gris neutre
    materiau.couleur = Vecteur3f(0.9f, 0.9f, 0.9f);
    _squeletteTech.setPBRmateriau(materiau);

    Vecteur3f cameraLocalPos3f = pMesh->getMondeTransform().posMondeEnPosLocal(_pCamera->getPos());
    _squeletteTech.setCameraLocalPos(cameraLocalPos3f);

    Matrice4f World = pMesh->getMondeTransform().getMatrice();
    _squeletteTech.setMatMonde(World);

}

void Renderer::actualiseLumierePosDir(Mesh* pMesh) {
    MondeTrans& meshMondeTransform = pMesh->getMondeTransform();

    if (_lumiereDir.intensiteDiffuse > 0.0) {
        _lumiereDir.calcDirectionLocal(meshMondeTransform);
    }

    for (uint i = 0 ; i < _nbreLumierePonctuel ; i++) {
        _lumierePonctuels[i].calcPosLocal(meshMondeTransform);
    }

    for (uint i = 0 ; i < _nbreLumiereProjecteur ; i++) {
        _lumiereProjecteurs[i].calcDirEtPosLocal(meshMondeTransform);
    }
}



void Renderer::controlLumiereContour(bool estActive) {
    passerEnLumiereTech();
    _lumiereTech.controlLumiereContour(estActive);
    _squeletteTech.activeShaderProgram();
    _squeletteTech.controlLumiereContour(estActive);
}
