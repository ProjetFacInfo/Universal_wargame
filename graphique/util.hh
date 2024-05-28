#pragma once

#include "types.hh"
#include <string>
#include <fstream>
#include <chrono>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices )
constexpr unsigned int INVALID_UNIFORM_LOCALISATION = 0xffffffff;
constexpr int MAX_OS = 200;

template<typename T>
void CLAMP(T& val, const T& start, const T& end) {
    val = std::min(std::max(val, start), end);
}

template <typename T, std::size_t N>
constexpr std::size_t nbreElmDansTab(const T (&)[N]) noexcept {
    return N;
}

long long getTempsMilliSecondre();
bool lireFichier(const char* pFileName, std::string& outFile);
std::string cheminDuFic(const std::string & fic);

