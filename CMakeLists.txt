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
)

file(GLOB OBJET_HEADER
    objet/Batiment.hh
    objet/Carte.hh
    objet/Element.hh
    objet/Graphe.hh
    objet/Jeu.hh
    objet/Joueur.hh
    objet/MAPF.hh
    objet/Terrain.hh
    objet/Troupe.hh
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
    ${OBJET_HEADER}
    ${BATIMENTS}
)



add_executable(Universal_WarGame main.cc ${OBJETS})