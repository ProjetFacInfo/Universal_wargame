cmake_minimum_required(VERSION 3.18.0)

project(Universal_WarGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

file(GLOB OBJET_HEADER
    objet/Element.hh
    objet/Jeu.hh
    objet/Joueur.hh
)

file(GLOB OBJETS
    #objet/Element.cc
    objet/Jeu.cc
    objet/Joueur.cc
    ${OBJET_HEADER}
)

add_executable(Universal_WarGame main.cc ${OBJETS})