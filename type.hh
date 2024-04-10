#pragma once
#include <cstdint>
#include <bitset>

// ECS
using u32 = std::uint32_t;
using u8 = std::uint8_t;
using entity = u32;
const entity MAX_ENTITIES = 5000;
using component_id = u8;
const component_id MAX_COMPONENTS = 64;
