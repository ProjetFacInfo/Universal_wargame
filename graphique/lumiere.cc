#include "lumiere.hh"
#include <cstring>
#include <iostream>

LumiereBase::LumiereBase()
    :couleur(Vecteur3f(1.0f, 1.0f, 1.0f)), intensiteAmbiante(0.0f), intensiteDiffuse(0.0f) {}

bool LumiereBase::estZero() {
    return ((intensiteAmbiante == 0) && (intensiteDiffuse == 0.0f));
}

LumiereDirectionnel::LumiereDirectionnel()
    :directionMonde(Vecteur3f(0.0f, 0.0f, 0.0f)), directionLocal(Vecteur3f(0.0f, 0.0f, 0.0f)) {}

const Vecteur3f& LumiereDirectionnel::getDirectionLocal() const {
    return directionLocal;
}

void LumiereDirectionnel::calcDirectionLocal(const MondeTrans& mondeTransform) {
    directionLocal = mondeTransform.dirMondeEnDirLocal(directionMonde);
}


Attenuation::Attenuation()
    :constant(1.0f), linear(0.0f), exponentiel(0.0f) {}

LumierePonctuel::LumierePonctuel()
        :posMonde(Vecteur3f(0.0f, 0.0f, 0.0f)), posLocal(Vecteur3f(0.0f, 0.0f, 0.0f)) {}

const Vecteur3f& LumierePonctuel::getPosLocal() const {
    return posLocal;
}

void LumierePonctuel::calcPosLocal(const MondeTrans& mondeTransform) {
    posLocal = mondeTransform.posMondeEnPosLocal(posMonde);
}

LumiereProjecteur::LumiereProjecteur()
    : directionMonde(Vecteur3f(0.0f, 0.0f, 0.0f))
      , directionLocal(Vecteur3f(0.0f, 0.0f, 0.0f)), limite(0.0f)  {}

void LumiereProjecteur::calcDirEtPosLocal(const MondeTrans& mondeTransform) {
    calcPosLocal(mondeTransform);
    directionLocal = mondeTransform.dirMondeEnDirLocal(directionMonde);
}

const Vecteur3f& LumiereProjecteur::getDirectionLocal() const { return directionLocal; }


LumiereTechnique::LumiereTechnique()
    :MVPLoc(INVALID_UNIFORM_LOCALISATION), matMondeLoc(INVALID_UNIFORM_LOCALISATION),
    matVueLoc(INVALID_UNIFORM_LOCALISATION), lumiereMVPLoc(INVALID_UNIFORM_LOCALISATION),
    samplerLoc(INVALID_UNIFORM_LOCALISATION), ombreCarteLoc(INVALID_UNIFORM_LOCALISATION),
    ombreCubeCarteLoc(INVALID_UNIFORM_LOCALISATION), ombreCarteLargeurLoc(INVALID_UNIFORM_LOCALISATION),
    ombreCarteHauteurLoc(INVALID_UNIFORM_LOCALISATION), ombreCartetaiFiltreLoc(INVALID_UNIFORM_LOCALISATION),
    ombreCarteDecalageTextureLoc(INVALID_UNIFORM_LOCALISATION), ombreCarteDecalageTaiTextureLoc(INVALID_UNIFORM_LOCALISATION),
    ombreCarteDecalageTaiFiltreLoc(INVALID_UNIFORM_LOCALISATION), ombreCarteRandomLoc(INVALID_UNIFORM_LOCALISATION),
    samplerExposantSpeculaire(INVALID_UNIFORM_LOCALISATION), cameraLocalPosLoc(INVALID_UNIFORM_LOCALISATION),
    cameraMondePosLoc(INVALID_UNIFORM_LOCALISATION), nbreLumierePonctuelLoc(INVALID_UNIFORM_LOCALISATION),
    nbreLumiereProjecteursLoc(INVALID_UNIFORM_LOCALISATION), lumiereContourActive(INVALID_UNIFORM_LOCALISATION),
    exposantSpeculaireActive(INVALID_UNIFORM_LOCALISATION), estPBRLoc(INVALID_UNIFORM_LOCALISATION),
    clipPlanLoc(INVALID_UNIFORM_LOCALISATION) { }

bool LumiereTechnique::init() {
    if (!Technique::init()) {
        return false;
    }

    if (!ajoutShader(GL_VERTEX_SHADER, "../graphique/shaders/lumiere.vs")) {
        return false;
    }

    if (!ajoutShader(GL_FRAGMENT_SHADER, "../graphique/shaders/lumiere.fs")) {
        return false;
    }

    if (!finalise()) {
        return false;
    }

    return initInterne();
}

bool LumiereTechnique::initInterne() {
    MVPLoc = getUniformLocation("gMVP");
    matMondeLoc = getUniformLocation("gMonde");
    lumiereMVPLoc = getUniformLocation("gLumiereMVP");
    samplerLoc = getUniformLocation("gSampler");
    ombreCarteLoc = getUniformLocation("gOmbreCarte");
    ombreCubeCarteLoc = getUniformLocation("gOmbreCubeCarte");
    ombreCarteLargeurLoc = getUniformLocation("gOmbreCarteLargeur");
    ombreCarteHauteurLoc = getUniformLocation("gOmbreCarteHauteur");
    ombreCartetaiFiltreLoc = getUniformLocation("gOmbreTailFiltreCarte");
    ombreCarteDecalageTextureLoc = getUniformLocation("gOmbreCarteDecalageTexture");
    ombreCarteDecalageTaiTextureLoc = getUniformLocation("gOmbreCarteDecalageTaiTexture");
    ombreCarteDecalageTaiFiltreLoc = getUniformLocation("gOmbreCarteDecalageTaiFiltre");
    ombreCarteRandomLoc = getUniformLocation("gOmbreCarteRandomRayon");
    samplerExposantSpeculaire = getUniformLocation("gSamplerExposantSpeculaire");
    materiauLoc.couleurAmbiante = getUniformLocation("gMateriau.couleurAmbiante");
    materiauLoc.couleurDiffuse = getUniformLocation("gMateriau.couleurDiffuse");
    materiauLoc.couleurSpeculaire = getUniformLocation("gMateriau.couleurSpeculaire");
    LumiereDirLoc.couleur = getUniformLocation("gLumiereDirectionnel.base.couleur");
    LumiereDirLoc.intensiteAmbiante = getUniformLocation("gLumiereDirectionnel.base.intensiteAmbiante");
    LumiereDirLoc.direction = getUniformLocation("gLumiereDirectionnel.direction");
    LumiereDirLoc.intensiteDiffuse = getUniformLocation("gLumiereDirectionnel.base.intensiteDiffuse");
    cameraLocalPosLoc = getUniformLocation("gCameraPosLocal");
    nbreLumierePonctuelLoc = getUniformLocation("gNbreLumierePonctuels");
    nbreLumiereProjecteursLoc = getUniformLocation("gNbreLumiereProjecteurs");
    lumiereContourActive = getUniformLocation("gLumiereContourActive");
    exposantSpeculaireActive = getUniformLocation("gExposantSpeculaireActive");
    estPBRLoc = getUniformLocation("gEstPBR");
    PBRMateriauLoc.rugosite = getUniformLocation("gPBRMateriau.rugosite");
    PBRMateriauLoc.estMetalique = getUniformLocation("gPBRMateriau.estMetalique");
    PBRMateriauLoc.couleur = getUniformLocation("gPBRMateriau.couleur");
    clipPlanLoc = getUniformLocation("gClipPlan");

    for (uint i = 0 ; i < nbreElmDansTab(LumierePonctuelLoc) ; i++) {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].base.couleur", i);
        LumierePonctuelLoc[i].couleur = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].base.intensiteAmbiante", i);
        LumierePonctuelLoc[i].intensiteAmbiante = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].posLocal", i);
        LumierePonctuelLoc[i].localPos = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].posMonde", i);
        LumierePonctuelLoc[i].mondePos = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].base.intensiteDiffuse", i);
        LumierePonctuelLoc[i].intensiteDiffuse = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].atten.constant", i);
        LumierePonctuelLoc[i].atten.constant = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].atten.linear", i);
        LumierePonctuelLoc[i].atten.linear = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumierePonctuels[%d].atten.exponentiel", i);
        LumierePonctuelLoc[i].atten.exponentiel = getUniformLocation(Name);

    }

    for (uint i = 0 ; i < nbreElmDansTab(LumiereProjecteurLoc) ; i++) {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.base.couleur", i);
        LumiereProjecteurLoc[i].couleur = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.base.intensiteAmbiante", i);
        LumiereProjecteurLoc[i].intensiteAmbiante = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.posLocal", i);
        LumiereProjecteurLoc[i].Position = getUniformLocation(Name);


        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].direction", i);
        LumiereProjecteurLoc[i].direction = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].limite", i);
        LumiereProjecteurLoc[i].limite = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.base.intensiteDiffuse", i);
        LumiereProjecteurLoc[i].intensiteDiffuse = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.atten.constant", i);
        LumiereProjecteurLoc[i].atten.constant = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.atten.linear", i);
        LumiereProjecteurLoc[i].atten.linear = getUniformLocation(Name);

        snprintf(Name, sizeof(Name), "gLumiereProjecteurs[%d].base.atten.exponentiel", i);
        LumiereProjecteurLoc[i].atten.exponentiel = getUniformLocation(Name);
    }

    return true;
}


void LumiereTechnique::setMVP(const Matrice4f& MVP) {
    glUniformMatrix4fv(MVPLoc, 1, GL_TRUE, (const GLfloat*)MVP.m);
}


void LumiereTechnique::setMatMonde(const Matrice4f& matMonde) {
    glUniformMatrix4fv(matMondeLoc, 1, GL_TRUE, (const GLfloat*)matMonde.m);
}


void LumiereTechnique::setMatVue(const Matrice4f& matVue) {
    glUniformMatrix4fv(matVueLoc, 1, GL_TRUE, (const GLfloat*)matVue.m);
}

void LumiereTechnique::setLumiereMVP(const Matrice4f& lumiereMVP) {
    glUniformMatrix4fv(lumiereMVPLoc, 1, GL_TRUE, (const GLfloat*)lumiereMVP.m);
}

void LumiereTechnique::setTextureUnit(uint textureUnit) {
    glUniform1i(samplerLoc, textureUnit);
}

void LumiereTechnique::setOmbreTailCarte(uint largeur, uint hauteur) {
    glUniform1i(ombreCarteLargeurLoc, largeur);
    glUniform1i(ombreCarteHauteurLoc, hauteur);
}


void LumiereTechnique::setOmbreTailFiltreCarte(uint size) {
    glUniform1i(ombreCartetaiFiltreLoc, size);
}


void LumiereTechnique::setOmbreTextureUnitCarte(uint textureUnit) {
    glUniform1i(ombreCarteLoc, textureUnit);
}


void LumiereTechnique::setOmbreCubeTextureUnitCarte(uint textureUnit) {
    glUniform1i(ombreCubeCarteLoc, textureUnit);
}


void LumiereTechnique::setOmbreDecalageTextureUnitCarte(uint textureUnit) {
    glUniform1i(ombreCarteDecalageTextureLoc, textureUnit);
}


void LumiereTechnique::setOmbreDecalageTextureParamCarte(float taiTexture, float taiFiltre, float rayon) {
    glUniform1f(ombreCarteDecalageTaiTextureLoc, taiTexture);
    glUniform1f(ombreCarteDecalageTaiFiltreLoc, taiFiltre);
    glUniform1f(ombreCarteRandomLoc, rayon);
}


void LumiereTechnique::setSpecularExponentTextureUnit(uint textureUnit) {
    glUniform1i(samplerExposantSpeculaire, textureUnit);
}


void LumiereTechnique::setLumiereDirectionnel(const LumiereDirectionnel& dirLumiere, bool avecDirection) {
    glUniform3f(LumiereDirLoc.couleur, dirLumiere.couleur.x, dirLumiere.couleur.y, dirLumiere.couleur.z);
    glUniform1f(LumiereDirLoc.intensiteAmbiante, dirLumiere.intensiteAmbiante);
    glUniform1f(LumiereDirLoc.intensiteDiffuse, dirLumiere.intensiteDiffuse);

    if (avecDirection) {
        updateDirLumiereDirection(dirLumiere);
    }
}


void LumiereTechnique::updateDirLumiereDirection(const LumiereDirectionnel& dirLumiere) {
    Vecteur3f directionLocal = dirLumiere.getDirectionLocal();
    directionLocal.normaliser();
    glUniform3f(LumiereDirLoc.direction, directionLocal.x, directionLocal.y, directionLocal.z);
    Vecteur3f directionMonde = dirLumiere.directionMonde;
    directionMonde.normaliser();
}


void LumiereTechnique::setCameraLocalPos(const Vecteur3f& cameraLocalPos) {
    glUniform3f(cameraLocalPosLoc, cameraLocalPos.x, cameraLocalPos.y, cameraLocalPos.z);
}


void LumiereTechnique::setCameraMondePos(const Vecteur3f& cameraMondePos) {
    glUniform3f(cameraMondePosLoc, cameraMondePos.x, cameraMondePos.y, cameraMondePos.z);
}


void LumiereTechnique::setMateriau(const Materiau& materiau) {
    glUniform3f(materiauLoc.couleurAmbiante, materiau.couleurAmbiante.r, materiau.couleurAmbiante.g, materiau.couleurAmbiante.b);
    glUniform3f(materiauLoc.couleurDiffuse, materiau.couleurDiffuse.r, materiau.couleurDiffuse.g, materiau.couleurDiffuse.b);
    glUniform3f(materiauLoc.couleurSpeculaire, materiau.couleurSpeculaire.r, materiau.couleurSpeculaire.g, materiau.couleurSpeculaire.b);
}


void LumiereTechnique::setLumierePonctuels(uint nbreLumiere, const LumierePonctuel* pLumieres, bool avecPos) {
    glUniform1i(nbreLumierePonctuelLoc, nbreLumiere);

    for (uint i = 0 ; i < nbreLumiere ; i++) {
        glUniform3f(LumierePonctuelLoc[i].couleur, pLumieres[i].couleur.x, pLumieres[i].couleur.y, pLumieres[i].couleur.z);
        glUniform1f(LumierePonctuelLoc[i].intensiteAmbiante, pLumieres[i].intensiteAmbiante);
        glUniform1f(LumierePonctuelLoc[i].intensiteDiffuse, pLumieres[i].intensiteDiffuse);
        glUniform1f(LumierePonctuelLoc[i].atten.constant, pLumieres[i].atten.constant);
        glUniform1f(LumierePonctuelLoc[i].atten.linear, pLumieres[i].atten.linear);
        glUniform1f(LumierePonctuelLoc[i].atten.exponentiel, pLumieres[i].atten.exponentiel);
    }

    if (avecPos) {
        updateLumierePonctuelPos(nbreLumiere, pLumieres);
    }
}

void LumiereTechnique::updateLumierePonctuelPos(uint nbreLumiere, const LumierePonctuel* pLumieres) {
    for (uint i = 0 ; i < nbreLumiere ; i++) {
        const Vecteur3f& localPos = pLumieres[i].getPosLocal();
        glUniform3f(LumierePonctuelLoc[i].localPos, localPos.x, localPos.y, localPos.z);
        const Vecteur3f& mondePos = pLumieres[i].posMonde;
        glUniform3f(LumierePonctuelLoc[i].mondePos, mondePos.x, mondePos.y, mondePos.z);
    }
}

void LumiereTechnique::setLumiereProjecteurs(uint nbreLumiere, const LumiereProjecteur* pLumieres, bool avecPosEtDir) {
    glUniform1i(nbreLumiereProjecteursLoc, nbreLumiere);

    for (uint i = 0 ; i < nbreLumiere ; i++) {
        glUniform3f(LumiereProjecteurLoc[i].couleur, pLumieres[i].couleur.x, pLumieres[i].couleur.y, pLumieres[i].couleur.z);
        glUniform1f(LumiereProjecteurLoc[i].intensiteAmbiante, pLumieres[i].intensiteAmbiante);
        glUniform1f(LumiereProjecteurLoc[i].intensiteDiffuse, pLumieres[i].intensiteDiffuse);
        glUniform1f(LumiereProjecteurLoc[i].limite, cosf(degreeEnRadian(pLumieres[i].limite)));
        glUniform1f(LumiereProjecteurLoc[i].atten.constant, pLumieres[i].atten.constant);
        glUniform1f(LumiereProjecteurLoc[i].atten.linear,   pLumieres[i].atten.linear);
        glUniform1f(LumiereProjecteurLoc[i].atten.exponentiel,      pLumieres[i].atten.exponentiel);
    }

    if (avecPosEtDir) {
        updateLumiereProjecteurPosDir(nbreLumiere, pLumieres);
    }
}


void LumiereTechnique::updateLumiereProjecteurPosDir(uint nbreLumiere, const LumiereProjecteur* pLumieres) {
    for (uint i = 0 ; i < nbreLumiere ; i++) {
        const Vecteur3f& localPos = pLumieres[i].getPosLocal();
        glUniform3f(LumiereProjecteurLoc[i].Position, localPos.x, localPos.y, localPos.z);
        Vecteur3f direction = pLumieres[i].getDirectionLocal();
        direction.normaliser();
        glUniform3f(LumiereProjecteurLoc[i].direction, direction.x, direction.y, direction.z);
    }
}


void LumiereTechnique::controlLumiereContour(bool estActive) {
    if (estActive) {
        glUniform1i(lumiereContourActive, 1);
    } else {
        glUniform1i(lumiereContourActive, 0);
    }
}

void LumiereTechnique::controlExposantSpeculaire(bool estActive) {
    if (estActive) {
        glUniform1i(exposantSpeculaireActive, 1);
    } else {
        glUniform1i(exposantSpeculaireActive, 0);
    }
}



void LumiereTechnique::setPBR(bool estPBR) {
    glUniform1i(estPBRLoc, estPBR);
}


void LumiereTechnique::setPBRmateriau(const PBRMateriau& materiau) {
    glUniform1f(PBRMateriauLoc.rugosite, materiau.rugosite);
    glUniform1i(PBRMateriauLoc.estMetalique, materiau.estMetalique);
    glUniform3f(PBRMateriauLoc.couleur, materiau.couleur.r, materiau.couleur.g, materiau.couleur.b);
}


void LumiereTechnique::setClipPlan(const Vecteur3f& normal, const Vecteur3f& pointDansLePlan) {
    float d = -normal.produitScalaire(pointDansLePlan);
    glUniform4f(clipPlanLoc, normal.x, normal.y, normal.z, d);
}
