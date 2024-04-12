#pragma once

#include "system.hh"

class System_manager {
private:
	std::unordered_map<signature, std::shared_ptr<System>> _systems;

public:
	System_manager() = default;

	template <typename T>
	std::shared_ptr<T> save_system(signature const & mask) {
		if (_systems.find(mask) != _systems.end()) {
			throw std::invalid_argument("Component type already exist.");
		}

		auto system = std::make_shared<T>();
		_systems.insert({mask, system});
		return system;
	}


	void delete_entity(entity ett) {
		for (auto const & [mask, system] : _systems) {
			system->remove_entity(ett);
		}
	}

};
