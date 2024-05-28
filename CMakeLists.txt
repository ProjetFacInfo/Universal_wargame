# cmake_minimum_required(VERSION 3.18.0)
#
# project(Universal_WarGame LANGUAGES CXX)
#
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS off)
#
# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Release)
# endif()
#
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#
# if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#     add_compile_options(-Wall -Wpedantic)
# endif()
#
# file(GLOB BATIMENTS
#     objet/Batiment/Base.cc
#     objet/Batiment/BatimentRessource.cc
#     objet/Batiment/BatimentTroupe.cc
# )
#
# file(GLOB MAPF
#     objet/MAPF/Graphe.cc
#     objet/MAPF/MAPF.cc
#     objet/MAPF/Chemin.cc
# )
#
# file(GLOB OBJETS
#     objet/Batiment.cc
#     objet/Carte.cc
#     objet/Element.cc
#     objet/Graphe.cc
#     objet/Jeu.cc
#     objet/Joueur.cc
#     objet/MAPF.cc
#     objet/Troupe.cc
#     objet/IA.cc
#     ${BATIMENTS}
#     ${MAPF}
# )
#
# add_executable(Universal_WarGame main.cc ${OBJETS})
#
# add_executable(Test_MAPF Test/Test_MAPF.cc ${OBJETS})

cmake_minimum_required(VERSION 3.18.0)

project(Universal_WarGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(ASSIMP REQUIRED assimp)

# Include directories
include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
)

# Define source files for Universal_WarGame
file(GLOB BATIMENTS
    objet/Batiment/Base.cc
    objet/Batiment/BatimentRessource.cc
    objet/Batiment/BatimentTroupe.cc
)

file(GLOB MAPF
    objet/MAPF/Graphe.cc
    objet/MAPF/MAPF.cc
    objet/MAPF/Chemin.cc
)

file(GLOB OBJETS
    objet/Batiment.cc
    objet/Carte.cc
    objet/Element.cc
    objet/Graphe.cc
    objet/Jeu.cc
    objet/Joueur.cc
    objet/MAPF.cc
    objet/Troupe.cc
    objet/IA.cc
    ${BATIMENTS}
    ${MAPF}
)

# Additional source files for the graphique target
file(GLOB GRAPHIQUE_SOURCES
    graphique/graphique.cc
    graphique/util.cc
    graphique/math3D.cc
    graphique/camera.cc
    graphique/monde_transformation.cc
    graphique/texture.cc
    graphique/lumiere.cc
    graphique/renderer.cc
    graphique/mesh.cc
    graphique/squelette_mesh.cc
    graphique/logiciel_tiers/stb_image.cc
    graphique/technique.cc
    graphique/texture_technique.cc
    graphique/squelette_technique.cc
    graphique/triangle_list.cc
    graphique/terrain.cc
    graphique/terrain_technique.cc
    graphique/glfw.cc
)

# Add the executable for Universal_WarGame
add_executable(Universal_WarGame main.cc ${OBJETS})

# Add the executable for Test_MAPF
add_executable(Test_MAPF Test/Test_MAPF.cc ${OBJETS})

# Add the executable for graphique
add_executable(graphique ${GRAPHIQUE_SOURCES})

# Link libraries to the graphique executable
target_link_libraries(graphique
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    X11
    dl
)

# Add debug information for graphique
set_target_properties(graphique PROPERTIES COMPILE_FLAGS "-ggdb3")
