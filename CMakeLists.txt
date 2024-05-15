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
    ${BATIMENTS}
    ${MAPF}
)

add_executable(Universal_WarGame main.cc ${OBJETS})
