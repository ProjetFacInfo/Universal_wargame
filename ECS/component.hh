#pragma once

#include "../type.hh"
#include <stdexcept>
#include <algorithm>
#include <array>
#include <unordered_map>

class Component_data_interface {
public:
      virtual ~Component_data_interface() = default;
      virtual void dlt_entity(entity ett) = 0;
      virtual component_id type_id;
};


template<typename C>
class Component_data : public Component_data_interface {
private:
      std::array<C, MAX_ENTITIES> _components;
      std::unordered_map<entity, u32> _ett_ind_map;

      u32 _size;

public:
      Component_data()
            :_size(0) {}

      // Return a reference to the entity's component
      C & get_component(entity ett) {
            if (_ett_ind_map.find(ett) == _ett_ind_map.end()) {
                  throw std::invalid_argument("Can't get nonexistent component.");
            }
            return _components[_ett_ind_map[ett]];
      }

      // Insert component data to the component_data array
      // and update the _ett_ind_map map.
      void add_data(entity ett, C component) {

            if (_ett_ind_map.find(ett) != _ett_ind_map.end()) {
                  throw std::invalid_argument("This component had already added to this entity.");
            }

            _ett_ind_map[ett] = _size;
            _components[_size] = component;
            ++_size;

            // printf("Add %c to entity %i\n", component, entity);
            // printf("----------\n");
      }

      // Delete component data from component_data array
      // copy last element into deleted element's place
      // to maintent density and update the _ett_ind_map map
      void dlt_data(entity ett) {
            if (_ett_ind_map.find(ett) == _ett_ind_map.end()) {
                  throw std::invalid_argument("Can't remove nonexistent component.");
            }

            size_t ind_of_remove_ett = _ett_ind_map[ett];
            C component = _components[ind_of_remove_ett];
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



      // Remove the entity's component
      // syntactic sugar for the World class
      void dlt_entity(entity ett) override {
            dlt_data(ett);
      }

      void display() {
            printf("[");
            for (size_t i = 0; i < _size-1; ++i) {
                  printf("%c, ", _components[i]);
            }
            printf("%c]\n", _components[_size-1]);

            printf("\nentity -> Index : \n");
            for (auto [key, value] : _ett_ind_map) {
                  printf("entity %i's data (%c) is at index %lu\n", key, _components[value], value);
            }
            printf("\n_size : %lu\n\n", _size);
      }
};
