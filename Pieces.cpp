#include"Pieces.h"
using namespace std;


Pieces::Pieces(const char* Type ,const char* Colour )
{
	type = new char[strlen(Type) + 1];
	colour = new char[strlen(Colour) + 1];

	copy(type, Type);
	copy(colour, Colour);
	mov_stat = 0;
}
string Pieces::getType()
{
	return type;
}

const char* Pieces::getColour()
{
	return colour;
}

Pieces::~Pieces()
{
	delete[] type;
	delete[] colour;

	type = nullptr; colour = nullptr;
}