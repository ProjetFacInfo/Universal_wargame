#pragma once

#include "../type.hh"
#include "component.hh"
#include <memory>


// Class qui gere les composants avec :
// un map : p type id -> pointeur des composants
// un u32 : un compteur de type de component
class Component_manager {
      private:
            std::unordered_map<signature, std::shared_ptr<Component_data_interface>> _component_arrays;

      public:
            Component_manager() = default;

            template <typename T>
            void save_component(signature const & mask) {
                  if (_component_arrays.find(mask) != _component_arrays.end()) {
                        throw std::invalid_argument("Component type already exist.");
                  }

                  _component_arrays.insert({mask, std::make_shared<Component_data<T>>()});
            }

            template <typename T>
            T & get_component(entity ett, signature const & mask) {
                  try {
                        return get_component_data<T>(mask)->get_data(ett);
                  } catch (std::invalid_argument const & e) {
                        std::cerr << e.what() << std::endl;
                        exit(1);
                  }
            }

            template <typename T>
            void add_component(entity ett, T component, signature const & mask) {
                  try {
                        get_component_data<T>(mask)->add_data(ett, component);
                  } catch (std::invalid_argument const & e) {
                        std::cerr << e.what() << std::endl;
                  }
            }

            template <typename T>
            void remove_component(entity ett, signature const & mask) {
                  try {
                        get_component_data<T>(mask)->remove_data(ett);
                  } catch (std::invalid_argument const & e) {
                        std::cerr << e.what() << std::endl;
                  }
            }

            void delete_entity(entity ett) {
                  for (auto const & [mask, component] : _component_arrays) {
                        component->remove_entity(ett);
                  }
            }

      private:
            // Determine quel type de composant il s'agit
            template <typename T>
                  std::shared_ptr<Component_data<T>> get_component_data(signature const & mask) {
                        if (_component_arrays.find(mask) == _component_arrays.end()) {
                              throw std::invalid_argument("Component type missing.");
                        }

                        return std::static_pointer_cast<Component_data<T>>(_component_arrays[mask]);
                  }


};

