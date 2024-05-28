#include "mesh.hh"
#include "GLTextureUnit.hh"
#include <cassert>
#include <iostream>

const uint INVALID_MATERIAL     = 0xFFFFFFFF;
const uint POSITION_LOCATION    = 0;
const uint TEX_COORD_LOCATION   = 1;
const uint NORMAL_LOCATION      = 2;

Mesh::Mesh() :_VAO(0), _buffers{0} {
    Mesh::MeshInfo();
}

Mesh::MeshInfo::MeshInfo()
    : nbreInd(0), baseSommet(0), baseInd(0), materiauInd(INVALID_MATERIAL) {}

Mesh::~Mesh() {
    effacer();
}

float Mesh::getScale() const {
    return _mondeTrans.getScale();
}

Vecteur3f Mesh::getPosition() const {
    return _mondeTrans.getPosition();
}

void Mesh::setScale(float Scale) {
    _mondeTrans.setScale(Scale);
}

void Mesh::setRotation(float x, float y, float z) {
    _mondeTrans.setRotation(x, y, z);
}

void Mesh::setPosition(float x, float y, float z) {
    _mondeTrans.setPosition(x, y, z);
}

void Mesh::setPosition(const Vecteur3f & v) {
    setPosition(v.x, v.y, v.z);
}

Matrice4f Mesh::getMondeMatrice() const {
    return _mondeTrans.getMatrice();
}

MondeTrans  & Mesh::getMondeTransform() {
    return _mondeTrans;
}

PBRMateriau & Mesh::getPBRMateriau() {
    return _materiaux[0].PBRmateriau;
}

void Mesh::effacer() {
    if (_buffers[0] != 0) {
        glDeleteBuffers(nbreElmDansTab(_buffers), _buffers);
    }

    if (_VAO != 0) {
        glDeleteVertexArrays(1,  &_VAO);
        _VAO = 0;
    }
}

bool Mesh::chargerMesh(const std::string & fic) {
    effacer();

    // Créer le VAO
    glCreateVertexArrays(1, &_VAO);
    glCreateBuffers(nbreElmDansTab(_buffers), _buffers);

    bool tmp = false;

    _pScene = _importer.ReadFile(fic.c_str(), ASSIMP_LOAD_FLAGS);

    if (_pScene) {
        _globalInverseTransform = _pScene->mRootNode->mTransformation;
        _globalInverseTransform = _globalInverseTransform.inverse();
        tmp = initScene(_pScene, fic);
    } else {
        printf("Erreur %s: %s\n", fic.c_str(), _importer.GetErrorString());
    }

    return tmp;
}

bool Mesh::initScene(const aiScene * pScene, const std::string & fic) {
    _meshes.resize(pScene->mNumMeshes);
    _materiaux.resize(pScene->mNumMaterials);

    uint nbreSommet = 0;
    uint nbreInd = 0;

    nbreSommetIndice(pScene, nbreSommet, nbreInd);

    reserve(nbreSommet, nbreInd);

    initMeshes(pScene);

    if (!initMateriau(pScene, fic)) {
        return false;
    }

    initBuffers();

    return glGetError() == GL_NO_ERROR;
}


void Mesh::nbreSommetIndice(const aiScene * pScene, uint & nbreSommet, uint & nbreInd) {
    for (uint i = 0 ; i < _meshes.size() ; i++) {
        _meshes[i].materiauInd = pScene->mMeshes[i]->mMaterialIndex;
        _meshes[i].nbreInd = pScene->mMeshes[i]->mNumFaces * 3;
        _meshes[i].baseSommet = nbreSommet;
        _meshes[i].baseInd = nbreInd;

        nbreSommet += pScene->mMeshes[i]->mNumVertices;
        nbreInd  += _meshes[i].nbreInd;
    }
}


void Mesh::reserve(uint nbreSommet, uint nbreInd) {
    _sommets.reserve(nbreSommet);
    _indices.reserve(nbreInd);
}


void Mesh::initMeshes(const aiScene * pScene) {
    for (uint i = 0 ; i < _meshes.size() ; i++) {
        const aiMesh * paiMesh = pScene->mMeshes[i];
        initMesh(i, paiMesh);
    }
}


void Mesh::initMesh(uint meshInd, const aiMesh * paiMesh) {
    const aiVector3D zero(0.0f, 0.0f, 0.0f);
    Sommet v;

    for (uint i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D & pPos = paiMesh->mVertices[i];
        v.position = Vecteur3f(pPos.x, pPos.y, pPos.z);

        if (paiMesh->mNormals) {
            const aiVector3D & pNormal = paiMesh->mNormals[i];
            v.normal = Vecteur3f(pNormal.x, pNormal.y, pNormal.z);
        } else {
            aiVector3D Normal(0.0f, 1.0f, 0.0f);
            v.normal = Vecteur3f(Normal.x, Normal.y, Normal.z);
        }

        const aiVector3D & pTexCoord = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : zero;
        v.textureCoord = Vecteur2f(pTexCoord.x, pTexCoord.y);

        _sommets.push_back(v);
    }

    for (uint i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace & face = paiMesh->mFaces[i];
        _indices.push_back(face.mIndices[0]);
        _indices.push_back(face.mIndices[1]);
        _indices.push_back(face.mIndices[2]);
    }
}

bool Mesh::initMateriau(const aiScene * pScene, const std::string & fic) {
    std::string dir = cheminDuFic(fic);
    std::cout << "Dir : " << dir << std::endl;

    bool tmp = true;

    // printf("nombre materials: %d\n", pScene->mNumMaterials);

    // initialise les materiaux
    for (int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial * pMaterial = pScene->mMaterials[i];
        chargerTextureDiffuse(dir, pMaterial, i);
        chargerTextureSpeculair(dir, pMaterial, i);
        chargerCouleur(pMaterial, i);
    }

    return tmp;
}

void Mesh::chargerTextureDiffuse(const std::string & dir, const aiMaterial * pMaterial, int materiauInd) {
    // TODO: supprimer
    _materiaux[materiauInd].pDiffuse = nullptr;

    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString Path;

        if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0,  &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            const aiTexture * paiTexture = _pScene->GetEmbeddedTexture(Path.C_Str());

            if (paiTexture) {  // Texture integrée
                printf("Type de texture diffuse integrée '%s'\n", paiTexture->achFormatHint);
                _materiaux[materiauInd].pDiffuse = new Texture(GL_TEXTURE_2D);
                int buffer_size = paiTexture->mWidth;
                _materiaux[materiauInd].pDiffuse->charger(buffer_size, paiTexture->pcData);
            } else {            // Texture a part
                std::string p(Path.data);


                // TODO : supprimer
                for (int i = 0 ; i < p.length() ; i++) {
                    if (p[i] == '\\') {
                        p[i] = '/';
                    }
                }

                // TODO : supprimer
                if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }

                std::string FullPath = dir + "/" + p;

                _materiaux[materiauInd].pDiffuse = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!_materiaux[materiauInd].pDiffuse->charger()) {
                    printf("Texture diffuse chargement erreur '%s'\n", FullPath.c_str());
                    exit(0);
                }
            }
        }
    }
}

void Mesh::chargerTextureSpeculair(const std::string & dir, const aiMaterial * pMaterial, int materiauInd) {
    _materiaux[materiauInd].pExposantSpeculaire = nullptr;

    if (pMaterial->GetTextureCount(aiTextureType_SHININESS) > 0) {
        aiString Path;

        if (pMaterial->GetTexture(aiTextureType_SHININESS, 0,  &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            const aiTexture * paiTexture = _pScene->GetEmbeddedTexture(Path.C_Str());

            if (paiTexture) {       // Texture integrée
                printf("Texture speculaire integrée type '%s'\n", paiTexture->achFormatHint);
                _materiaux[materiauInd].pExposantSpeculaire = new Texture(GL_TEXTURE_2D);
                int buffer_size = paiTexture->mWidth;
                _materiaux[materiauInd].pExposantSpeculaire->charger(buffer_size, paiTexture->pcData);
            } else {                // Texture à part
                std::string p(Path.data);

                // TODO : supprimer
                if (p == "C:\\\\") {
                    p = "";
                } else if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }

                std::string FullPath = dir + "/" + p;

                _materiaux[materiauInd].pExposantSpeculaire = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!_materiaux[materiauInd].pExposantSpeculaire->charger()) {
                    printf("Texture speculaire chargement erreur '%s'\n", FullPath.c_str());
                    exit(0);
                }
            }
        }
    }
}


void Mesh::chargerCouleur(const aiMaterial * pMaterial, int index) {
    aiColor3D couleurAmbiante(0.0f, 0.0f, 0.0f);
    int modelOmbrage = 0;

    if (pMaterial->Get(AI_MATKEY_SHADING_MODEL, modelOmbrage) == AI_SUCCESS) {
        printf("model d'ombrage %d\n", modelOmbrage);
    }

    if (pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, couleurAmbiante) == AI_SUCCESS) {
        printf("chargement couleur ambiante [%f %f %f]\n", couleurAmbiante.r, couleurAmbiante.g, couleurAmbiante.b);
        _materiaux[index].couleurAmbiante.r = couleurAmbiante.r;
        _materiaux[index].couleurAmbiante.g = couleurAmbiante.g;
        _materiaux[index].couleurAmbiante.b = couleurAmbiante.b;
    } else {    // Pas de lumiere, tout à 1
        _materiaux[index].couleurAmbiante = Vecteur3f(1.0f, 1.0f, 1.0f);
    }

    aiColor3D couleurDiffuse(0.0f, 0.0f, 0.0f);

    if (pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, couleurDiffuse) == AI_SUCCESS) {
        printf("chargement couleur diffuse [%f %f %f]\n", couleurDiffuse.r, couleurDiffuse.g, couleurDiffuse.b);
        _materiaux[index].couleurDiffuse.r = couleurDiffuse.r;
        _materiaux[index].couleurDiffuse.g = couleurDiffuse.g;
        _materiaux[index].couleurDiffuse.b = couleurDiffuse.b;
    }

    aiColor3D couleurSpeculaire(0.0f, 0.0f, 0.0f);

    if (pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, couleurSpeculaire) == AI_SUCCESS) {
        printf("chargement couleur speculaire [%f %f %f]\n", couleurSpeculaire.r, couleurSpeculaire.g, couleurSpeculaire.b);
        _materiaux[index].couleurSpeculaire.r = couleurSpeculaire.r;
        _materiaux[index].couleurSpeculaire.g = couleurSpeculaire.g;
        _materiaux[index].couleurSpeculaire.b = couleurSpeculaire.b;
    }
}


void Mesh::initBuffers() {
    // glBindBuffer(GL_ARRAY_BUFFER, _buffers[SOMMET_BUFFER]);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[INDEX_BUFFER]);
    //
    // glBufferData(GL_ARRAY_BUFFER, sizeof(_sommets[0]) * _sommets.size(),  &_sommets[0], GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices.size(),  &_indices[0], GL_STATIC_DRAW);
    //
    // size_t cpt = 0;
    //
    // glEnableVertexAttribArray(POSITION_LOCATION);
    // glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Sommet), (const void*)(cpt * sizeof(float)));
    // cpt += 3;
    //
    // glEnableVertexAttribArray(TEX_COORD_LOCATION);
    // glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(Sommet), (const void *)(cpt * sizeof(float)));
    // cpt += 2;
    //
    // glEnableVertexAttribArray(NORMAL_LOCATION);
    // glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Sommet), (const void *)(cpt * sizeof(float)));

    // DSA
    glNamedBufferStorage(_buffers[SOMMET_BUFFER], sizeof(_sommets[0]) * _sommets.size(), _sommets.data(), 0);
    glNamedBufferStorage(_buffers[INDEX_BUFFER], sizeof(_indices[0]) * _indices.size(), _indices.data(), 0);

    glVertexArrayVertexBuffer(_VAO, 0, _buffers[SOMMET_BUFFER], 0, sizeof(Sommet));
    glVertexArrayElementBuffer(_VAO, _buffers[INDEX_BUFFER]);

    size_t NumFloats = 0;

    glEnableVertexArrayAttrib(_VAO, POSITION_LOCATION);
    glVertexArrayAttribFormat(_VAO, POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, (GLuint)(NumFloats * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, POSITION_LOCATION, 0);
    NumFloats += 3;

    glEnableVertexArrayAttrib(_VAO, TEX_COORD_LOCATION);
    glVertexArrayAttribFormat(_VAO, TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, (GLuint)(NumFloats * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, TEX_COORD_LOCATION, 0);
    NumFloats += 2;

    glEnableVertexArrayAttrib(_VAO, NORMAL_LOCATION);
    glVertexArrayAttribFormat(_VAO, NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, (GLuint)(NumFloats * sizeof(float)));
    glVertexArrayAttribBinding(_VAO, NORMAL_LOCATION, 0);
}

void Mesh::render(IRendererCallback * pRendererCallback) {
    // printf("Render : IRenderCallbacks\n");
    glBindVertexArray(_VAO);

    for (uint i = 0 ; i < _meshes.size() ; i++) {
        uint materiauInd = _meshes[i].materiauInd;
        assert(materiauInd < _materiaux.size());

        if (_materiaux[materiauInd].pDiffuse) {
            _materiaux[materiauInd].pDiffuse->attacher(COULEUR_TEXTURE_UNIT);
        }

        if (_materiaux[materiauInd].pExposantSpeculaire) {
            _materiaux[materiauInd].pExposantSpeculaire->attacher(EXPOSANT_SPECULAIRE_UNIT);

            if (pRendererCallback) {
                pRendererCallback->exposantSpeculaire(true);
            }
        } else {
            if (pRendererCallback) {
                pRendererCallback->exposantSpeculaire(false);
            }
        }

        if (pRendererCallback) {
            if (_materiaux[materiauInd].pDiffuse) {
                pRendererCallback->dessiner(i);
                pRendererCallback->setMateriau(_materiaux[materiauInd]);
            } else {
                pRendererCallback->desactiverTexture();
            }
        }

        glDrawElementsBaseVertex(GL_TRIANGLES,
                                 _meshes[i].nbreInd,
                                 GL_UNSIGNED_INT,
                                 (void *)(sizeof(uint) * _meshes[i].baseInd),
                                 _meshes[i].baseSommet);
    }

    glBindVertexArray(0);
}


void Mesh::render(uint renderInd, uint primitifInd) {
    printf("render : renderInd primitifInd\n");
    glBindVertexArray(_VAO);

    uint materiauInd = _meshes[renderInd].materiauInd;
    assert(materiauInd < _materiaux.size());

    if (_materiaux[materiauInd].pDiffuse) {
        _materiaux[materiauInd].pDiffuse->attacher(COULEUR_TEXTURE_UNIT);
    }

    if (_materiaux[materiauInd].pExposantSpeculaire) {
        _materiaux[materiauInd].pExposantSpeculaire->attacher(EXPOSANT_SPECULAIRE_UNIT);
    }

    glDrawElementsBaseVertex(GL_TRIANGLES,
                             3,
                             GL_UNSIGNED_INT,
                             (void *)(sizeof(uint) * (_meshes[renderInd].baseInd + primitifInd * 3)),
                             _meshes[renderInd].baseSommet);

    glBindVertexArray(0);
}



void Mesh::render(uint nbreInstance, const Matrice4f * matMVP, const Matrice4f * matMonde) {
    printf("render : nbreInstance matMVP mat Monde\n");
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[MVP_MAT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Matrice4f) * nbreInstance, matMVP, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[MONDE_MAT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Matrice4f) * nbreInstance, matMonde, GL_DYNAMIC_DRAW);

    glBindVertexArray(_VAO);

    for (uint i = 0 ; i < _meshes.size() ; i++) {
        const uint materiauInd = _meshes[i].materiauInd;

        assert(materiauInd < _materiaux.size());

        if (_materiaux[materiauInd].pDiffuse) {
            _materiaux[materiauInd].pDiffuse->attacher(COULEUR_TEXTURE_UNIT);
        }

        if (_materiaux[materiauInd].pExposantSpeculaire) {
            _materiaux[materiauInd].pExposantSpeculaire->attacher(EXPOSANT_SPECULAIRE_UNIT);
        }

        glDrawElementsInstancedBaseVertex(GL_TRIANGLES,
                                          _meshes[i].nbreInd,
                                          GL_UNSIGNED_INT,
                                          (void *)(sizeof(uint) * _meshes[i].baseInd),
                                          nbreInstance,
                                          _meshes[i].baseSommet);
    }

    glBindVertexArray(0);
}


const Materiau & Mesh::getMateriau() {
    for (uint i = 0 ; i < _materiaux.size() ; i++) {
        if (_materiaux[i].couleurAmbiante != Vecteur3f(0.0f, 0.0f, 0.0f)) {
            return _materiaux[i];
        }
    }

    return _materiaux[0];
}


void Mesh::getSommetBase(uint renderInd, uint primitifInd, Vecteur3f & sommet) {
    uint meshInd = renderInd;

    assert(meshInd < _pScene->mNumMeshes);
    const aiMesh * paiMesh = _pScene->mMeshes[meshInd];

    assert(primitifInd < paiMesh->mNumFaces);
    const aiFace & face = paiMesh->mFaces[primitifInd];

    uint indEnTete = face.mIndices[0];

    assert(indEnTete < paiMesh->mNumVertices);
    const aiVector3D & Pos = paiMesh->mVertices[indEnTete];
    sommet.x = Pos.x;
    sommet.y = Pos.y;
    sommet.z = Pos.z;
}
