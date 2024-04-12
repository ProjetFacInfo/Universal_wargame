#pragma once

#include "../type.hh"
#include <stdexcept>
#include <algorithm>
#include <array>
#include <unordered_map>

class Component_data_interface {
public:
      virtual ~Component_data_interface() = default;
      virtual void remove_entity(entity ett) = 0;
};


template <typename T>
class Component_data : public Component_data_interface {
private:
      std::array<T, MAX_ENTITIES> _components;
      std::unordered_map<entity, u32> _ett_ind_map;
      u32 _size;

public:
      Component_data()
            :_size(1) {}

      // Return la reference du composant de l'entité
      T & get_data(entity ett);


      // Insert component data to the component_data array
      // and update the _ett_ind_map map.
      void add_data(entity ett, T component);

      // Delete component data from component_data array
      // copy last element into deleted element's place
      // to maintent density and update the _ett_ind_map map
      void remove_data(entity ett);

      // Remove the entity's component from All king of component_data array
      void remove_entity(entity ett) override {
            remove_data(ett);
      }

      void display() {
            printf("[");
            for (size_t i = 0; i < _size-1; ++i) {
                  printf("%i - %i, ", _components[i].current_health, _components[i].max_health);
            }
            printf("%i - %i]\n", _components[_size-1].current_health, _components[_size-1].max_health);

            printf("\nentity -> Index : \n");
            for (auto [key, value] : _ett_ind_map) {
                  printf("entity %i's data (%i- %i) is at index %u\n", key, _components[value].current_health, _components[value].max_health, value);
            }
            printf("\n_size : %u\n\n", _size);
      }
};


template <typename T>
T & Component_data<T>::get_data(entity ett) {
      if (_ett_ind_map.find(ett) == _ett_ind_map.end()) {
            throw std::invalid_argument("Can't get nonexistent component.");
      }
      return _components[_ett_ind_map[ett]];
}

template <typename T>
void Component_data<T>::add_data(entity ett, T component) {
      if (_ett_ind_map.find(ett) != _ett_ind_map.end()) {
            throw std::invalid_argument("This component had already added to this entity.");
      }
      _ett_ind_map[ett] = _size;
      _components[_size] = component;
      ++_size;
      // printf("Add %c to entity %i\n", component, entity);
      // printf("----------\n");
}

template <typename T>
void Component_data<T>::remove_data(entity ett) {
      if (_ett_ind_map.find(ett) == _ett_ind_map.end()) {
            throw std::invalid_argument("Can't remove nonexistent component.");
      }
      size_t ind_of_remove_ett = _ett_ind_map[ett];
      T component = _components[ind_of_remove_ett];
      _components[ind_of_remove_ett] = _components[_size - 1];

      auto it = std::find_if(_ett_ind_map.begin(), _ett_ind_map.end(),
                  [this](auto const & e) {return e.second == _size - 1;});

      entity ett_of_last_elm = it->first;
      _ett_ind_map[ett_of_last_elm] = ind_of_remove_ett;
      _ett_ind_map.erase(ett);
      --_size;
      // printf("Delete %c (which was at Index %li and was the data of entity %i)\n", component, ind_of_remove_ett, ett);
      // printf("----------\n");
}
