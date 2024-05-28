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

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double x, double y);
static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);


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
    float _roughness = 2.0f;
    float _hauteurMin = -2.0f;
    float _hauteurMax = 100.0f;
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


    void Init() {
        CreateWindow();

        InitCallbacks();

        InitTerrain();

        InitCamera();

        InitMesh();

        InitRenderer();

        _debTemps = getTempsMilliSecondre();
        _courantTemps = _debTemps;
        // std::cerr << "=================== Init ok ======================" << std::endl;
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
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _pCamera->OnRender();

        if (_runAnimation) {
            _courantTemps = getTempsMilliSecondre();
        }

        // _terrain.setLumiereDir(_lumiereDir.directionMonde);
        // _terrain.render(*_pCamera);
        _terrain.setLightDir(_lumiereDir.directionMonde);
        _terrain.Render(*_pCamera);

        float AnimationTimeSec = (float)((double)_courantTemps - (double)_debTemps) / 1000.0f;
        float TotalPauseTimeSec = (float)((double)_pauseTemps / 1000.0f);
        AnimationTimeSec -= TotalPauseTimeSec;

        // std::cerr << "=================== Render ok ======================" << std::endl;
        _renderer.renderAnimation(_pMesh1, AnimationTimeSec, _animationInd);
    }


    void PassiveMouseCB(int x, int y) {
            _pCamera->OnMouse(x, y);
    }

    void KeyboardCB(uint key, int state) {
        if (state == GLFW_PRESS) {

            switch (key) {

            case GLFW_KEY_ESCAPE:
                glfwDestroyWindow(window);
                glfwTerminate();
                exit(0);

            case GLFW_KEY_B:
                _constrainCamera = !_constrainCamera;
                printf("constrain %d\n", _constrainCamera);
                break;
            }

            bool CameraChangedPos = _pCamera->OnKeyboard(key);

            if (_constrainCamera && CameraChangedPos) {
                ConstrainCameraToTerrain();
            }
        }

    }


    void MouseCB(int button, int action, int x, int y) {
    }
    void CreateWindow() {
        int major_ver = 0;
        int minor_ver = 0;
        bool estPleinEcrain = true;
        window = glfw_init(major_ver, minor_ver, WINDOW_WIDTH, WINDOW_HEIGHT, estPleinEcrain, "Universal Wargame");
        glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }


    void InitCallbacks() {
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

    void InitTerrain() {
        float WorldScale = 4.0f;
        float TextureScale = 1.0f;
        std::vector<std::string> TextureFilenames;
        TextureFilenames.push_back("../graphique/data/textures/ocean_terrain.jpg");
        TextureFilenames.push_back("../graphique/data/textures/eau_terrain.jpg");
        TextureFilenames.push_back("../graphique/data/textures/pelouse_terrain.png");
        TextureFilenames.push_back("../graphique/data/textures/montagne_terrain.jpg");

        // _terrain.initTerrain(WorldScale, TextureScale, TextureFilenames);
        // _terrain.creerCarteDiamantCarre(_terrainSize, _roughness, _hauteurMin, _hauteurMax);
        //
        //
        // _terrain.sauvegarderDansFichier("carte_aleatoire");
        // _terrain.setLumiereDir(_lumiereDir.directionMonde);

        _terrain.InitTerrain(WorldScale, TextureScale, TextureFilenames);
        _terrain.CreateMidpointDisplacement(_terrainSize, _roughness, _hauteurMin, _hauteurMax);
        // _terrain.CreateMap("carte_aleatoire", _terrainSize, _hauteurMin, _hauteurMax);


        _terrain.SaveToFile("carte_aleatoire");
        _terrain.setLightDir(_lumiereDir.directionMonde);
    }

    void InitCamera() {
        float CameraX = _terrain.getWorldSize() / 2.0f;
        // float CameraX = _terrain.getTailleMonde() / 2.0f;
        float CameraZ = CameraX;
        Vecteur3f Pos(CameraX , 0.0f, CameraZ);
        Pos = _terrain.ConstrainPosToTerrain(Pos);
        // Pos = _terrain.contraindrePositionAuTerrain(Pos);
        std::cout << "getWorldHeight : " << _terrain.getWorldHeight(CameraX, CameraZ) << std::endl;
        Pos.y += 100.0f;
        Vecteur3f Target(0.0f, -0.25f, 1.0f);
        Vecteur3f Up(0.0, 1.0f, 0.0f);

        float FOV = 45.0f;
        float zNear = 0.01f;
        float zFar = Z_FAR;
        PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };

        _pCamera = new Camera(persProjInfo, Pos, Target, Up);
        _pCamera->setVitesse(10.0f);
        printf("camera : x %f y %f z %f\n", Pos.x, Pos.y, Pos.z);

        // Vecteur3f Pos(0.0f, 0.0f, 0.0f);
        // Vecteur3f Target(0.0f, 0.0f, 1.0f);
        // Vecteur3f Up(0.0, 1.0f, 0.0f);
        // float FOV = 45.0f;
        // float zNear = 0.1f;
        // float zFar = Z_FAR;
        // PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };
        // _pCamera = new Camera(persProjInfo, Pos, Target, Up);
        // _pCamera->setVitesse(10.0f);
    }


    void InitRenderer() {
        _renderer.initRenderer();
        _renderer.setCamera(_pCamera);
        _renderer.setLumiereDirectionel(_lumiereDir);
    }


    void InitMesh() {
        float scale = 0.1f;
        float CameraX = _terrain.getWorldSize() / 2.0f;
        float CameraZ = CameraX;
        Vecteur3f Pos(CameraX, 0.0f, CameraZ);
        Pos = _terrain.ConstrainPosToTerrain(Pos);
        printf("Model 1 : x %f y %f z %f\n", Pos.x, Pos.y, Pos.z);
        // Pos.y += 10.0f * scale;
        printf("Model 1 : x %f y %f z %f\n", Pos.x, Pos.y, Pos.z);

        _pMesh1 = new SqueletteMesh();
        _pMesh1->chargerMesh("../graphique/data/Walking.dae");
        void setPosition(const Vecteur3f & pos);
        _pMesh1->setPosition(Pos);
        // printf("Position mesh : ");
        // _pMesh1->getPosition().print();
        // printf("\n");
        _pMesh1->setScale(scale);

    }

    void ConstrainCameraToTerrain() {
        Vecteur3f NewCameraPos = _terrain.ConstrainPosToTerrain(_pCamera->getPos());
        NewCameraPos.y += 10.0f;

        _pCamera->setPosition(NewCameraPos);
    }
};

Graphique* app = NULL;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    app->KeyboardCB(key, action);
}


static void CursorPosCallback(GLFWwindow* window, double x, double y) {
    app->PassiveMouseCB((int)x, (int)y);
}


static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    app->MouseCB(Button, Action, (int)x, (int)y);
}


int main(int argc, char** argv) {

    app = new Graphique();

    app->Init();

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 0.0f);
    // glClearColor(0.04f, 0.04f, 0.16f, 1.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    app->Run();

    delete app;
    // std::cerr << "=================== main ok ======================" << std::endl;

    return 0;
}
