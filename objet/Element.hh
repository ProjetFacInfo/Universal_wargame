#include <string>
using uint32 = uint32_t;
using uint8 = uint8_t;

enum class Type { batiment, troupe};

struct Ressource {
	uint32 Metaux, Bois, Viande;
};


class Element {
private:
	std::string _nom;
	Type _type;
	uint32 _vie;
	uint32 _pos;
	uint8  _ere;
	Ressource _cout;

public:

};
