using ui32 = uint32_t;
using ui8 = uint8_t;

enum class Type { batiment, troupe};

struct Ressource {
	Metaux,
	Bois,
	Viande
};


class Element {
private:
	std::string _nom;
	Type _type;
	ui32 _vie;
	ui32 _pos;
	ui8  _ere;
	Ressource _cout;

public:



}
