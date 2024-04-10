// TODO : simplifier ?? un seul map, enlever static_cast
#pragma once

#include  "component.hh"
#include <typeinfo>
#include <memory>

// Class qui gere les composants avec :
// un map : p type id -> id des composants
// un map : p type id -> pointeur des composants
class Component_manager {
      private:
            std::unordered_map<const char *, component_id> _component_ids;
            std::unordered_map<const char *, std::shared_ptr<Component_interface>> _component_arrays;
            component_id _component_id_counter;

      public:
            Component_manager()
                  :_component_id_counter(0) {}

            template <typename C>
            component_id get_component_id() {
                  const char * type_id = typeid(C).name();

                  if (_componenet_ids.find(type_id) == _component_ids.end()) {
                        throw std::invalid_argument("Component id no find.")
                  }

                  return _component_ids[type_id];

            }

            template <typename C>
            void save_component() {
                  const char * type_id = typeid(C).name();

                  if (_component_ids.find(type_id) != _component_ids.end()) {
                        throw std::invalid_argument("Component id already exist.");
                  }

                  _component_ids.insert({type_id, _component_id_counter++});
                  _component_arrays.insert({type_id, std::make_shared<Component_data<C>>()});
            }

            template <typename C>
            void add_component(entity ett, C component) {
                  get_component_array<T>()->add_data();
            }

            template <typename C>
            void remove_component(entity ett) {
                  get_component_array<T>()->dlt_data(ett);
            }



};

