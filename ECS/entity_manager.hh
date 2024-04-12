#pragma once

#include "../type.hh"
#include <stdexcept>
#include <algorithm>

class Entity_manager {
private:
  u32 _entity_counter;
  std::unordered_map<entity, signature> _ett_signature_map;

public:
  Entity_manager()
    :_entity_counter(1) {}

  entity create_entity() {
    if (_entity_counter > MAX_ENTITIES) {
      throw std::length_error("entity over the max capacity !");
      return 0;
    }
    entity tmp(_entity_counter++);
    _ett_signature_map.insert({tmp, 0});
    return tmp;
  }

  void delete_entity(entity ett) {
    if (_ett_signature_map.find(ett) == _ett_signature_map.end()) {
      throw std::invalid_argument("Delete a nonexistent entity.");
    }
    _ett_signature_map.erase(ett);
  }

  signature get_ett_signature(entity ett) {
    if (_ett_signature_map.find(ett) == _ett_signature_map.end()) {
      throw std::invalid_argument("Delete a nonexistent entity.");
    }
    return _ett_signature_map[ett];
  }

  void set_ett_signature(entity ett, signature const & s)  {
    if (_ett_signature_map.find(ett) == _ett_signature_map.end()) {
      throw std::invalid_argument("Delete a nonexistent entity.");
    }
    _ett_signature_map[ett] = s;
  }

  void add_bit_to_ett_signature(entity ett, signature const & s) {
    _ett_signature_map[ett] |= s;
  }

  void remove_bit_to_ett_signature(entity ett, signature const & s) {
    _ett_signature_map[ett] ^= s;
  }

  void display() const {
    for(auto const & [e, s] : _ett_signature_map) {
		  std::cout << e << " = " << s << std::endl;
    }
  }
};
