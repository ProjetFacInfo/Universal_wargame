#include "squelette_mesh.hh"
#include <cassert>

const uint POSITION_LOCATION    = 0;
const uint TEX_COORD_LOCATION   = 1;
const uint NORMAL_LOCATION      = 2;
const uint OS_ID_LOCATION       = 3;
const uint OS_POIDS_LOCATION    = 4;

const uint NBRE_OS_PAR_SOMMET = 4;

SqueletteMesh::OsSommetInfo::OsSommetInfo()
    :osID{0}, poids{0.0f}, ind(0) {}

void SqueletteMesh::OsSommetInfo::ajoutOsInfo(uint osId, float poid) {
    for (int i = 0; i < ind; i++) {
        if (osID[i] == osId) {
            return;
        }
    }

    if (poid == 0.0f) {
        return;
    }

    if (ind == NBRE_OS_PAR_SOMMET) {
        return;
        assert(0);
    }

    osID[ind] = osId;
    poids[ind] = poid;

    ind++;
}

SqueletteMesh::OsInfo::OsInfo(const Matrice4f & decalage)
    : matriceDecalage(decalage), transformFinal(0) {}

SqueletteMesh::NoeudInfo::NoeudInfo()
    :pNoeud(nullptr), estNecessair(false) {}

SqueletteMesh::NoeudInfo::NoeudInfo(const aiNode * n)
    : pNoeud(n), estNecessair(false){}


SqueletteMesh::~SqueletteMesh() {
    effacer();
}

SqueletteMesh::SqueletteMesh()
    :_osBuffer(0) {}

uint SqueletteMesh::getNbreOs() const {
    return (uint)_osIndMap.size();
}

void SqueletteMesh::reserve(uint nbreSommet, uint nbreInd) {
    Mesh::reserve(nbreSommet, nbreInd);
    initNoeudMap(_pScene->mRootNode);
}


void SqueletteMesh::initMesh(uint meshInd, const aiMesh * paiMesh) {
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    SqueletteSommet v;
    // printf("Mesh %d\n", meshInd);

    for (uint i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D & pPos = paiMesh->mVertices[i];
        // printf("%d: ", i); Vecteur3f v(pPos.x, pPos.y, pPos.z); v.Print();
        v.position = Vecteur3f(pPos.x, pPos.y, pPos.z);

        if (paiMesh->mNormals) {
            const aiVector3D & pNormal = paiMesh->mNormals[i];
            v.normal = Vecteur3f(pNormal.x, pNormal.y, pNormal.z);
        } else {
            aiVector3D normal(0.0f, 1.0f, 0.0f);
            v.normal = Vecteur3f(normal.x, normal.y, normal.z);
        }

        const aiVector3D & pTexCoord = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : Zero3D;
        v.textureCoord = Vecteur2f(pTexCoord.x, pTexCoord.y);

        _squeletteSommets.push_back(v);
    }

    // Populate the index buffer
    for (uint i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace & face = paiMesh->mFaces[i];
        _indices.push_back(face.mIndices[0]);
        _indices.push_back(face.mIndices[1]);
        _indices.push_back(face.mIndices[2]);
    }

    chargerSquelettes(meshInd, paiMesh, _meshes[meshInd].baseSommet);
}

void SqueletteMesh::chargerSquelettes(uint meshInd, const aiMesh * pMesh, int baseSommet) {
    if (pMesh->mNumBones > MAX_OS) {

        printf("Le nombre maximum de squelette de ce model (%d) est supérieur au max supportée (%d)\n", pMesh->mNumBones, MAX_OS);
        printf("Augmente le maximum de squelette MAX_OS dans util.hh et dans le shader");
        assert(0);
    }

    for (uint i = 0 ; i < pMesh->mNumBones ; i++) {
        chargerSquelette(meshInd, pMesh->mBones[i], baseSommet);
    }
}


void SqueletteMesh::chargerSquelette(uint meshInd, const aiBone * pBone, int baseSommet) {
    int BoneId = getOsId(pBone);

    if (BoneId == _osInfos.size()) {
        OsInfo bi(pBone->mOffsetMatrix);
        _osInfos.push_back(bi);
    }

    for (uint i = 0 ; i < pBone->mNumWeights ; i++) {
        const aiVertexWeight & vw = pBone->mWeights[i];
        uint globalSommetID = baseSommet + pBone->mWeights[i].mVertexId;
        _squeletteSommets[globalSommetID].os.ajoutOsInfo(BoneId, vw.mWeight);
    }

    markNoeudPourOs(pBone);
}


void SqueletteMesh::markNoeudPourOs(const aiBone * pBone) {
    std::string nomNoeud(pBone->mName.C_Str());
    const aiNode * pParent = nullptr;

    do {
        std::map<std::string,NoeudInfo>::iterator it = _noeudMap.find(nomNoeud);

        if (it == _noeudMap.end()) {
            printf("Os introuvable %s dans hierarchie \n", nomNoeud.c_str());
            assert(0);
        }

        it->second.estNecessair = true;
        pParent = it->second.pNoeud->mParent;

        if (pParent) {
            nomNoeud = std::string(pParent->mName.C_Str());
        }

    } while (pParent);
}

// Récursif
void SqueletteMesh::initNoeudMap(const aiNode * pNode) {
    std::string nomNoeud(pNode->mName.C_Str());
    NoeudInfo info(pNode);
    _noeudMap[nomNoeud] = info;

    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
        initNoeudMap(pNode->mChildren[i]);
    }
}


int SqueletteMesh::getOsId(const aiBone * pBone) {
    int osInd = 0;
    std::string osNom(pBone->mName.C_Str());

    if (_osIndMap.find(osNom) == _osIndMap.end()) {
        osInd = (int)_osIndMap.size();
        _osIndMap[osNom] = osInd;
    } else {
        osInd = _osIndMap[osNom];
    }

    return osInd;
}


void SqueletteMesh::initBuffers() {
    // glBindBuffer(GL_ARRAY_BUFFER, _buffers[SOMMET_BUFFER]);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[INDEX_BUFFER]);
    //
    // glBufferData(GL_ARRAY_BUFFER, sizeof(_squeletteSommets[0])  * _squeletteSommets.size(),  &_squeletteSommets[0], GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0])  * _indices.size(),  &_indices[0], GL_STATIC_DRAW);
    //
    // size_t nbre = 0;
    //
    // glEnableVertexAttribArray(POSITION_LOCATION);
    // glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(SqueletteSommet), (const void *)(nbre  * sizeof(float)));
    // nbre += 3;
    //
    // glEnableVertexAttribArray(TEX_COORD_LOCATION);
    // glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(SqueletteSommet), (const void *)(nbre  * sizeof(float)));
    // nbre += 2;
    //
    // glEnableVertexAttribArray(NORMAL_LOCATION);
    // glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(SqueletteSommet), (const void *)(nbre  * sizeof(float)));
    // nbre += 3;
    //
    // glEnableVertexAttribArray(OS_ID_LOCATION);
    // glVertexAttribIPointer(OS_ID_LOCATION, NBRE_OS_PAR_SOMMET, GL_INT, sizeof(SqueletteSommet), (const void *)(nbre  * sizeof(float)));
    // nbre += NBRE_OS_PAR_SOMMET;
    //
    // glEnableVertexAttribArray(OS_POIDS_LOCATION);
    // glVertexAttribPointer(OS_POIDS_LOCATION, NBRE_OS_PAR_SOMMET, GL_FLOAT, GL_FALSE, sizeof(SqueletteSommet), (const void *)(nbre  * sizeof(float)));

    // DSA
    glNamedBufferStorage(_buffers[SOMMET_BUFFER], sizeof(_squeletteSommets[0]) * _squeletteSommets.size(), _squeletteSommets.data(), 0);
    glNamedBufferStorage(_buffers[INDEX_BUFFER], sizeof(_indices[0]) * _indices.size(), _indices.data(), GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayVertexBuffer(_VAO, 0, _buffers[SOMMET_BUFFER], 0, sizeof(SqueletteSommet));
    glVertexArrayElementBuffer(_VAO, _buffers[INDEX_BUFFER]);

    size_t nbre = 0;

    glEnableVertexArrayAttrib(_VAO, POSITION_LOCATION);
    glVertexArrayAttribFormat(_VAO, POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, (GLuint)(nbre * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, POSITION_LOCATION, 0);
    nbre += 3;

    glEnableVertexArrayAttrib(_VAO, TEX_COORD_LOCATION);
    glVertexArrayAttribFormat(_VAO, TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, (GLuint)(nbre * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, TEX_COORD_LOCATION, 0);
    nbre += 2;

    glEnableVertexArrayAttrib(_VAO, NORMAL_LOCATION);
    glVertexArrayAttribFormat(_VAO, NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, (GLuint)(nbre * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, NORMAL_LOCATION, 0);
    nbre += 3;

    glEnableVertexArrayAttrib(_VAO, OS_ID_LOCATION);
    glVertexArrayAttribIFormat(_VAO, OS_ID_LOCATION, NBRE_OS_PAR_SOMMET, GL_INT, (GLuint)(nbre * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, OS_ID_LOCATION, 0);

    nbre += NBRE_OS_PAR_SOMMET;

    glEnableVertexArrayAttrib(_VAO, OS_POIDS_LOCATION);
    glVertexArrayAttribFormat(_VAO, OS_POIDS_LOCATION, NBRE_OS_PAR_SOMMET, GL_FLOAT, GL_FALSE, (GLuint)(nbre * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, OS_POIDS_LOCATION, 0);
}

uint SqueletteMesh::getPositionAi(float tickes, const aiNodeAnim * pNodeAnim) {
    for (uint i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        float t = (float)pNodeAnim->mPositionKeys[i + 1].mTime;
        if (tickes < t) {
            return i;
        }
    }

    return 0;
}

uint SqueletteMesh::getScalingAi(float tickes, const aiNodeAnim * pNodeAnim) {
    assert(pNodeAnim->mNumScalingKeys > 0);

    for (uint i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        float t = (float)pNodeAnim->mScalingKeys[i + 1].mTime;
        if (tickes < t) {
            return i;
        }
    }

    return 0;
}

uint SqueletteMesh::getRotationAi(float tickes, const aiNodeAnim * pNodeAnim) {
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (uint i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        float t = (float)pNodeAnim->mRotationKeys[i + 1].mTime;
        if (tickes < t) {
            return i;
        }
    }

    return 0;
}

void SqueletteMesh::calcLocalTransform(LocalTransform & transform, float tickes, const aiNodeAnim * pNodeAnim) {
    interpoleScaling(transform.scaling, tickes, pNodeAnim);
    interpoleRotation(transform.rotation, tickes, pNodeAnim);
    interpolePosition(transform.translation, tickes, pNodeAnim);
}

void SqueletteMesh::interpolePosition(aiVector3D & out, float tickes, const aiNodeAnim * pNodeAnim) {
    if (pNodeAnim->mNumPositionKeys == 1) {
        out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }

    uint positionIndex = getPositionAi(tickes, pNodeAnim);
    uint posIndSuiv = positionIndex + 1;
    assert(posIndSuiv < pNodeAnim->mNumPositionKeys);
    float t1 = (float)pNodeAnim->mPositionKeys[positionIndex].mTime;
    if (t1 > tickes) {
        out = pNodeAnim->mPositionKeys[positionIndex].mValue;
    } else {
        float t2 = (float)pNodeAnim->mPositionKeys[posIndSuiv].mTime;
        float deltaTemps = t2 - t1;
        float facteur = (tickes - t1) / deltaTemps;
        assert(facteur >= 0.0f  && facteur <= 1.0f);
        const aiVector3D & start = pNodeAnim->mPositionKeys[positionIndex].mValue;
        const aiVector3D & end = pNodeAnim->mPositionKeys[posIndSuiv].mValue;
        aiVector3D delta = end - start;
        out = start + facteur  * delta;
    }
}

void SqueletteMesh::interpoleRotation(aiQuaternion & out, float tickes, const aiNodeAnim * pNodeAnim) {
    if (pNodeAnim->mNumRotationKeys == 1) {
        out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }

    uint rotationInd = getRotationAi(tickes, pNodeAnim);
    uint rotationIndSuiv = rotationInd + 1;
    assert(rotationIndSuiv < pNodeAnim->mNumRotationKeys);
    float t1 = (float)pNodeAnim->mRotationKeys[rotationInd].mTime;
    if (t1 > tickes) {
        out = pNodeAnim->mRotationKeys[rotationInd].mValue;
    } else {
        float t2 = (float)pNodeAnim->mRotationKeys[rotationIndSuiv].mTime;
        float deltaTemps = t2 - t1;
        float facteur = (tickes - t1) / deltaTemps;
        assert(facteur >= 0.0f  && facteur <= 1.0f);
        const aiQuaternion & startRotationQ = pNodeAnim->mRotationKeys[rotationInd].mValue;
        const aiQuaternion & endRotationQ   = pNodeAnim->mRotationKeys[rotationIndSuiv].mValue;
        aiQuaternion::Interpolate(out, startRotationQ, endRotationQ, facteur);
    }

    out.Normalize();
}

void SqueletteMesh::interpoleScaling (aiVector3D & out, float tickes, const aiNodeAnim * pNodeAnim) {
    if (pNodeAnim->mNumScalingKeys == 1) {
        out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    uint scalInd = getScalingAi(tickes, pNodeAnim);
    uint scalIndSuiv = scalInd + 1;
    assert(scalIndSuiv < pNodeAnim->mNumScalingKeys);
    float t1 = (float)pNodeAnim->mScalingKeys[scalInd].mTime;
    if (t1 > tickes) {
        out = pNodeAnim->mScalingKeys[scalInd].mValue;
    } else {
        float t2 = (float)pNodeAnim->mScalingKeys[scalIndSuiv].mTime;
        float deltaTemps = t2 - t1;
        float facteur = (tickes - (float)t1) / deltaTemps;
        assert(facteur >= 0.0f  && facteur <= 1.0f);
        const aiVector3D & start = pNodeAnim->mScalingKeys[scalInd].mValue;
        const aiVector3D & end   = pNodeAnim->mScalingKeys[scalIndSuiv].mValue;
        aiVector3D delta = end - start;
        out = start + facteur  * delta;
    }
}


void SqueletteMesh::hierarchieNoeud
(float tickes, const aiNode * pNode, const Matrice4f & parentTransform, const aiAnimation & animation) {
    std::string nomNoeud(pNode->mName.data);
    Matrice4f noeudTransform(pNode->mTransformation);
    const aiNodeAnim * pNodeAnim = getNodeAnim(animation, nomNoeud);

    if (pNodeAnim) {
        LocalTransform transform;
        calcLocalTransform(transform, tickes, pNodeAnim);
        Matrice4f scalMat;
        scalMat.scaleTransform(transform.scaling.x, transform.scaling.y, transform.scaling.z);
        Matrice4f rotationMat(transform.rotation.GetMatrix());
        Matrice4f translationMat;
        translationMat.translationTransform(transform.translation.x, transform.translation.y, transform.translation.z);
        noeudTransform = translationMat  * rotationMat  * scalMat;
    }

    Matrice4f globalTransform = parentTransform  * noeudTransform;

    if (_osIndMap.find(nomNoeud) != _osIndMap.end()) {
        uint osInd = _osIndMap[nomNoeud];
        _osInfos[osInd].transformFinal = _globalInverseTransform  * globalTransform  * _osInfos[osInd].matriceDecalage;
    }

    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
        std::string noeudFils(pNode->mChildren[i]->mName.data);

        std::map<std::string,NoeudInfo>::iterator it = _noeudMap.find(noeudFils);

        if (it == _noeudMap.end()) {
            printf("noeud fils %s introuvable dans le noeud map\n", noeudFils.c_str());
            assert(0);
        }

        if (it->second.estNecessair) {
            hierarchieNoeud(tickes, pNode->mChildren[i], globalTransform, animation);
        }
    }
}


std::vector<Matrice4f> SqueletteMesh::getSqueletteTransforms(float temps, uint animationInd) {
    if (animationInd >= _pScene->mNumAnimations) {
        printf("animation ind invalid %d, le max est %d\n", animationInd, _pScene->mNumAnimations);
        assert(0);
    }

    Matrice4f identite;
    identite.identite();
    float animationEnTicks = convertTempsEnTicks(temps, animationInd);
    const aiAnimation & animation =  *_pScene->mAnimations[animationInd];

    hierarchieNoeud(animationEnTicks, _pScene->mRootNode, identite, animation);
    std::vector<Matrice4f> transforms;
    transforms.resize(_osInfos.size());

    for (uint i = 0 ; i < _osInfos.size() ; i++) {
        transforms[i] = _osInfos[i].transformFinal;
    }
    return transforms;
}


float SqueletteMesh::convertTempsEnTicks(float tempsEnSecond, uint animationInd) {
    float ticksParSecondre = (float)(_pScene->mAnimations[animationInd]->mTicksPerSecond != 0 ? _pScene->mAnimations[animationInd]->mTicksPerSecond : 25.0f);
    float TempsEnTicks = tempsEnSecond * ticksParSecondre;
    double duree = (float)((int)_pScene->mAnimations[animationInd]->mDuration);
    return fmod(TempsEnTicks, (float)duree);
}

const aiNodeAnim *
SqueletteMesh::getNodeAnim(const aiAnimation & animation, const std::string & nomNoeud) {
    for (uint i = 0 ; i < animation.mNumChannels ; i++) {
        const aiNodeAnim * pNodeAnim = animation.mChannels[i];

        if (std::string(pNodeAnim->mNodeName.data) == nomNoeud) {
            return pNodeAnim;
        }
    }

    return nullptr;
}
