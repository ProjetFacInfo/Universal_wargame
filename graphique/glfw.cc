#include "glfw.hh"
#include "util.hh"

#include <cstdio>
#include <iostream>

static int glMajorVersion = 0;
static int glMinorVersion = 0;

static void glfw_lib_init() {
    if (glfwInit() != 1) {
        std::cerr << "glfw erreur initialisation" << std::endl;
        exit(1);
    }

    int Major, Minor, Rev;
    glfwGetVersion(&Major, &Minor, &Rev);
    printf("GLFW %d.%d.%d initialisé \n", Major, Minor, Rev);
}


static void enable_debug_output() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
}


static void init_glew() {
    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cerr << "erreur initialisation GLEW" << ((const char*)glewGetErrorString(res)) << std::endl;
        exit(1);
    }
}


GLFWwindow* glfw_init(int major_ver, int minor_ver, int width, int height, bool is_full_screen, const char* title) {
    glfw_lib_init();
    GLFWmonitor* monitor = is_full_screen ? glfwGetPrimaryMonitor() : NULL;
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    if (major_ver > 0) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
    }

    if (minor_ver > 0) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, NULL);

    if (!window) {
        const char* pDesc = NULL;
        int error_code = glfwGetError(&pDesc);
        std::cerr << "Erreur de création de la fenêtre: " << pDesc << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);

    if (major_ver > 0) {
        if (major_ver != glMajorVersion) {
            std::cerr << "la version majeure demandée ne correspond pas à la version crée\n"
                << " demandé : " << major_ver << ", obtenu : " << glMajorVersion << std::endl;
            exit(0);
        }
    }

    if (minor_ver > 0) {
        if (minor_ver != glMinorVersion) {
            std::cerr << "la version mineure demandée ne correspond pas à la version crée\n"
                << " demandé : " << minor_ver << ", obtenu : " << glMinorVersion << std::endl;
            exit(0);
        }
    }

    init_glew();
    enable_debug_output();
    glfwSwapInterval(1);

    return window;
}

void debugCallback
(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
    GLuint ignore_ids[1] = { 131185 };

    for (int i = 0 ; i < nbreElmDansTab(ignore_ids) ; i++) {
        if (id == ignore_ids[i]) {
            return;
        }
    }

    printf("!!! Debug callback !!!\n");
    printf("Debug message: id %d, %s\n", id, message);

    printf("Message source: ");
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             printf("API\n"); break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Window System\n"); break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Shader Compiler\n"); break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Third Party\n"); break;
    case GL_DEBUG_SOURCE_APPLICATION:     printf("Application\n"); break;
    case GL_DEBUG_SOURCE_OTHER:           printf("Other\n"); break;
    }

    printf("Error type: ");
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               printf("Error\n"); break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Deprecated Behaviour\n"); break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Undefined Behaviour\n"); break;
    case GL_DEBUG_TYPE_PORTABILITY:         printf("Portability\n"); break;
    case GL_DEBUG_TYPE_PERFORMANCE:         printf("Performance\n"); break;
    case GL_DEBUG_TYPE_MARKER:              printf("Marker\n"); break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Push Group\n"); break;
    case GL_DEBUG_TYPE_POP_GROUP:           printf("Pop Group\n"); break;
    case GL_DEBUG_TYPE_OTHER:               printf("Other\n"); break;
    }

    printf("Severity: ");
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         printf("High\n"); break;
    case GL_DEBUG_SEVERITY_MEDIUM:       printf("Medium\n"); break;
    case GL_DEBUG_SEVERITY_LOW:          printf("Low\n"); break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Notification\n"); break;
    }
}
