#pragma once

class IRendererCallback {
public:
    virtual void dessiner(uint dessinInd) {}

    virtual void exposantSpeculaire(bool estDesactiver) {}

    virtual void setMateriau(const Materiau & materiau) {}

    virtual void desactiverTexture() {}
};
