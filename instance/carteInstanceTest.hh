#pragma once
#include <map>
#include <string>
#include <array>
#include "../objet/Terrain.hh"

std::map<std::string, std::array<Terrain,256>> maps{
    {"1", {
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::foret, Terrain::foret, Terrain::montagne, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::montagne, Terrain::montagne, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::montagne, Terrain::montagne, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::colline, Terrain::montagne, Terrain::montagne, Terrain::montagne, Terrain::montagne, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau
    }},

    {"2", {
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::foret, Terrain::foret, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::desert, Terrain::desert, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::montagne, Terrain::colline, Terrain::colline, Terrain::plaine, Terrain::colline, Terrain::colline, Terrain::colline, Terrain::plaine, Terrain::colline, Terrain::colline, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine,
        Terrain::eau, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::colline, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::plaine, Terrain::eau, Terrain::eau, Terrain::eau,
        Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau, Terrain::eau
    }}
};
