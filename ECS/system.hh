#pragma once

#include "../type.hh"
#include <set>

class System {
protected:
	std::set<entity> _etts;

public:
	System() = delete;

	virtual void remove_entity(entity ett) = 0;

};

