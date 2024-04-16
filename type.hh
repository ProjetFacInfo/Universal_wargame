#pragma once
#include <cstdint>
#include <bitset>


using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;

using weapon_signature = std::bitset<3>;
using arms_signature = std::bitset<8>;
using signature = std::bitset<32>;


// ECS
// using entity = uint32;
// const entity MAX_ENTITIES = 1000;
