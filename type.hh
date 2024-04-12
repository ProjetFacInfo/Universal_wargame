#pragma once
#include <cstdint>
#include <bitset>
#include <string>
#include <map>


// ECS
using u32 = std::uint32_t;
using entity = u32;
const entity MAX_ENTITIES = 1000;
using signature = std::bitset<32>;

// TODO:const_map
