#pragma once

enum class Terrain{
    plaine = 1,         // 0000'...'0000'0000'0000'0001
    colline = 4,        // 0000'...'0000'0000'0000'0100
    montagne = 16,      // 0000'...'0000'0000'0001'0000
    foret = 64,         // 0000'...'0000'0000'0100'0000
    desert = 256,       // 0000'...'0000'0001'0000'0000
    eau = 1024,         // 0000'...'0000'0100'0000'0000
    mer = 4096,         // 0000'...'0001'0000'0000'0000
};
