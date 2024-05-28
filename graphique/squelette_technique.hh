#include "technique.hh"
#include "math3D.hh"
#include "lumiere.hh"

class SqueletteTechnique : public LumiereTechnique {
private:
    GLuint _osLoc[MAX_OS];

public:
    SqueletteTechnique() = default;
    virtual bool init();
    void setSqueletteTransform(uint ind, const Matrice4f & transform);

};

