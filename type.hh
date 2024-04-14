#pragma once
#include <cstdint>
#include <bitset>


using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using signature = std::bitset<16>;

const uint8 NB_ERE = 5;

enum class TypeTroupe{
    infanterie, archer, cavalier
};


// ECS
using entity = uint32;
const entity MAX_ENTITIES = 1000;
using signature = std::bitset<32>;
