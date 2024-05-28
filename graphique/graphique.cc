#include <GL/glew.h>

#include "glfw.hh"
#include "util.hh"

#include "camera.hh"
#include "mesh.hh"
#include "monde_transformation.hh"
#include "lumiere.hh"
#include "renderer.hh"

#include "GLTerrainTextureUnit.hh"
#include "terrain.hh"

#include <cstdio>
#include <string.h>
#include <iostream>
#include <math.h>
#include <vector>

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080
#define Z_FAR 5000.0f

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursorPosCallback(GLFWwindow* window, double x, double y);
static void mouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);


class Graphique {
private:
    GLFWwindow* window = NULL;
    Camera* _pCamera = NULL;
    Renderer _renderer;
    SqueletteMesh* _pMesh1 = NULL;
    PersProjInfo _persProfInfo;
    LumiereDirectionnel _lumiereDir;
    Terrain _terrain;

    long long _debTemps = 0;
    long long _courantTemps = 0;
    bool _runAnimation = true;
    long long _pauseTemps = 0;
    long long _pauseDeb = 0;
    int _animationInd = 0;

    int _terrainSize = 256;
    float _roughness = 1.5f;
    float _hauteurMin = -20.0f;
    float _hauteurMax = 200.0f;
    bool _constrainCamera = false;

public:
    Graphique() {
        _lumiereDir.directionMonde = Vecteur3f(0.0f, -1.0f, 1.0f);
        _lumiereDir.intensiteDiffuse = 1.0f;
        _lumiereDir.intensiteAmbiante = 0.5f;
    }

    virtual ~Graphique() {
        if (_pCamera) {
            delete _pCamera;
            _pCamera = NULL;
        }
    }


    void init() {
        createWindow();

        initCallbacks();

        initTerrain();

        initCamera();

        initMesh();

        initRenderer();

        _debTemps = getTempsMilliSecondre();
        _courantTemps = _debTemps;
    }

    // boucle principale du programme qui continue tant que la fenetre n'est pas fermée
    void Run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            // récupère la taille du framebuffer (la zone de rendu en pixels)
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            // définit la zone de rendu (viewport) pour correspondre à la taille du framebuffer
            glViewport(0, 0, display_w, display_h);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            RenderScene();
            // std::cerr << "=================== run ok ======================" << std::endl;
            glfwSwapBuffers(window);
        }
    }


    void RenderScene() {

        _pCamera->OnRender();

        if (_runAnimation) {
            _courantTemps = getTempsMilliSecondre();
        }

        _terrain.setLumiereDir(_lumiereDir.directionMonde);
        _terrain.render(*_pCamera);

        float AnimationTimeSec = (float)((double)_courantTemps - (double)_debTemps) / 1000.0f;
        float TotalPauseTimeSec = (float)((double)_pauseTemps / 1000.0f);
        AnimationTimeSec -= TotalPauseTimeSec;

        _renderer.renderAnimation(_pMesh1, AnimationTimeSec, _animationInd);
    }


    void passiveMouseCB(int x, int y) {
            _pCamera->OnMouse(x, y);
    }

    void keyboardCB(uint key, int state) {
        if (state == GLFW_PRESS) {

            switch (key) {

            case GLFW_KEY_ESCAPE:
                glfwDestroyWindow(window);
                glfwTerminate();
                exit(0);

            }
            _pCamera->OnKeyboard(key);
        }
    }


    void mouseCB(int button, int action, int x, int y) {
    }

    void createWindow() {
        int major_ver = 0;
        int minor_ver = 0;
        bool estPleinEcrain = true;
        window = glfw_init(major_ver, minor_ver, WINDOW_WIDTH, WINDOW_HEIGHT, estPleinEcrain, "Universal Wargame");
        glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }


    void initCallbacks() {
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCursorPosCallback(window, cursorPosCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
    }

    void initTerrain() {
        float worldScale = 4.0f;
        float textureScale = 1.0f;
        std::vector<std::string> textureNomFic;
        textureNomFic.push_back("../graphique/data/textures/ocean_terrain.jpg");
        textureNomFic.push_back("../graphique/data/textures/eau_terrain.jpg");
        textureNomFic.push_back("../graphique/data/textures/desert_terrain.jpg");
        textureNomFic.push_back("../graphique/data/textures/pelouse_terrain.png");
        textureNomFic.push_back("../graphique/data/textures/montagne_terrain.jpg");
        textureNomFic.push_back("../graphique/data/textures/neige_terrain.png");

        _terrain.initTerrain(worldScale, textureScale, textureNomFic);
        _terrain.creerCarteDiamantCarre(_terrainSize, _roughness, _hauteurMin, _hauteurMax);
        // _terrain.creerCarte("../instance/carte_hauteur", _terrainSize, _hauteurMin, _hauteurMax);
        _terrain.setLumiereDir(_lumiereDir.directionMonde);
    }

    void initCamera() {
        float CameraX = _terrain.getTailleMonde() / 2.0f;
        Vecteur3f Pos(CameraX , 600.0f, 0);
        Vecteur3f Target(0.0f, -0.25f, 1.0f);
        Vecteur3f Up(0.0, 1.0f, 0.0f);

        float FOV = 45.0f;
        float zNear = 0.01f;
        float zFar = Z_FAR;
        PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };

        _pCamera = new Camera(persProjInfo, Pos, Target, Up);
        _pCamera->setVitesse(10.0f);
    }


    void initRenderer() {
        _renderer.initRenderer();
        _renderer.setCamera(_pCamera);
        _renderer.setLumiereDirectionel(_lumiereDir);
    }


    void initMesh() {
        float scale = 0.1f;
        float CameraX = _terrain.getTailleMonde() / 2.0f;
        float CameraZ = CameraX;
        Vecteur3f Pos(CameraX, 0.0f, CameraZ);
        Pos = _terrain.constrainPosToTerrain(Pos);
        Pos.y += 10.0f;

        _pMesh1 = new SqueletteMesh();
        _pMesh1->chargerMesh("../graphique/data/Walking.dae");
        void setPosition(const Vecteur3f & pos);
        _pMesh1->setPosition(Pos);
        _pMesh1->setScale(scale);
    }

};

Graphique* app = NULL;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    app->keyboardCB(key, action);
}


static void cursorPosCallback(GLFWwindow* window, double x, double y) {
    app->passiveMouseCB((int)x, (int)y);
}


static void mouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    app->mouseCB(Button, Action, (int)x, (int)y);
}


int main(int argc, char** argv) {

    app = new Graphique();

    app->init();

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 0.0f);
    // glClearColor(0.04f, 0.04f, 0.16f, 1.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    app->Run();

    delete app;

    return 0;
}
